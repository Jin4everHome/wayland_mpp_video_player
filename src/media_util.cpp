#include <string.h>
#include <cmath>
#include "media_util.h"

#include "log.h"

#ifdef TAG
#undef TAG
#define TAG "MediaUtil"
#endif

namespace {
// TODO:
#define VID_HEADER_SIZE     8192
#define ADTS_HEADER_SIZE    7
#define FLAC_METADATA_HEAD_SIZE 4
#define FLAC_METADATA_STREAMINFO_SIZE 34

enum FLAC_BLOCK_TYPE
{
	FLAC_STREAMINFO = 0,
	FLAC_PADDING,
	FLAC_APPLICATION,
	FLAC_SEEKTABLE,
	FLAC_VORBIS_COMMENT,
	FLAC_CUESHEET,
	FLAC_PICTURE
};

typedef struct {
    unsigned short syncword;
    unsigned short aac_frame_length;
    unsigned short adts_buffer_fullness;

    unsigned char id: 1;
    unsigned char layer: 2;
    unsigned char protection_absent: 1;
    unsigned char profile: 2;
    unsigned char original_copy: 1;
    unsigned char home: 1;

    unsigned char sample_freq_idx: 4;
    unsigned char private_bit: 1;
    unsigned char channel_configuration: 3;

    unsigned char copyright_identification_bit: 1;
    unsigned char copyright_identification_start: 1;
    unsigned char number_of_raw_data_blocks_in_frame: 2;
} adts_header_t;

const uint32_t sample_rates[] = {
    96000, 88200, 64000, 48000, 44100, 32000,
    24000, 22050, 16000, 12000, 11025, 8000
    //,7350
};

const char* aac_encode_level[] = {
	"AAC UND",
	"AAC MAIN",
	"AAC LC",
	"AAC SSR",
	"AAC LTP",
	"AAC HE",
};

int check_size_in_buffer(unsigned char *p, int len)
{
    unsigned int size;
    unsigned char *q = p;
    while ((q + 4) < (p + len)) {
        size = (*q << 24) | (*(q + 1) << 16) | (*(q + 2) << 8) | (*(q + 3));
        if (size & 0xff000000) {
            return 0;
        }

        if (q + size + 4 == p + len) {
            return 1;
        }

        q += size + 4;
    }
    return 0;
}

int check_size_in_buffer3(unsigned char *p, int len)
{
    unsigned int size;
    unsigned char *q = p;
    while ((q + 3) < (p + len)) {
        size = (*q << 16) | (*(q + 1) << 8) | (*(q + 2));

        if (q + size + 3 == p + len) {
            return 1;
        }

        q += size + 3;
    }
    return 0;
}

int check_size_in_buffer2(unsigned char *p, int len)
{
    unsigned int size;
    unsigned char *q = p;
    while ((q + 2) < (p + len)) {
        size = (*q << 8) | (*(q + 1));

        if (q + size + 2 == p + len) {
            return 1;
        }

        q += size + 2;
    }
    return 0;
}

void flac_metablock_header(uint8_t *buf, int *isLastBlock, int *blockType, int *blockLen)
{
	int length = 0;
	*isLastBlock = buf[0]&0x1;
	*blockType = ((buf[0]>>1) & 0x7F);

	length = ((int)buf[3]&0xFF)<<16 | ((int)buf[2]&0xFF)<<8 | buf[1];

	*blockLen = length;
}

} // namespace

int MediaUtil::h264_add_header(AVCodecContext *pCodecCtx, uint8_t *buf)
{
    char nal_start_code[] = {0x0, 0x0, 0x0, 0x1};
    int nalsize;
    uint8_t* p;
    int tmpi;
    int header_len = 0;
    int size;

    if(!pCodecCtx->extradata) return 0;

    p = pCodecCtx->extradata;
    size = pCodecCtx->extradata_size;

    if (size > VID_HEADER_SIZE)
    {
        return 0;
    }

    if((p[0] == 0 && p[1] == 0 && p[2] == 0 && p[3] == 1) || (p[0] == 0 && p[1] == 0 && p[2] == 1) && size < VID_HEADER_SIZE)
    {
        memcpy(buf, p, size);
        header_len = size;
        return header_len;
    }
    if(size < 4)
    {
        return 0;
    }

    if(size < 10)
    {
        // avcC too short
        return 0;
    }

    if(*p != 1)
    {
        // Unkonwn avcC version
        return 0;
    }

    int cnt = *(p + 5) & 0x1f; //number of sps
    // printf("number of sps :%d\n", cnt);
    p += 6;
    for (tmpi = 0; tmpi < cnt; tmpi++)
    {
        nalsize = (*p << 8) | (*(p + 1));
        memcpy(&(buf[header_len]), nal_start_code, 4);
        header_len += 4;
        memcpy(&(buf[header_len]), p + 2, nalsize);
        header_len += nalsize;
        p += (nalsize + 2);
    }

    cnt = *(p++); //Number of pps
    // printf("number of pps :%d\n", cnt);
    for (tmpi = 0; tmpi < cnt; tmpi++)
    {
        nalsize = (*p << 8) | (*(p + 1));
        memcpy(&(buf[header_len]), nal_start_code, 4);
        header_len += 4;
        memcpy(&(buf[header_len]), p + 2, nalsize);
        header_len += nalsize;
        p += (nalsize + 2);
    }

    if (header_len >= VID_HEADER_SIZE)
    {
        return 0;
    }

    return header_len;
}

int MediaUtil::h264_check_header(uint8_t * buf,int size)
{
    int i , j;

    if(buf == nullptr || size < 0x10)
    {
        return -1;
    }

    for(i = 0; i < (size - 5); i++)
    {
        /* nal_ref_idc might not be always 2 (Not true -> buf[3 or 4] != 0x67)*/
        if ((buf[i] == 0 && buf[i + 1] == 0 && buf[i + 2] == 0 && buf[i + 3] == 1 && (buf[i + 4] & 0x1f) == 0x7)
           || (buf[i] == 0 && buf[i + 1] == 0 && buf[i + 2] == 1 && (buf[i + 3] & 0x1f) == 0x7))
        {
            break;
        }
    }

    if (i == (size - 5))
    {
        return -1;    //not found sps
    }

    for (j = i; j < (size - 5); j++)
    {
        /* nal_ref_idc might not be always 2 (Not ture -> buf[3 or 4] != 0x68)*/
        if ((buf[j] == 0 && buf[j + 1] == 0 && buf[j + 2] == 0 && buf[j + 3] == 1 && (buf[j + 4] & 0x1f) == 0x8)
           || (buf[j] == 0 && buf[j + 1] == 0 && buf[j + 2] == 1 && (buf[j + 3] & 0x1f) == 0x8))
        {
            break;
        }
    }

    if (j == (size - 5))
    {
        return -1 ;    //not found pps
    }

    return 0;
}

int MediaUtil::h264_update_frame_header(unsigned char * data,int size)
{
	int nalsize;
	unsigned char *p = data;
	if (p != nullptr) {
		if (check_size_in_buffer(p, size)) {
			while ((p + 4) < (data + size)) {
				nalsize = (*p << 24) | (*(p + 1) << 16) | (*(p + 2) << 8) | (*(p + 3));
				*p = 0;
				*(p + 1) = 0;
				*(p + 2) = 0;
				*(p + 3) = 1;
				p += (nalsize + 4);
			}
			return 0;
		} else if (check_size_in_buffer3(p, size)) {
			while ((p + 3) < (data + size)) {
				nalsize = (*p << 16) | (*(p + 1) << 8) | (*(p + 2));
				*p = 0;
				*(p + 1) = 0;
				*(p + 2) = 1;
				p += (nalsize + 3);
			}
			return 0;
		} else if (check_size_in_buffer2(p, size)) {
#if 0
			unsigned char *new_data;
			int new_len = 0;

			new_data = (unsigned char *)MALLOC(size + 2 * 1024);
			if (!new_data) {
				return -1;
			}

			while ((p + 2) < (data + size)) {
				nalsize = (*p << 8) | (*(p + 1));
				*(new_data + new_len) = 0;
				*(new_data + new_len + 1) = 0;
				*(new_data + new_len + 2) = 0;
				*(new_data + new_len + 3) = 1;
				memcpy(new_data + new_len + 4, p + 2, nalsize);
				p += (nalsize + 2);
				new_len += nalsize + 4;
			}

			FREE(pkt->buf);

			pkt->buf = new_data;
			pkt->buf_size = size + 2 * 1024;
			pkt->data = pkt->buf;
			pkt->data_size = new_len;
#endif
		}
	} else {
		//log_error("[%s]invalid pointer!\n", __FUNCTION__);
		return -1;
	}
	return 0;
}

int MediaUtil::hevc_add_header(AVCodecContext * pCodecCtx,uint8_t * buf)
{
    char nal_start_code[] = {0x0, 0x0, 0x0, 0x1};
    int nalsize;
    uint8_t* p;
    int header_len = 0;
    int size;

    if(!pCodecCtx->extradata) return 0;

    p = pCodecCtx->extradata;
    size = pCodecCtx->extradata_size;

    if (size > VID_HEADER_SIZE)
    {
        return 0;
    }

    if((p[0] == 0 && p[1] == 0 && p[2] == 0 && p[3] == 1) || (p[0] == 0 && p[1] == 0 && p[2] == 1) && size < VID_HEADER_SIZE)
    {
        memcpy(buf, p, size);
        header_len = size;
        return header_len;
    }

    if(size < 4)
    {
        return 0;
    }

    // TODO: maybe need to modify here.
    if(p[0] || p[1] || p[2] > 1)
    {
        /* It seems the extradata is encoded as hvcC format.
         * Temporarily, we support configurationVersion==0 until 14496-15 3rd
         * is finalized. When finalized, configurationVersion will be 1 and we
         * can recognize hvcC by checking if extradata[0]==1 or not. */
        int i, j, num_arrays, nal_len_size;
        p += 21;  // skip 21 bytes
        nal_len_size = *(p++) & 3 + 1;
        num_arrays   = *(p++);
        for(i = 0; i < num_arrays; i++)
        {
            int type = *(p++) & 0x3f;
            int cnt  = (*p << 8) | (*(p + 1));
            p += 2;

            for(j = 0; j < cnt; j++)
            {
                /** nal units in the hvcC always have length coded with 2 bytes */
                nalsize = (*p << 8) | (*(p + 1));
                memcpy(&(buf[header_len]), nal_start_code, 4);
                header_len += 4;
                memcpy(&(buf[header_len]), p + 2, nalsize);
                header_len += nalsize;
                p += (nalsize + 2);
            }
        }
        if(header_len >= VID_HEADER_SIZE)
        {
            return 0;
        }
        return header_len;
    }
    return 0;
}

int MediaUtil::hevc_update_frame_header(unsigned char * data,int size)
{
    // NAL has been formatted already, no need to update
    if (data[0] == 0 && data[1] == 0 && data[2] == 0 && data[3] == 1)
    {
        return 0;
    }
    // process like h264 for now.
    return h264_update_frame_header(data, size);
}

int MediaUtil::codec_add_header(AVCodecContext * pCodecCtx,uint8_t * buf)
{
    return 0;
}

int MediaUtil::aac_add_header(AVCodecContext * pCodecCtx, uint8_t * buf)
{
    adts_header_t hdr;
    uint8_t *p = nullptr;
    int i;

    if (pCodecCtx->extradata) {
        p = pCodecCtx->extradata;
        hdr.profile = (*p >> 3) - 1;        // 5 bits
        hdr.sample_freq_idx = (*p & 0x7) << 1 | (*(p + 1) >> 7); // 4 bits
        hdr.channel_configuration = (*(p + 1) & 0x7f) >> 3; // 4 bits
        if ((*p >> 3) == 5/*AOT_SBR*/ || ((*p >> 3) == 29/*AOT_PS*/ &&
                                          // check for W6132 Annex YYYY draft MP3onMP4
                                          !((*(p + 1) & 0x7) & 0x03 && !(((*(p + 1) & 0x7) << 6 | (*(p + 2) >> 2)) & 0x3F)))) {
            //skip 4  bits for ex-sample-freq_idx
            hdr.profile = ((*(p + 2) & 0x7f) >> 2) - 1; // 5 bits

        }
        //log_print("extract aac insert adts header:profile %d,sr_index %d,ch_config %d\n", hdr.profile, hdr.sample_freq_idx, hdr.channel_configuration);
    } else {
        if (pCodecCtx->profile < 0)
        {
            hdr.profile = 1;
        }
        else
        {
            if (pCodecCtx->profile > 3)
            {
               hdr.profile = 1;
            }
            else
            {
                hdr.profile = pCodecCtx->profile /* - 1 org*/;
            }
        }
        hdr.channel_configuration = pCodecCtx->channels;
        for (i = 0; i < sizeof(sample_rates) / sizeof(uint32_t); i ++) {
            if (pCodecCtx->sample_rate == sample_rates[i]) {
                hdr.sample_freq_idx = i;
            }
        }
        //log_print("aac insert adts header:profile %d,sr_index %d,ch_config %d\n", hdr.profile, hdr.sample_freq_idx, hdr.channel_configuration);
    }

    hdr.syncword = 0xfff;
    hdr.id = 0;
    hdr.layer = 0;
    hdr.protection_absent = 1;
    hdr.private_bit = 0;
    hdr.original_copy = 0;
    hdr.home = 0;
    hdr.copyright_identification_bit = 0;
    hdr.copyright_identification_start = 0;
    hdr.aac_frame_length = 0;
    hdr.adts_buffer_fullness = 0x7ff;
    hdr.number_of_raw_data_blocks_in_frame = 0;
    buf[0] = (char)(hdr.syncword >> 4);
    buf[1] = (char)((hdr.syncword & 0xf << 4) |
                    (hdr.id << 3) |
                    (hdr.layer << 1) |
                    hdr.protection_absent);
    buf[2] = (char)((hdr.profile << 6) |
                    (hdr.sample_freq_idx << 2) |
                    (hdr.private_bit << 1) |
                    (hdr.channel_configuration >> 2));
    buf[3] = (char)(((hdr.channel_configuration & 0x3) << 6) |
                    (hdr.original_copy << 5) |
                    (hdr.home << 4) |
                    (hdr.copyright_identification_bit << 3) |
                    (hdr.copyright_identification_start << 2) |
                    (hdr.aac_frame_length) >> 11);
    buf[4] = (char)((hdr.aac_frame_length >> 3) & 0xff);
    buf[5] = (char)(((hdr.aac_frame_length & 0x7) << 5) |
                    (hdr.adts_buffer_fullness >> 6));
    buf[6] = (char)(((hdr.adts_buffer_fullness & 0x3f) << 2) |
                    hdr.number_of_raw_data_blocks_in_frame);

    return ADTS_HEADER_SIZE;
}

int MediaUtil::aac_check_header(uint8_t * buf,int size)
{
    if(buf && size >= ADTS_HEADER_SIZE)
    {
        if(((buf[0] << 4) | (buf[1] & 0xF0) >> 4) != 0xFFF) //sync code
        {
            return -1;
        }
        if((((buf[3] & 0x2) << 11) | ((buf[4] & 0xFF) << 3) | ((buf[5] & 0xE0) >> 5)) != size) //frame length
        {
            // TODO: update here, please check whether this code is safe.
            LOGD("[DEBUG] Update size from %d to %d\n", (((buf[3] & 0x2) << 11) | ((buf[4] & 0xFF) << 3) | ((buf[5] & 0xE0) >> 5)), size);
            aac_update_frame_header(size, buf);
            //return -1;
        }
        // Do not send header
        return 0;
    }

    return -1;
}

int MediaUtil::aac_update_frame_header(int size,uint8_t * hdr)
{
    if(hdr)
    {
        // TODO: check logic.
        hdr[3] = (hdr[3] & 0xfc) | (size >> 11);
        hdr[4] = (size >> 3) & 0xff;
        hdr[5] = (hdr[5] & 0x1f) | ((size & 0x7) << 5);
        return ADTS_HEADER_SIZE;
    }

    return 0;
}

int MediaUtil::aac_csd0_from_context(AVCodecContext * pCodecCtx, uint8_t * csd_buf)
{
    adts_header_t hdr;
    uint8_t *p = nullptr;
    int i;

    int profile = 2;
    int sampleRateIndex = 3;
    int channelConfig = 2;

    if (pCodecCtx->extradata) {
        p = pCodecCtx->extradata;
        hdr.profile = (*p >> 3) - 1;        // 5 bits
        hdr.sample_freq_idx = (*p & 0x7) << 1 | (*(p + 1) >> 7); // 4 bits
        hdr.channel_configuration = (*(p + 1) & 0x7f) >> 3; // 4 bits
        if ((*p >> 3) == 5/*AOT_SBR*/ || ((*p >> 3) == 29/*AOT_PS*/ &&
                                          // check for W6132 Annex YYYY draft MP3onMP4
                                          !((*(p + 1) & 0x7) & 0x03 && !(((*(p + 1) & 0x7) << 6 | (*(p + 2) >> 2)) & 0x3F)))) {
            //skip 4  bits for ex-sample-freq_idx
            hdr.profile = ((*(p + 2) & 0x7f) >> 2) - 1; // 5 bits
        }
    } else {
        if (pCodecCtx->profile < 0)
        {
            hdr.profile = 1;
        }
        else
        {
            if (pCodecCtx->profile > 3)
            {
               hdr.profile = 1;
            }
            else
            {
                hdr.profile = pCodecCtx->profile /* - 1 org*/;
            }
        }
        hdr.channel_configuration = pCodecCtx->channels;
        for (i = 0; i < sizeof(sample_rates) / sizeof(uint32_t); i ++) {
            if (pCodecCtx->sample_rate == sample_rates[i]) {
                hdr.sample_freq_idx = i;
            }
        }
    }

    // The stream indicates AAC-Main (1), AAC-SSR (3) or AAC-LTP (4). When the stream indicates
    // AAC-Main it's more likely that the stream contains HE-AAC (5), which cannot be
    // represented correctly in the 2 bit audio_object_type field in the ADTS header. In
    // practice when the stream indicates AAC-SSR or AAC-LTP it more commonly contains AAC-LC or
    // HE-AAC. Since most Android devices don't support AAC-Main, AAC-SSR or AAC-LTP, and since
    // indicating AAC-LC works for HE-AAC streams, we pretend that we're dealing with AAC-LC and
    // hope for the best. In practice this often works.
    // See: https://github.com/google/ExoPlayer/issues/774
    // See: https://github.com/google/ExoPlayer/issues/1383
    profile = hdr.profile + 1;
    if (profile != 2) {
        LOGD("Detected audio profile %s(%d) -> but assuming it as AAC LC(2)\n", aac_encode_level[profile], profile);
        profile = 2;
    }

    sampleRateIndex = hdr.sample_freq_idx;
    channelConfig = hdr.channel_configuration;
    csd_buf[0] =  (uint8_t)(((profile<<3)&0xF8) | ((sampleRateIndex>>1)&0x07));
    csd_buf[1] =  (uint8_t)(((sampleRateIndex<<7)&0x80) | ((channelConfig<<3)&0x78));

    return 2;
}

int MediaUtil::aac_csd0_from_payload(uint8_t * buf, uint8_t *csd_buf)
{
    adts_header_t hdr;
    uint8_t *p = nullptr;
    int i;

    int profile = 2;
    int sampleRateIndex = 3;
    int channelConfig = 2;

    if(((buf[0] << 4) | (buf[1] & 0xF0) >> 4) != 0xFFF) //sync code
    {
        return -1;
    }

    profile = ((buf[2]>>6) & 0x3) + 1;

    if (profile != 2) {
        LOGD("Detected audio profile %s(%d) -> but assuming it as AAC LC(2)\n", aac_encode_level[profile], profile);
        profile = 2;
	}

    sampleRateIndex = ((buf[2]>>2)&0xf);
    channelConfig = ((buf[2]&0x1)<<2) | ((buf[3]>>6)&0x3);

    csd_buf[0] =  (uint8_t)(((profile<<3)&0xF8) | ((sampleRateIndex>>1)&0x07));
    csd_buf[1] =  (uint8_t)(((sampleRateIndex<<7)&0x80) | ((channelConfig<<3)&0x78));

	return 2;
}

int MediaUtil::opus_csd0_from_playload(uint8_t *buf, int buf_size, uint8_t *csd_buf)
{
	if (!buf || !csd_buf) {
		LOGE("Invalid null parameter\n");
		return -1;
	}

	// check OPUS header : "Opus"
	if (*(int *)buf != 0x7375704f) {
		LOGE("No OPUS signature found 0x%x\n", *(int *)buf);
		return -1;
	}

	memcpy(csd_buf, buf, buf_size);

	return buf_size;
}

int MediaUtil::opus_csd1_from_playload(uint8_t *buf, int buf_size, uint8_t *csd_buf)
{
	int preSkipSamples = 0;
	uint64_t preSkipNanoDuration = 0LL;

	if (!buf || !csd_buf) {
		LOGE("Invalid null parameter\n");
		return -1;
	}

	if (buf_size < 15) {
		LOGE("Not enough data(%d) to parse opus preSkipCount\n", buf_size);
		return -1;
	}

	// check OPUS header : "Opus"
	if (*(int *)buf != 0x7375704f) {
		LOGE("No OPUS signature found 0x%x\n", *(int *)buf);
		return -1;
	}

	int sample_rate = ((int)buf[15] & 0xFF) << 24 | ((int)buf[14] & 0xFF) << 16 | ((int)buf[13] & 0xFF) << 8 | (int)buf[12];

	if (sample_rate != 48000) {
		LOGW("[DEBUG] OPUS sample rate %d != 48000\n", sample_rate);
	}

	preSkipSamples = ((int)buf[11] & 0xFF) << 8 | (buf[10]&0xFF);
	/* opus streams are always 48000 Hz */
	preSkipNanoDuration = preSkipSamples * 1000000000LL / 48000;

	memcpy(csd_buf, (uint8_t*)&preSkipNanoDuration, sizeof(preSkipNanoDuration));

	return sizeof(preSkipNanoDuration);
}

int MediaUtil::opus_csd2_from_playload(uint8_t *buf, int buf_size, uint8_t *csd_buf)
{
#define DEFAULT_SEEK_PRE_ROLL_SAMPLES 3840
	uint64_t seekPrerollNanoDuration = 0LL;

	if (!buf || !csd_buf) {
		LOGE("Invalid null parameter\n");
		return -1;
	}

	if (buf_size < 12) {
		LOGE("Not enough data(%d) to parse opus preSkipCount\n", buf_size);
		return -1;
	}

	// check OPUS header : "Opus"
	if (*(int *)buf != 0x7375704f) {
		LOGE("No OPUS signature found 0x%x\n", *(int *)buf);
		return -1;
	}

	int sample_rate = ((int)buf[15] & 0xFF) << 24 | ((int)buf[14] & 0xFF) << 16 | ((int)buf[13] & 0xFF) << 8 | (int)buf[12];
	if (sample_rate != 48000) {
		LOGW("[DEBUG] OPUS sample rate %d != 48000\n", sample_rate);
	}

	/* opus streams are always 48000 Hz */
	seekPrerollNanoDuration = DEFAULT_SEEK_PRE_ROLL_SAMPLES * 1000000000LL / 48000;
	memcpy(csd_buf, (uint8_t*)&seekPrerollNanoDuration, sizeof(seekPrerollNanoDuration));

	return sizeof(seekPrerollNanoDuration);
}

/* extract identification header */
int MediaUtil::vorbis_csd0_from_playload(uint8_t *buf, int buf_size, uint8_t *csd_buf, int *block0, int *block1)
{
	int ret;
	int i, hsizes[3];
	uint8_t *p = buf;
	uint8_t * headers[3];

	int csd_length = -1;

	if (!p || !csd_buf) {
		LOGE("Invalid null parameter\n");
		return -1;
	}

	if (p[0] == 0 && p[1] == 30) {
		int size_num = 0;
		for (i=0; i<3; i++) {
			hsizes[i] = ((int)p[0]&0xFF) << 8 | (int)p[1] & 0xFF;
			p +=2;
			size_num += 2 + hsizes[i];
			if (size_num > buf_size) {
				LOGE("Vorbis initial header is too small(%d)\n", buf_size);
				return -1;
			}

			headers[0] = p;
			p += hsizes[i];
		}
	}
	else if (*p==2) {
		uint32_t offset = 1;
		uint32_t size_num = 1;
		p++;
		for (i=0; i<2; i++) {
			hsizes[i] = 0;
			while((*p == 0xFF) && (size_num < buf_size)) {
				hsizes[i] += 0xFF;
				offset++;
				size_num += 1 + 0xFF;
				p++;
			}

			hsizes[i] += *p;
			offset++;
			size_num += 1 + *p;
			if (size_num > buf_size) {
				LOGE("Vorbis initial header is too small(%d)\n", buf_size);
				return -1;
			}
			p++;
		}
		hsizes[2] = buf_size - hsizes[0] - hsizes[1] - offset;

		headers[0] = buf + offset;
		headers[1] = buf + offset + hsizes[0];
		headers[2] = buf + offset + hsizes[0] + hsizes[1];
	}
	else {
		LOGE("Vorbis initial header is too small(%d)\n", buf_size);
		return -1;
	}

	for(i=0; i<3; i++) {
		p = headers[i];
		if (*p == 1) {
			int block0_size = 0;
			int block1_size = 0;
			// This is identification header
			if (p[1] == 'v' &&
			    p[2] == 'o' &&
			    p[3] == 'r' &&
			    p[4] == 'b' &&
			    p[5] == 'i' &&
			    p[6] == 's') {
				csd_length = hsizes[i];
				memcpy(csd_buf, p, csd_length);

				// debug
				p += strlen("vorbis") + 1;
				// version unsigned
				//LOGE("VERSION = 0x%x\n", (uint32_t)(p[0]));
				p += 4;
				// channel unsigne byte
				//LOGE("CHANNEL = 0x%02x\n", p[0]);
				p += 1;

				// samplerate
				//LOGE("samplerate = %u\n", *(uint32_t *)p);
				p +=4;

				// bitrate max
				//LOGE("maximum bitrate = %d\n", *(uint32_t *)p);
				p +=4;

				//LOGE("norminal bitrate = %d\n", *(uint32_t *)p);
				p +=4;

				//LOGE("minimum bitrate = %d\n", *(uint32_t *)p);
				p +=4;

				//LOGE("blocksize  = %02x\n", p[0]);
				block0_size = (int)(std::pow(2.0, (p[0]&0x0F)));
				block1_size = (int)(std::pow(2.0, (p[0]&0x0F)));

				if (block0_size != 64 &&
					block0_size != 128 &&
					block0_size != 256 &&
					block0_size != 512 &&
					block0_size != 1024 &&
					block0_size != 2048 &&
					block0_size != 4096 &&
					block0_size != 8192) {
					// failed.
					block0_size = 256;
					block1_size = 2048;
				}
				else {
					if (block0_size >= block1_size) {
						block0_size = 256;
						block1_size = 2048;
					}
					else {
						if (block1_size > 8192) {
							block1_size = 8192;
						}
					}
				}

				if (block0)
					*block0 = block0_size;
				if (block1)
					*block1 = block1_size;

				LOGD("Vorbis block0 = %d\n", block0_size);
				LOGD("Vorbis block1 = %d\n", block1_size);
				//p += 1;
				//LOGE("flag = %d\n", p[0] & 0x01);

				break;
			}
		}
	}

	if (csd_length == -1) {
		LOGE("Found no vorbis identification header\n");
	}

	return csd_length;
}

/* extract setup header */
int MediaUtil::vorbis_csd1_from_playload(uint8_t *buf, int buf_size, uint8_t *csd_buf)
{
	int ret;
	int i, hsizes[3];
	uint8_t *p = buf;
	uint8_t * headers[3];

	int csd_length = -1;

	if (!p || !csd_buf) {
		LOGE("Invalid null parameter\n");
		return -1;
	}

	if (p[0] == 0 && p[1] == 30) {
		int size_num = 0;
		for (i=0; i<3; i++) {
			hsizes[i] = ((int)p[0]&0xFF) << 8 | (int)p[1] & 0xFF;
			p +=2;
			size_num += 2 + hsizes[i];
			if (size_num > buf_size) {
				LOGE("Vorbis initial header is too small(%d)\n", buf_size);
				return -1;
			}

			headers[0] = p;
			p += hsizes[i];
		}
	}
	else if (*p==2) {
		uint32_t offset = 1;
		uint32_t size_num = 1;
		p++;
		for (i=0; i<2; i++) {
			hsizes[i] = 0;
			while((*p == 0xFF) && (size_num < buf_size)) {
				hsizes[i] += 0xFF;
				offset++;
				size_num += 1 + 0xFF;
				p++;
			}

			hsizes[i] += *p;
			offset++;
			size_num += 1 + *p;
			if (size_num > buf_size) {
				LOGE("Vorbis initial header is too small(%d)\n", buf_size);
				return -1;
			}
			p++;
		}
		hsizes[2] = buf_size - hsizes[0] - hsizes[1] - offset;

		headers[0] = buf + offset;
		headers[1] = buf + offset + hsizes[0];
		headers[2] = buf + offset + hsizes[0] + hsizes[1];
	}
	else {
		LOGE("Vorbis initial header is too small(%d)\n", buf_size);
		return -1;
	}

	for(i=0; i<3; i++) {
		p = headers[i];
		if (*p == 5) {
			// This is setup header
			if (p[1] == 'v' &&
			    p[2] == 'o' &&
			    p[3] == 'r' &&
			    p[4] == 'b' &&
			    p[5] == 'i' &&
			    p[6] == 's') {
				csd_length = hsizes[i];
				memcpy(csd_buf, p, csd_length);
				break;
			}
		}
	}

	if (csd_length == -1) {
		LOGE("Found no vorbis setup header\n");
	}

	return csd_length;
}

int MediaUtil::flac_csd0_from_playload(uint8_t *buf, int buf_size, uint8_t *csd_buf)
{
	uint8_t *p = buf;
	int size = buf_size;
	int header_size = 0;

	if (!buf || !csd_buf) {
		LOGE("Invalid null parameter\n");
		return -1;
	}

	// check FLAC header : "fLaC"
	if (*(int *)buf == 0x43614C66) {
		// skip header
		p += 4;
	}

	csd_buf[0] = 0x66;
	csd_buf[1] = 0x4C;
	csd_buf[2] = 0x61;
	csd_buf[3] = 0x43;
	csd_buf[4] = 0x80; // default : set last
	csd_buf[5] = ((size & 0xFF0000) >> 16) & 0xFF;
	csd_buf[6] = ((size & 0x00FF00) >> 8) & 0xFF;
	csd_buf[7] = (size & 0xFF);

	/* search stream info */
	while(size > (FLAC_METADATA_HEAD_SIZE+FLAC_METADATA_STREAMINFO_SIZE)) {
		int isLast = 0;
		int blockType = FLAC_STREAMINFO;
		int blockLen = 0;

		flac_metablock_header(p, &isLast, &blockType, &blockLen);
		if (blockType == FLAC_STREAMINFO && blockLen == FLAC_METADATA_STREAMINFO_SIZE) {
			if (size < blockLen) {
				LOGE("FLAC: Not enough data in the header to parse streamInfo(need %d > left %d\n", blockLen, size);
				break;
			}

			LOGD("FLAC : Found streamInfo metadata\n", blockLen);
			memcpy(&csd_buf[4], p, blockLen + 4);
			p += blockLen + FLAC_METADATA_HEAD_SIZE;
			header_size = 4 + FLAC_METADATA_HEAD_SIZE + blockLen;
			// skip other metablock
			break;
		}
		else if (blockLen > 0) {
			if (size < blockLen + FLAC_METADATA_HEAD_SIZE + FLAC_METADATA_STREAMINFO_SIZE) {
				LOGD("[DEBUG] FLAC: no more data left to parse streamInfo\n");
				break;
			}

			size -= blockLen;
			p += blockLen;
		}
	}

	if (header_size == 0) {
		// Mandatory(8B + streamInfo): "fLaC" + MetaHeaderSize(4) + ...
		memcpy(&csd_buf[4 + FLAC_METADATA_HEAD_SIZE], buf, buf_size);
		header_size = 4 + FLAC_METADATA_HEAD_SIZE + buf_size;
	}

	return header_size;
}

