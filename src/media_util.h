#include <stdint.h>

extern "C"
{
#include <libavformat/avformat.h>
}

class MediaUtil {

public:
	static int h264_add_header(AVCodecContext *pCodecCtx, uint8_t *buf);
	static int h264_check_header(uint8_t *buf, int size);
	static int h264_update_frame_header(unsigned char *data, int size);

	static int hevc_add_header(AVCodecContext *pCodecCtx, uint8_t *buf);
	static int hevc_update_frame_header(unsigned char *data, int size);

	static int codec_add_header(AVCodecContext *pCodecCtx, uint8_t *buf);

	static int aac_add_header(AVCodecContext *pCodecCtx, uint8_t *hdr);
	static int aac_check_header(uint8_t *buf, int size);
	static int aac_update_frame_header(int size, uint8_t *hdr);

	static int aac_csd0_from_context(AVCodecContext * pCodecCtx, uint8_t * csd_buf);
	static int aac_csd0_from_payload(uint8_t * buf, uint8_t *csd_buf);

	static int opus_csd0_from_playload(uint8_t *buf, int buf_size, uint8_t *csd_buf);
	static int opus_csd1_from_playload(uint8_t *buf, int buf_size, uint8_t *csd_buf);
	static int opus_csd2_from_playload(uint8_t *buf, int buf_size, uint8_t *csd_buf);

	static int vorbis_csd0_from_playload(uint8_t *buf, int buf_size, uint8_t *csd_buf, int *block0, int *block1);
	static int vorbis_csd1_from_playload(uint8_t *buf, int buf_size, uint8_t *csd_buf);
	static int flac_csd0_from_playload(uint8_t *buf, int buf_size, uint8_t *csd_buf);
};

