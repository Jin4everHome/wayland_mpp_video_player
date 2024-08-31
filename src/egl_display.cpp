#define GL_GLEXT_PROTOTYPES   1
#define EGL_EGLEXT_PROTOTYPES 1
#include "config.h"


#include <string.h>
#include <errno.h>

#include <drm/drm_fourcc.h>

#include "helpers.h"
#include "platform.h"
#include "weston-egl-ext.h"

#include "egl_display.h"

#include "linmath.h"

#include <wayland-client.h>
#include "xdg-shell-client-protocol.h"

#include "log.h"
#include "system_time.h"

/* Measure EGL swapbuffer time */
#define __DEBUG_SWAPBUFFER_DURATION__ 1

namespace {

const int kBlitPositionAttribute = 0;
const int kBlitTexcoordAttribute = 1;

const char* vert_shader_text =
	"attribute vec3 a_position;"
	"attribute vec2 a_tex_coord;"
	"varying vec2 v_tex_coord_rgba;"
	"uniform vec4 scale_translate_rgba;"
	"uniform mat4 model_view_projection_transform;"
	"void main() {"
	"  gl_Position = model_view_projection_transform * vec4(a_position.xyz, 1.0);"
	"  v_tex_coord_rgba = a_tex_coord * scale_translate_rgba.xy + scale_translate_rgba.zw;"
	"}";

const char* frag_shader_text =
	"#extension GL_OES_EGL_image_external : require\n"
	"precision mediump float;"
	"varying vec2 v_tex_coord_rgba;"
	"uniform samplerExternalOES texture_rgba;"
	"void main() {"
	"  vec4 untransformed_color = vec4(texture2D(texture_rgba, v_tex_coord_rgba).rgba);"
	"  gl_FragColor = untransformed_color;"
	"}";

#if 1 // Full Screen Example
static float vertices[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom left 
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // top left
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // top left
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
        1.0f, 1.0, 0.0f, 1.0f, 1.0f,    // top right;
};
#else
        // one quard screen @ Right Bottom Example
static float vertices[] = {
        0.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // bottom left
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // top left
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // top left
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
        1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right;
};
#endif

static float  scale_translate_vector[4] =
{
        1.0f, -1.0f, 0.0f, 1.0f
};

static unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3, // second triangle 
};

void xdg_wm_base_ping(void *data, struct xdg_wm_base *shell, uint32_t serial)
{
	LOGD("XDG_WM_BASE PING/PONG\n");
	xdg_wm_base_pong(shell, serial);
}

const struct xdg_wm_base_listener wm_base_listener = {
     xdg_wm_base_ping,
};

void registry_handle_global(void *data, struct wl_registry *registry,
                       uint32_t name, const char *interface, uint32_t version)
{
	EGLDisplayOut *dispObj = static_cast<EGLDisplayOut *>(data);

	LOGD("CTX=%p registry_handle_global interface %s, version=%u, name=%u\n", dispObj, interface, version, name);
	if (dispObj) {
		if (strcmp(interface, "wl_compositor") == 0) {
			LOGI("BIND interface %s\n", interface);
			if (!dispObj->GetCompositor()) {
			    dispObj->SetCompositor((wl_compositor *)wl_registry_bind(registry, name, &wl_compositor_interface, MIN(version, 4)));
			}
		}
		else if (strcmp(interface, "xdg_wm_base") == 0) {
			LOGI("BIND interface %s\n", interface);
			dispObj->mWMBase = (xdg_wm_base*)wl_registry_bind(registry, name,  &xdg_wm_base_interface, 1);
			xdg_wm_base_add_listener(dispObj->mWMBase, &wm_base_listener, (void *)dispObj);
		}
		else if (strcmp(interface, "wl_seat") == 0) {
			//dispObj->SetSeat((struct wl_seat*)wl_registry_bind(registry, name, &wl_seat_interface, 1));
			//wl_seat_add_listener(dispObj->GetSeat(), &seat_listener, dispObj);
		}

		if (strcmp(interface, "wl_shell") == 0) {
			LOGI("BIND interface %s\n", interface);
			if (!dispObj->GetShell()) {
				dispObj->SetShell((wl_shell*)wl_registry_bind(registry, name, &wl_shell_interface, 1));
			}
		}
	}
}

void registry_handle_global_remove(void *data, struct wl_registry *registry,
                              uint32_t name)
{
}

struct wl_registry_listener registry_listener =
{
        &registry_handle_global,
        &registry_handle_global_remove
};

static void shell_surface_ping (
        void *data,
        struct wl_shell_surface *shell_surface,
        uint32_t serial)
{
    printf(">>>>> Shell Surface Ping >>>>>>>>>\n");
    wl_shell_surface_pong (shell_surface, serial);
}

static void shell_surface_configure (
        void *data,
        struct wl_shell_surface *shell_surface,
        uint32_t edges,
        int32_t width,
        int32_t height)
{
	EGLDisplayOut *dispObj = static_cast<EGLDisplayOut *>(data);

	printf(">>>>> Shell Surface Configure >>>>>>>>>\n");

	if (dispObj) {
		if (width && height) {
			LOGD(">>>>> ShellSurfaceConfigure: window width=%d, height=%d\n",width, height);
			if (dispObj->GetWLEGLWindow()) {
				dispObj->SetGeomertyWindowSize(width, height);
				wl_egl_window_resize (dispObj->GetWLEGLWindow(), width, height, 0, 0);
			}
			else {
				LOGE("No egl_window exist\n");
			}
		}
		else {
			printf("Invalid width or height got. we don't resize that");
		}

		dispObj->WaitConfigureDone();
	}
}

static void shell_surface_popup_done (void *data, struct wl_shell_surface *shell_surface)
{

}

static struct wl_shell_surface_listener shell_surface_listener =
{
        &shell_surface_ping,
        &shell_surface_configure,
        &shell_surface_popup_done
};


void handle_surface_configure(void *data, struct xdg_surface *surface,
                         uint32_t serial)
{
	EGLDisplayOut *dispObj = static_cast<EGLDisplayOut *>(data);

	xdg_surface_ack_configure(surface, serial);
	LOGD("EGL display configured\n");

	if (dispObj) {
		dispObj->WaitConfigureDone();
	}
	else {
		LOGE("Callback doesn't have context\n");
	}
}

const struct xdg_surface_listener xdg_surface_listener_ = {
        handle_surface_configure
};

void handle_toplevel_configure(void *data, struct xdg_toplevel *toplevel,
                          int32_t width, int32_t height,
                          struct wl_array *states)
{
	EGLDisplayOut *dispObj = static_cast<EGLDisplayOut *>(data);
	void *p;

	wl_array_for_each(p, states) {
		uint32_t state = *(uint32_t *)p;
		switch (state) {
			case XDG_TOPLEVEL_STATE_FULLSCREEN:
				LOGD("XDG_TOPLEVEL_STATE_FULLSCREEN\n");
				dispObj->mIsFullScreenMode = true;
				break;
			case XDG_TOPLEVEL_STATE_MAXIMIZED:
				LOGD("XDG_TOPLEVEL_STATE_MAXIMIZED\n");
				dispObj->mIsMaximizeMode = true;
				break;
		}
	}

	if (width > 0 && height > 0) {
		if (!dispObj->mIsFullScreenMode && !dispObj->mIsMaximizeMode) {
			dispObj->mWindowSize.width  = width;
			dispObj->mWindowSize.height = height;
		}
		
		dispObj->mGeometry.width  = width;
		dispObj->mGeometry.height = height;
	}
	else if(!dispObj->mIsFullScreenMode && !dispObj->mIsMaximizeMode) {
		dispObj->mGeometry = dispObj->mWindowSize;
	}
	else {
		LOGE("Failed to set geometry\n");
	}

	LOGD("EGL Geometry SET W:H = %d:%d\n", dispObj->mGeometry.width, dispObj->mGeometry.height);

	if (dispObj->GetWLEGLWindow()) {
		Geometry geo = dispObj->GetGeoMetry();
		wl_egl_window_resize(dispObj->GetWLEGLWindow(),
		                     dispObj->mGeometry.width,
		                     dispObj->mGeometry.height,
		                     0, 0);
	}
}

void handle_toplevel_close(void *data, struct xdg_toplevel *xdg_toplevel)
{
	EGLDisplayOut *dispObj = static_cast<EGLDisplayOut *>(data);
	LOGD("EGLDisplay toplevel closed\n");

	if (dispObj) {
		dispObj->mRunning = false;
	}
	else {
		LOGE("Found no handle\n");
	}
}

const struct xdg_toplevel_listener xdg_toplevel_listener_ = {
	handle_toplevel_configure,
	handle_toplevel_close,
};


} // namespace


EGLDisplayOut::EGLDisplayOut()
	:mBufferCnt(MAX_BUFFER_COUNT),
	 mBufferSize(0),
	 mWLDisplay(nullptr),
	 mWLRegistry(nullptr),
	 mWLCompositor(nullptr),
	 mWLShell(nullptr),
	 mWLSeat(nullptr),
	 mWLKeyboard(nullptr),
	 mWLSurface(nullptr),
	 mWLShellSurface(nullptr),
	 mWLEGLWindow(nullptr)
{
	mGeometry.width = 1920;
	mGeometry.height = 1024;
}

EGLDisplayOut::EGLDisplayOut(int numBuffer)
	:mBufferCnt(numBuffer),
	 mBufferSize(0),
	 mWLDisplay(nullptr),
	 mWLRegistry(nullptr),
	 mWLCompositor(nullptr),
	 mWLShell(nullptr),
	 mWLSeat(nullptr),
	 mWLKeyboard(nullptr),
	 mWLSurface(nullptr),
	 mWLShellSurface(nullptr),
	 mWLEGLWindow(nullptr)
{
	mGeometry.width = 1920;
	mGeometry.height = 1024;
}

EGLDisplayOut::~EGLDisplayOut()
{
	deinitDisplayInternal();
}

int EGLDisplayOut::initDisplay(int width, int height, int numOfBuffer)
{
	EGLBoolean ret;

	mWindowSize.width = width;
	mWindowSize.height = height;

	if (numOfBuffer > 0) {
		mBufferCnt = numOfBuffer;
	}

	/* Connect display */
	mWLDisplay = wl_display_connect(NULL);
	mWLRegistry = wl_display_get_registry(mWLDisplay);

	if (!mWLDisplay || !mWLRegistry) {
		LOGE("Westion display connection failed\n");
		return -1;
	}
	
	/* add global listener */
	wl_registry_add_listener (mWLRegistry, &registry_listener,  (void *)this); //TODO:
	wl_display_roundtrip(mWLDisplay);

	if (initEGL()) {
		LOGE("initEGL() failed\n");
		return -1;
	}

	createShellSurface();
	eglSwapInterval(mEGLDisplay, 0);
	mWaitForConfigure = true;

	if (initGL()) {
		LOGE("initGL() failed\n");
		return -1;
	}

	for (int i=0; i < mBufferCnt; i++) {
		mEGLImage[i] = EGL_NO_IMAGE_KHR;
		mTextureID[i] = 0xFFFFFFFF;
		last_resolution_[i] = 0;
	}

	mGLInitDone = true;
	mRunning = true;

	return 0;
}

int EGLDisplayOut::Render(MppFrame frame)
{
	int i = 0, ret = 0;

	if (!frame) {

		LOGE("Invalid null point paramter\n");
		return -1;
	}

	if (!mWLDisplay) {
		LOGD("Westion display not yet prepared\n");
		return -1;
	}

	if (mGLInitDone) {
		if (mWaitForConfigure) {
			ret = wl_display_dispatch(mWLDisplay);
			//mWaitForConfigure = false;
		}
		else {
			wl_display_dispatch_pending(mWLDisplay);
			ret = RenderInternal(frame);
			if (ret) {
				LOGE("Render EGL image failed\n");
				return -1;
			}
		}
	}
	else {
		if (mWaitForConfigure) {
			wl_display_dispatch_pending (mWLDisplay);
		}
		else {
			wl_display_dispatch_pending (mWLDisplay);
			//drawTest();
		}
	}

	return 0;
}

int EGLDisplayOut::deinitDisplay()
{
	deinitDisplayInternal( );

	return 0;
}

void EGLDisplayOut::SetCompositor(struct wl_compositor * compositor)
{
	mWLCompositor = compositor;
}

void EGLDisplayOut::SetShell(struct wl_shell * shell)
{
	mWLShell = shell;
}

void EGLDisplayOut::SetGeomertyWindowSize(int width, int height)
{
	mGeometry.width = width;
	mGeometry.height = height;
}

/* Private */
int EGLDisplayOut::RenderInternal(MppFrame frame)
{
	uint32_t new_res = 0;
	int i = 0, ret = 0;

	uint32_t width, height;
	uint32_t strideW, strideH;
	MppBuffer mpp_buf;
	int mpp_buf_index;
	int mpp_buf_fd;

	EGLint img_attrs[] =
	{
			EGL_WIDTH, 0,
			EGL_HEIGHT, 0,
			EGL_LINUX_DRM_FOURCC_EXT, 0,
			EGL_DMA_BUF_PLANE0_FD_EXT, 0,
			EGL_DMA_BUF_PLANE0_OFFSET_EXT, 0,
			EGL_DMA_BUF_PLANE0_PITCH_EXT, 0,
			EGL_DMA_BUF_PLANE1_FD_EXT, 0,
			EGL_DMA_BUF_PLANE1_OFFSET_EXT, 0, // NV12
			EGL_DMA_BUF_PLANE1_PITCH_EXT, 0,
			EGL_YUV_COLOR_SPACE_HINT_EXT, EGL_ITU_REC709_EXT,   // EGL_ITU_REC601_EXT , EGL_ITU_REC709_EXT , // EGL_ITU_REC2020_EXT
			EGL_SAMPLE_RANGE_HINT_EXT, EGL_YUV_NARROW_RANGE_EXT, // EGL_YUV_NARROW_RANGE_EXT , // EGL_YUV_FULL_RANGE_EXT creates a "washed out" picture
			EGL_YUV_CHROMA_HORIZONTAL_SITING_HINT_EXT, EGL_YUV_CHROMA_SITING_0_5_EXT,
			EGL_YUV_CHROMA_VERTICAL_SITING_HINT_EXT, EGL_YUV_CHROMA_SITING_0_5_EXT,
			EGL_NONE
	};

	GL_CALL(glActiveTexture(GL_TEXTURE0));

	for (i=0; i<mBufferCnt; i++)
	{
		/* Make sure no TextureID alloacted */
		if (mTextureID[i] != 0xFFFFFFFF)
			break;

		if (i == mBufferCnt - 1) {
			int n;
			GL_CALL(glGenTextures(mBufferCnt, &mTextureID[0]));

			for (int n=0; n < mBufferCnt; n++) {
				LOGI("Create TextureID[%d] = %d\n", n, mTextureID[n]);
			}
		}
	}

	mpp_buf = mpp_frame_get_buffer(frame);
	if (!mpp_buf) {
		LOGE("Unalbe to get decoder buffer\n");
		return -1;
	}

	mpp_buf_index = mpp_buffer_get_index(mpp_buf);
	if (mpp_buf_index < 0) {
		LOGE("Decoder buffer index(%d) is wrong\n", mpp_buf_index);
		return -1;
	}

	mpp_buf_fd = mpp_buffer_get_fd(mpp_buf);
	if (mpp_buf_fd < 0) {
		LOGE("Decoder buffer fd(%d) is wrong\n", mpp_buf_fd);
		return -1;
	}

	width   = mpp_frame_get_width(frame);
	height  = mpp_frame_get_height(frame);
	strideW = mpp_frame_get_hor_stride(frame);
	strideH = mpp_frame_get_ver_stride(frame);

	new_res = ((width<<16) | height);

	if (new_res != last_resolution_[mpp_buf_index]) {
		last_resolution_[mpp_buf_index] = new_res;
		/* Create Image */
		img_attrs[1] = width;
		img_attrs[3] = height;
		img_attrs[5] = DRM_FORMAT_NV12;
		img_attrs[7] = mpp_buf_fd;
		img_attrs[9] = 0;
		img_attrs[11] = strideW; // or display geometry width ??? (EGL_DMA_BUF_PLANE0_PITCH_EXT)
		img_attrs[13] = mpp_buf_fd; // EGL_DMA_BUF_PLANE1_FD_EXT
		img_attrs[15] = strideW * strideH; // For NV12, EGL_DMA_BUF_PLANE1_OFFSET_EXT
		img_attrs[17] = strideW; // EGL_DMA_BUF_PLANE1_PITCH_EXT
		// TODO: 
		// EGL_YUV_COLOR_SPACE_HINT_EXT =  EGL_ITU_REC601_EXT , EGL_ITU_REC709_EXT , EGL_ITU_REC2020_EXT 
		img_attrs[19] = EGL_ITU_REC2020_EXT;
		img_attrs[21] = EGL_YUV_NARROW_RANGE_EXT; //EGL_YUV_NARROW_RANGE_EXT, EGL_YUV_FULL_RANGE_EXT creates a "washed out" picture
		img_attrs[23] = EGL_YUV_CHROMA_SITING_0_5_EXT; // EGL_YUV_CHROMA_HORIZONTAL_SITING_HINT_EXT : NV12 
		img_attrs[25] = EGL_YUV_CHROMA_SITING_0_5_EXT; // EGL_YUV_CHROMA_VERTICAL_SITING_HINT_EXT : NV12

		if (mEGLImage[mpp_buf_index] != EGL_NO_IMAGE_KHR) {
			eglDestroyImageKHR(eglGetCurrentDisplay(), mEGLImage[mpp_buf_index]);
		}

		mEGLImage[mpp_buf_index] = eglCreateImageKHR(
			eglGetCurrentDisplay(),
			EGL_NO_CONTEXT,
			EGL_LINUX_DMA_BUF_EXT,
			0,
			img_attrs);

		if (eglGetError() != EGL_SUCCESS)
		{
			LOGE("eglCreateImageKHR failed\n");
			return -1;
		}

		if (mEGLImage[mpp_buf_index] == EGL_NO_IMAGE_KHR) {
			LOGE("Failed to create image\n");
			return -1;
		}

		LOGI("EGLImage[%d] : eglCreateImageKHR (W:H=%d:%d, fd=%d)\n", mpp_buf_index, width, height, mpp_buf_fd);
	}

	GL_CALL(glBindTexture(GL_TEXTURE_EXTERNAL_OES, mTextureID[mpp_buf_index]));
	GL_CALL(glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GL_CALL(glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GL_CALL(glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL_CALL(glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GL_CALL(glEGLImageTargetTexture2DOES(GL_TEXTURE_EXTERNAL_OES, (GLeglImageOES)mEGLImage[mpp_buf_index]));

	ret = DrawFrame(mpp_buf_index);
	if (ret) {
		LOGE("Failed to draw a EGLImage frame\n");
		return -1;
	}

	return 0;
}

int EGLDisplayOut::DrawFrame(int index)
{
	mat4x4 model_view_projection_matrix;
	mat4x4_identity(model_view_projection_matrix);
	EGLint buffer_age = 0;

#if 0
	const GLfloat kVertexInformation[] = {
		-1.0f, 1.0f,	   // TexCoord 0 top left
		-1.0f,-1.0f,	   // TexCoord 1 bottom left
		1.0f,-1.0f, 	   // TexCoord 2 bottom right
		1.0f, 1.0f	   // TexCoord 3 top right
	};

	const GLshort kTextureCoordinateInformation[] = {
		0, 0,		   // TexCoord 0 top left
		0, 1,		   // TexCoord 1 bottom left
		1, 1,		   // TexCoord 2 bottom right
		1, 0		        // TexCoord 3 top right
	};
	
	const GLshort kIndicesInformation[] = {
		0, 1, 2,
		0, 2, 3
	};
#endif

	// This may be the first use of the render target, so ensure it is bound.
	//GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));

	if (mSwapBuffersWithDamage) {
		eglQuerySurface(mEGLDisplay, mEGLSurface, EGL_BUFFER_AGE_EXT, &buffer_age);
	}

	// We setup our viewport to fill the entire canvas.
	GL_CALL(glViewport(0, 0, mGeometry.width, mGeometry.height));
	GL_CALL(glScissor(0, 0, mGeometry.width, mGeometry.height));

	GL_CALL(glUseProgram(mGL.program));

	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, mGL.vbo));
	GL_CALL(glVertexAttribPointer(kBlitPositionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0));
	GL_CALL(glVertexAttribPointer(kBlitTexcoordAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)(sizeof(float) * 3)));
	GL_CALL(glEnableVertexAttribArray(kBlitPositionAttribute));
	GL_CALL(glEnableVertexAttribArray(kBlitTexcoordAttribute));
	
	GL_CALL(glUniformMatrix4fv(mGL.mvp_transform_uniform, 1, GL_FALSE, (GLfloat *)model_view_projection_matrix));

	GL_CALL(glActiveTexture(GL_TEXTURE0));
	GL_CALL(glBindTexture(GL_TEXTURE_EXTERNAL_OES, mTextureID[index]));
	GL_CALL(glUniform1i(mGL.texture_uniforms, 0));
	GL_CALL(glUniform4fv(mGL.texcoord_scale_translate_uniforms, 1, scale_translate_vector));
	GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 6));

#if __DEBUG_SWAPBUFFER_DURATION__
	debug_time_ = getSystemTimeNow();
	debug_test_count_++;
#endif
	EGL_CALL(eglSwapBuffers(mEGLDisplay, mEGLSurface));

#if __DEBUG_SWAPBUFFER_DURATION__
			debug_time_ = getSystemTimeNow() - debug_time_;
			debug_totoal_duration_ += debug_time_;
			debug_average_duration_  = debug_totoal_duration_/debug_test_count_;

			LOGD("EGL SWAP TIME : %lld usec (accum=%lld, average=%lld)\n",
				debug_time_,
				debug_totoal_duration_,
				debug_average_duration_);
#endif

	GL_CALL(glBindTexture(GL_TEXTURE_EXTERNAL_OES, 0));
	GL_CALL(glDisableVertexAttribArray(kBlitTexcoordAttribute));
	GL_CALL(glDisableVertexAttribArray(kBlitPositionAttribute));
	GL_CALL(glUseProgram(0));

	//GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	return 0;
}

int EGLDisplayOut::deinitDisplayInternal()
{
	deinitGL();
	deinitEGL();
	deinitWL();

	if (mWLRegistry) {
		wl_registry_destroy(mWLRegistry);
		mWLRegistry = nullptr;
	}

	if (mWLDisplay) {
		wl_display_flush(mWLDisplay);
		wl_display_disconnect(mWLDisplay);
		mWLDisplay = nullptr;
	}

	return 0;
}

int EGLDisplayOut::initEGL()
{
	if (!mWLDisplay) {
		LOGE("Invalid null display\n");
		return -1;
	}

	static const struct {
			//char *extension, *entrypoint;
			const char *extension, *entrypoint; // fix warning
	} swap_damage_ext_to_entrypoint[] = {
		{
			.extension = "EGL_EXT_swap_buffers_with_damage",
			.entrypoint = "eglSwapBuffersWithDamageEXT",
		},
		{
			.extension = "EGL_KHR_swap_buffers_with_damage",
			.entrypoint = "eglSwapBuffersWithDamageKHR",
		},
	};

	static const EGLint context_attribs[] = {
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};
	const char *extensions;

	EGLint config_attribs[] = {
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_RED_SIZE, 1,
		EGL_GREEN_SIZE, 1,
		EGL_BLUE_SIZE, 1,
		EGL_ALPHA_SIZE, 1,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_NONE
	};

	EGLint major, minor, n, count, i;
	EGLConfig *configs;
	EGLBoolean ret;

	//if (window->opaque || window->buffer_size == 16)
	//	config_attribs[9] = 0;

	mEGLDisplay = weston_platform_get_egl_display(EGL_PLATFORM_WAYLAND_KHR, mWLDisplay, NULL);
	//mEGLDisplay = eglGetDisplay(mWLDisplay);
	if (mEGLDisplay == EGL_NO_DISPLAY) {
		LOGE("Unable to get an EGLDisplay\n");
		return -1;
	}

	ret = eglInitialize(mEGLDisplay, NULL, NULL);
	if (ret != EGL_TRUE) {
		LOGE("Call eglInitialize failed\n", __func__, __LINE__);
		return -1;
	}
	
	ret = eglBindAPI(EGL_OPENGL_ES_API /*EGL_OPENGL_API*/);
	if (ret != EGL_TRUE) {
		LOGE("Call eglBindAPI failed\n");
		return -1;
	}

	if (!eglGetConfigs(mEGLDisplay, NULL, 0, &count) || count < 1) {
		assert(0);
	}

	configs = (EGLConfig *)calloc(count, sizeof *configs);
	if (!configs) {
		LOGE("Failed to allocate a memory\n");
		return -1;
	}

	ret = eglChooseConfig(mEGLDisplay, config_attribs, configs, count, &n);
	assert(ret && n >= 1);

	for (i = 0; i < n; i++) {
		EGLint buffer_size, red_size;
		eglGetConfigAttrib(mEGLDisplay,
		                   configs[i], EGL_BUFFER_SIZE, &buffer_size);
		eglGetConfigAttrib(mEGLDisplay,
		                   configs[i], EGL_RED_SIZE, &red_size);

		LOGD("EGL Get config buffer_size=%d, red_size=%d\n", buffer_size, red_size);
		if (red_size < 10) {
			mEGLConfig = configs[i];
			break;
		}
		break;
	}
	free(configs);

	mEGLContext = eglCreateContext(mEGLDisplay, mEGLConfig, EGL_NO_CONTEXT, context_attribs);
	if (eglGetError() != EGL_SUCCESS || !mEGLContext) {
		LOGE("Unable to create egl context\n");
		return -1;
	}

	mSwapBuffersWithDamage = nullptr;
	extensions = eglQueryString(mEGLDisplay, EGL_EXTENSIONS);

	if (extensions &&	weston_check_egl_extension(extensions, "EGL_EXT_buffer_age")) {
		for (i = 0; i < (int) ARRAY_LENGTH(swap_damage_ext_to_entrypoint); i++) {
			if (weston_check_egl_extension(extensions,  swap_damage_ext_to_entrypoint[i].extension)) {
				/* The EXTPROC is identical to the KHR one */
				mSwapBuffersWithDamage =
					(PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC)
					eglGetProcAddress(swap_damage_ext_to_entrypoint[i].entrypoint);
				break;
			}
		}
	}

	if (mSwapBuffersWithDamage) {
		LOGD("EGL Has EGL_EXT_buffer_age extenstion\n");
	}

	return 0;
}

int EGLDisplayOut::deinitEGL()
{
	if (mEGLDisplay != EGL_NO_DISPLAY) {
		/* Required, otherwise segfault in egl_dri2.c: dri2_make_current()
		* on eglReleaseThread(). */
		eglMakeCurrent(mEGLDisplay, EGL_NO_DISPLAY/*EGL_NO_SURFACE*/, EGL_NO_SURFACE, EGL_NO_CONTEXT);

		// Distory egl surface
		if (mEGLSurface != EGL_NO_SURFACE) {
			eglDestroySurface (mEGLDisplay, mEGLSurface);
			mEGLSurface = EGL_NO_SURFACE;
		}

		if (mEGLContext != EGL_NO_CONTEXT) {
			eglDestroyContext(mEGLDisplay, mEGLContext);
			mEGLContext = EGL_NO_CONTEXT;
		}

		eglTerminate(mEGLDisplay);
		mEGLDisplay = EGL_NO_DISPLAY;
	}

	return 0;
}

int EGLDisplayOut::deinitWL( )
{
	if (mWLEGLWindow) {
		wl_egl_window_destroy(mWLEGLWindow);
		mWLEGLWindow = nullptr;
	}

	if (mWLShellSurface) {
		wl_shell_surface_destroy(mWLShellSurface);
		mWLShellSurface = nullptr;
	}

	if (mWLSurface) {
		wl_surface_destroy(mWLSurface);
		mWLSurface = nullptr;
	}

	if (mWMBase) {
		xdg_wm_base_destroy(mWMBase);
		mWMBase = nullptr;
	}

	if (mWLCompositor) {
		wl_compositor_destroy(mWLCompositor);
		mWLCompositor = nullptr;
	}

	return 0;
}

int EGLDisplayOut::initGL()
{
	GLuint frag, vert;
	GLuint program;
	GLint status;

	mGL.vbo = getVBO();

	frag = createShader(frag_shader_text, GL_FRAGMENT_SHADER);
	vert = createShader(vert_shader_text, GL_VERTEX_SHADER);
	program = glCreateProgram();
	mGL.program = program;

	GL_CALL(glAttachShader(program, frag));
	GL_CALL(glAttachShader(program, vert));
	GL_CALL(glBindAttribLocation(program, kBlitPositionAttribute,"a_position"));
	GL_CALL(glBindAttribLocation(program, kBlitTexcoordAttribute,"a_tex_coord"));

	GL_CALL(glLinkProgram(program));
	
	// Should be argument of render()
	mGL.mvp_transform_uniform = glGetUniformLocation(program, "model_view_projection_transform");
	mGL.texcoord_scale_translate_uniforms = glGetUniformLocation(program, "scale_translate_rgba");
	mGL.texture_uniforms = glGetUniformLocation(program, "texture_rgba");

	GL_CALL(glGetProgramiv(program, GL_LINK_STATUS, &status));
	if (!status) {
		 char log[1000];
		 GLsizei len;
		 glGetProgramInfoLog(program, 1000, &len, log);
		 LOGE("Error: linking:\n%.*s\n", len, log);
		 return -1; // exit...
	}

	GL_CALL(glViewport(0, 0, mGeometry.width, mGeometry.height));
	GL_CALL(glUseProgram(0));

	GL_CALL(glDeleteShader(frag));
	GL_CALL(glDeleteShader(vert));

	return 0;
}

int EGLDisplayOut::deinitGL()
{
	if (mGL.vbo_valid) {
		glDeleteBuffers(1, &mGL.vbo);
		mGL.vbo_valid = false;
	}

	return 0;
}


int EGLDisplayOut::createShellSurface()
{

	EGLBoolean ret;

	if(!mWLCompositor) {
		LOGE("WL compositor is not initialized\n");
		return -1;
	}

	if(!mWMBase) {
		LOGE("Found no WM base\n");
		return -1;
	}

	mWLSurface = wl_compositor_create_surface(mWLCompositor);
	if (!mWLSurface) {
		LOGE("Unable to get WL surface\n");
		return -1;
	}
	// native
	mWLEGLWindow = wl_egl_window_create(mWLSurface, mGeometry.width, mGeometry.height);
	// eglCreateWindowSurface(mEGLDisplay, config, mWLEGLWindow, NULL);
	mEGLSurface = weston_platform_create_egl_surface(mEGLDisplay, mEGLConfig, mWLEGLWindow, NULL);

	mXDGSurface = xdg_wm_base_get_xdg_surface(mWMBase, mWLSurface);
	xdg_surface_add_listener(mXDGSurface, &xdg_surface_listener_, (void *)this);

	mXDGToplevel = xdg_surface_get_toplevel(mXDGSurface);
	xdg_toplevel_add_listener(mXDGToplevel, &xdg_toplevel_listener_, (void *)this);

	xdg_toplevel_set_title(mXDGToplevel, "MediaPlayer");
	//xdg_toplevel_set_app_id(mXDGToplevel, "org.freedesktop.weston.simple-egl");

	mWaitForConfigure = true;
	wl_surface_commit(mWLSurface);

	//EGL_CALL(eglMakeCurrent(mEGLDisplay, mEGLSurface, mEGLSurface, mEGLContext));
	ret = eglMakeCurrent(mEGLDisplay, mEGLSurface, mEGLSurface, mEGLContext);
	assert(ret == EGL_TRUE);

	if (!mWMBase) {

	}

	if (mIsFullScreenMode) {
		xdg_toplevel_set_fullscreen(mXDGToplevel, NULL);
	}

	return 0;
}

unsigned int EGLDisplayOut::getVBO()
{
	unsigned int vbo = 0;

	if (mGL.vbo_valid == 0) {
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		mGL.vbo_valid  = 1;
		mGL.vbo  = vbo;
	}
	
	return	vbo;
}

GLuint EGLDisplayOut::createShader(const char *source, GLenum shader_type)
{
	GLuint shader;
	GLint status;

	shader = glCreateShader(shader_type);
	if (shader == 0) {
		LOGE("Unable to create shader\n");
		return shader;
	}

	glShaderSource(shader, 1, (const char **)&source, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status) {
		char log[1000];
		GLsizei len;
		glGetShaderInfoLog(shader, 1000, &len, log);
		LOGE(" Error: compiling %s: %.*s\n",
			shader_type == GL_VERTEX_SHADER ? "vertex" : "fragment",
			len, log);
		return (GLuint)0;
	}

	return shader;
}

void EGLDisplayOut::drawTest()
{
	if (mRunning) {
		glClearColor (0.0, 1.0, mColor, 1.0);
		glClear (GL_COLOR_BUFFER_BIT);
		eglSwapBuffers (mEGLDisplay, mEGLSurface);
		mColor -= 0.2f;
		if (mColor < 0) {
			mColor = 1.0f;
		}
	}
}

