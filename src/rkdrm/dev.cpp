/*
 * Copyright 2016 Rockchip Electronics S.LSI Co. LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
#include "dev.h"
#include "log.h"

#if 0 //def USE_ATOMIC_API
static uint32_t get_prop_id(struct sp_dev *dev,
			    drmModeObjectPropertiesPtr props, const char *name){
	drmModePropertyPtr p;
	uint32_t i, prop_id = 0; /* Property ID should always be > 0 */

	for (i = 0; !prop_id && i < props->count_props; i++) {
		p = drmModeGetProperty(dev->fd, props->props[i]);
		if (!strcmp(p->name, name))
		prop_id = p->prop_id;
		drmModeFreeProperty(p);
	}
	if (!prop_id)
		LOGE("Could not find %s property\n", name);
	return prop_id;
}
#endif

static char char_buff[5] = {0};

struct property_arg {
	uint32_t obj_id;
	uint32_t obj_type;
	char name[DRM_PROP_NAME_LEN+1];
	uint32_t prop_id;
	uint64_t value;
};


char* HexStringToAscii(const char *pc, unsigned int length)
{
	// And store a printable ASCII character for later.
	int i = 0;
	for(i=0; i<length; i++) {
		if ((pc[i] < 0x20) || (pc[i] > 0x7e))
			char_buff[i] = '.';
		else
			char_buff[i] = pc[i];
	}
	char_buff[i + 1] = '\0';

	return (char*) char_buff;
}

void set_plane_property(int fd, int plane_id, struct property_arg *p)
{
    drmModeObjectPropertiesPtr props;
    drmModePropertyPtr pt;
    const char *obj_type;
    int ret;
    int i;

    props = drmModeObjectGetProperties(fd, plane_id, DRM_MODE_OBJECT_PLANE);

    if(props){
        for (i = 0; i < (int)props->count_props; ++i) {

            pt = drmModeGetProperty(fd, props->props[i]);

            if (!pt)
                continue;
            if (strcmp(pt->name, p->name) == 0){
                drmModeFreeProperty(pt);
                LOGE("GET Rigth name %s\n",  p->name);
                break;
            }

            drmModeFreeProperty(pt);
        }

        if (i == (int)props->count_props) {
            printf("%i has no %s property\n",p->obj_id, p->name);
            return;
        }

        p->prop_id = props->props[i];

        LOGE("GdrmModeObjectSetProperty\n",  p->name);

        ret = drmModeObjectSetProperty(fd, p->obj_id, p->obj_type,
                           p->prop_id, p->value);

        LOGE("GdrmModeObjectSetProperty Done ret = %d\n", ret);

        if (ret < 0) {
           //GE("faild to set property %s,id %d,value %d\n",p->obj_id, p->name, p->value);
        }

        drmModeFreeObjectProperties(props);
    }
}

void get_planes_property(int fd,drmModePlaneRes *pr)
{
	drmModeObjectPropertiesPtr props;
	int i,j;
	drmModePropertyPtr p;

	for(i = 0; i < pr->count_planes; i++) {
		LOGD("planes id %d\n",pr->planes[i]);
		props = drmModeObjectGetProperties(fd, pr->planes[i], DRM_MODE_OBJECT_PLANE);
		if(props){
			for (j = 0;j < props->count_props; j++) {
				p = drmModeGetProperty(fd, props->props[j]);
				LOGD("get property ,name %s, id %d\n",p->name,p->prop_id);
				drmModeFreeProperty(p);
			}
			drmModeFreeObjectProperties(props);
		}
		LOGD("\n\n");
	}
}

void set_rotation(int fd, int plane_id,int value)
{
	struct property_arg prop;

	if(value !=1 && value !=2 && value !=4 && value !=8)
		return;

	memset(&prop, 0, sizeof(prop));
	prop.obj_type = 0;
	prop.name[DRM_PROP_NAME_LEN] = '\0';
	prop.obj_id = plane_id;
	memcpy(prop.name,"rotation",sizeof("rotation"));
	prop.value = value; //rotate-0=0x1 rotate-90=0x2 rotate-180=0x4 rotate-270=0x8, modetest -p can show the details

	LOGD("==SET set_plane_property\n");
	set_plane_property(fd, plane_id, &prop);
	LOGD("==SET set_plane_property Done\n");

}

int is_supported_format(struct sp_plane* plane, uint32_t format)
{
	uint32_t i;
	// DEBUG only
	for (i = 0; i < plane->plane->count_formats; i++) {
		//LOGD("DRM Support fromat %s\n", HexStringToAscii((const char*)&plane->plane->formats[i], 4));
	}

	for (i = 0; i < plane->plane->count_formats; i++) {
		if (plane->plane->formats[i] == format) {
			return 1;
		}
	}
	return 0;
}

static int get_supported_format(struct sp_plane* plane, uint32_t* format)
{
    uint32_t i;

    for (i = 0; i < plane->plane->count_formats; i++) {
        if (plane->plane->formats[i] == DRM_FORMAT_XRGB8888 || plane->plane->formats[i] == DRM_FORMAT_ARGB8888 || plane->plane->formats[i] == DRM_FORMAT_RGBA8888) {
            *format = plane->plane->formats[i];
            return 0;
        }
    }
    LOGI("No suitable formats found!\n");
    return -ENOENT;
}

struct sp_dev* create_sp_dev(void)
{
    struct sp_dev* dev;
    int ret, fd, i, j;
    drmModeRes* modeRes = NULL;
    drmModePlaneRes* planeRes = NULL;

    fd = open("/dev/dri/card0", O_RDWR | O_CLOEXEC);
    if (fd < 0) {
        LOGE("failed to open card0\n");
        return NULL;
    }

    dev = (struct sp_dev*)calloc(1, sizeof(*dev));
    if (!dev) {
        LOGE("failed to allocate dev\n");
        return NULL;
    }

    dev->fd = fd;

    ret = drmSetClientCap(dev->fd, DRM_CLIENT_CAP_ATOMIC, 1);
    if (ret) {
        LOGE("failed to set client cap atomic\n");
        goto err;
    }
    ret = drmSetClientCap(dev->fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 1);
    if (ret) {
        LOGE("failed to set client cap\n");
        goto err;
    }

    modeRes = drmModeGetResources(dev->fd);
    if (!modeRes) {
        LOGE("failed to get modeResources\n");
        goto err;
    }

    dev->num_connectors = modeRes->count_connectors;
    dev->connectors = (drmModeConnectorPtr*)calloc(dev->num_connectors, sizeof(*dev->connectors));
    // TODO: We are going to use just first mode because the first one has the highest resolution.
    dev->modes = (drmModeModeInfo*)calloc(dev->num_connectors, sizeof(drmModeModeInfo));

    LOGD("[DEBUG %s:%d] DRM # of Connector = %d\n", __func__, __LINE__, dev->num_connectors);
    
    if (!dev->connectors) {
        LOGE("failed to allocate connectors\n");
        goto err;
    }
    for (i = 0; i < dev->num_connectors; i++) {
        dev->connectors[i] = drmModeGetConnector(dev->fd,
                                                 modeRes->connectors[i]);
        if (!dev->connectors[i]) {
            LOGE("failed to get connector %d\n", i);
            goto err;
        }

        if (dev->connectors[i]->connection != DRM_MODE_CONNECTED) {
            LOGW("DRM Connector %i is not connected to Display\n", i);
        }
        else {
            LOGD("DRM Connector[%i] %d is onnected to Display\n", i, dev->connectors[i]->connector_id);
        }
#if 1
        /* check if there is at least one valid mode */
        if (dev->connectors[i]->count_modes == 0) {
            LOGE("no valid mode for connector %u\n", dev->connectors[i]->connector_id);
        }
        else {
            if (dev->modes) {
                LOGD("DRM Connector %d has the number of %d modes\n", dev->connectors[i]->connector_id, dev->connectors[i]->count_modes);
                memcpy((uint8_t *)&dev->modes[i], (uint8_t *)&dev->connectors[i]->modes[0], sizeof(drmModeModeInfo));
            }
        }

        if (dev->modes) {
            LOGI("DRM connector[%d] mode name %s,hdisplay %d, vdisplay %d, vrefresh %d, type=%d\n",
               i, dev->modes[i].name, dev->modes[i].hdisplay, dev->modes[i].vdisplay, dev->modes[i].vrefresh, dev->modes[i].type);
        }
#endif
    }

    dev->num_encoders = modeRes->count_encoders;
    dev->encoders = (drmModeEncoderPtr*)calloc(dev->num_encoders, sizeof(*dev->encoders));
    if (!dev->encoders) {
        LOGE("failed to allocate encoders\n");
        goto err;
    }
    for (i = 0; i < dev->num_encoders; i++) {
        dev->encoders[i] = drmModeGetEncoder(dev->fd, modeRes->encoders[i]);
        if (!dev->encoders[i]) {
            LOGE("failed to get encoder %d\n", i);
            goto err;
        }
    }
    LOGD("DRM # of Endoder = %d\n", dev->num_encoders);

    /*
     * A CRTC represents the overall display pipeline. 
     * It receives pixel data from drm_plane and blends them together.
     * The drm_display_mode is also attached to the CRTC, 
     * specifying display timings. On the output side the data is fed to one or more drm_encoder, 
     * which are then each connected to one drm_connector.
     */

    dev->num_crtcs = modeRes->count_crtcs;
    dev->crtcs = (struct sp_crtc*)calloc(dev->num_crtcs, sizeof(struct sp_crtc));
    if (!dev->crtcs) {
        LOGE("failed to allocate crtcs\n");
        goto err;
    }
    for (i = 0; i < dev->num_crtcs; i++) {
        dev->crtcs[i].crtc = drmModeGetCrtc(dev->fd, modeRes->crtcs[i]);
        if (!dev->crtcs[i].crtc) {
            LOGE("failed to get crtc %d\n", i);
            goto err;
        }
        dev->crtcs[i].scanout = NULL;
        dev->crtcs[i].pipe = i;
        dev->crtcs[i].num_planes = 0;
        dev->crtcs[i].valid = 0;
    }
    LOGD("DRM # of CRTC = %d\n", dev->num_crtcs);

    planeRes = drmModeGetPlaneResources(dev->fd);
    if (!planeRes) {
        LOGE("failed to get plane resources\n");
        goto err;
    }
    
    dev->num_planes = planeRes->count_planes;
    LOGD("DRM # of PLANES = %d\n", dev->num_planes);
    
    dev->planes = (struct sp_plane*)calloc(dev->num_planes, sizeof(struct sp_plane));
    for (i = 0; i < dev->num_planes; i++) {
        drmModeObjectPropertiesPtr props;
        struct sp_plane* plane = &dev->planes[i];

        plane->dev = dev;
        plane->plane = drmModeGetPlane(dev->fd, planeRes->planes[i]);
        if (!plane->plane) {
            LOGE("failed to get plane %d\n", i);
            goto err;
        }
        plane->bo = NULL;
        plane->in_use = 0;

        ret = get_supported_format(plane, &plane->format);
        if (ret) {
            LOGE("failed to get supported format: %d\n", ret);
            goto err;
        }

        for (j = 0; j < dev->num_crtcs; j++) {
            if (plane->plane->possible_crtcs & (1 << j))
                dev->crtcs[j].num_planes++;
        }

        props = drmModeObjectGetProperties(dev->fd, planeRes->planes[i],	DRM_MODE_OBJECT_PLANE);
        if (!props) {
            LOGE("failed to get plane properties\n");
            goto err;
        }

        if (props->count_props > 0) {
            for (j = 0; j < (int)props->count_props; j++) {
                drmModePropertyPtr p = drmModeGetProperty(dev->fd, props->props[j]);
                if (i==0) {
                    LOGD("DRM Plane[%d] Property=%d, name %s, id %d\n", i, j, p->name, p->prop_id);
                }
                drmModeFreeProperty(p);
            }
        }
    }

    if (planeRes)
        drmModeFreePlaneResources(planeRes);
    if (modeRes)
        drmModeFreeResources(modeRes);
    return dev;
err:
    if (planeRes)
        drmModeFreePlaneResources(planeRes);
    if (modeRes)
        drmModeFreeResources(modeRes);
    destroy_sp_dev(dev);
    return NULL;
}

void destroy_sp_dev(struct sp_dev* dev)
{
    int i;

    if (dev->planes) {
        for (i = 0; i < dev->num_planes; i++) {
            if (dev->planes[i].in_use)
                put_sp_plane(&dev->planes[i]);
            if (dev->planes[i].plane)
                drmModeFreePlane(dev->planes[i].plane);
            if (dev->planes[i].bo)
                free_sp_bo(dev->planes[i].bo);
        }
        free(dev->planes);
    }
    if (dev->crtcs) {
        for (i = 0; i < dev->num_crtcs; i++) {
            if (dev->crtcs[i].crtc)
                drmModeFreeCrtc(dev->crtcs[i].crtc);
            if (dev->crtcs[i].scanout)
                free_sp_bo(dev->crtcs[i].scanout);
        }
        free(dev->crtcs);
    }
    if (dev->encoders) {
        for (i = 0; i < dev->num_encoders; i++) {
            if (dev->encoders[i])
                drmModeFreeEncoder(dev->encoders[i]);
        }
        free(dev->encoders);
    }
    if (dev->connectors) {
        for (i = 0; i < dev->num_connectors; i++) {
            if (dev->connectors[i])
                drmModeFreeConnector(dev->connectors[i]);
        }
        free(dev->connectors);
    }

    close(dev->fd);
    free(dev);
}
