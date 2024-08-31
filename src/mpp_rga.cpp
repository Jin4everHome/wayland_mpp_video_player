#include <rga/RgaApi.h>
#include <rockchip/mpp_buffer.h>
#include <rockchip/rk_mpi.h>
#include "mpp_rga.h"
#include "log.h"

namespace {

#define _DEBUG_RECTS_ 0

#define CODEC_ALIGN(x, a)   (((x)+(a)-1)&~((a)-1))

const char * rgaFormatToString(RgaSURF_FORMAT format)
{
	switch(format) {
	
		case RK_FORMAT_YCbCr_420_SP:
			return "RK_FORMAT_YCbCr_420_SP";
		case RK_FORMAT_YCbCr_420_SP_10B:
			return "RK_FORMAT_YCbCr_420_SP_10B";
		case RK_FORMAT_YCbCr_420_P:
			return "RK_FORMAT_YCbCr_420_P";
		default : 
			return "RK_FORMAT_UNKNOWN";
	}

	return  "RK_FORMAT_UNKNOWN";
}

RgaSURF_FORMAT getRGAFormat (MppFrameFormat format) 
{
	RgaSURF_FORMAT outFmt = RK_FORMAT_UNKNOWN;

	switch(format) {
		case MPP_FMT_YUV420SP:
			outFmt = RK_FORMAT_YCbCr_420_SP;
			break;
		case MPP_FMT_YUV420P:
			outFmt = RK_FORMAT_YCbCr_420_P;
			break;
		case MPP_FMT_RGB888:
			outFmt = RK_FORMAT_RGB_888;
			break;
		case MPP_FMT_ARGB8888:
			outFmt = RK_FORMAT_RGBA_8888;
			break;
		case MPP_FMT_RGB565:
			outFmt = RK_FORMAT_RGB_565;
			break;
		default :
			LOGE("Unknown MPP Frame format %d\n", format);
	}

	return outFmt;
}


int getRGARotation(int rotation)
{
	if (rotation < 0) {
		return 0;
	}

	switch (rotation) {
	case 0:
		return 0;
	case 90:
		return HAL_TRANSFORM_ROT_90;
	case 180:
		return HAL_TRANSFORM_ROT_180;
	case 270:
		return HAL_TRANSFORM_ROT_270;
	default:
		LOGE("Invalid rotation value = %d\n", rotation);
		return 0;
	}
}

int getRGAFlip(int flip)
{

	switch (flip) {
	case 0:
		return 0;
	case 1:
		return HAL_TRANSFORM_FLIP_H;
	case 2:
		return HAL_TRANSFORM_FLIP_V;
	default:
		LOGE("Invalid flip value = %d\n", flip);
		return 0;
	}
}

} // namespace

RGA::RGA()
   :mRKRga(RockchipRga::get()),
    mRotation(0),
    mFlip(0), // 0(none), 1(H), 2(V)
    mFlushed(false),

    mInX(0),
    mInY(0),
    mInWidth(0),
    mInHeight(0),
    mInStrideW(0),
    mInStrideH(0),
    mInFormat(RK_FORMAT_UNKNOWN),

    mOutX(0),
    mOutY(0),
    mOutWidth(0),
    mOutHeight(0),
    mOutStrideW(0),
    mOutStrideH(0),
    mOutFormat(RK_FORMAT_UNKNOWN)
{
	LOGD("%s\n", __func__);
}

RGA::~RGA()
{
	LOGD("%s\n", __func__);
}

int RGA::setInputRGA(int width, int height, int strideW, int strideH, MppFrameFormat inFmt)
{
	RgaSURF_FORMAT rgaFmt;

	rgaFmt = getRGAFormat(inFmt);

	if (rgaFmt == RK_FORMAT_UNKNOWN) {
		LOGE("Found no RGA format for %d\n", inFmt);
		return -1;
	}

	mInX = 0;
	mInY = 0;
	mInWidth = width;
	mInHeight = height;
	mInStrideW= strideW;
	mInStrideH= strideH;
	mInFormat = rgaFmt;
	
	return 0;
}

int RGA::setOutputRGA(int width, int height, int strideW, int strideH, MppFrameFormat inFmt)
{
	RgaSURF_FORMAT rgaFmt;

	rgaFmt = getRGAFormat(inFmt);

	if (rgaFmt == RK_FORMAT_UNKNOWN) {
		LOGE("Found no RGA format for %d\n", inFmt);
		return -1;
	}

	mOutX = 0;
	mOutY = 0;
	mOutWidth = width;
	mOutHeight = height;
	mOutStrideW= strideW;
	mOutStrideH= strideH;
	mOutFormat = rgaFmt;

	return 0;
}

int RGA::setRotation(int rotation)
{
	if (rotation == 90 || rotation == 180 || rotation == 270) {
		mRotation = getRGARotation(rotation);
	}
	else {
		mRotation = 0;
	}

	return 0;
}

int RGA::	setFlip(int flip)
{
	if (flip == 1 || flip == 2) {
		mFlip = getRGAFlip(flip);
	}

	return 0;
}

int RGA::convert_m2m(void *pSrcAddr, void *pDstAddr)
{
	int rc = 0;
	rga_info_t src_info = {0};
	rga_info_t dst_info = {0};

	if (!pSrcAddr || !pDstAddr) {
		LOGE("Invalid null point parameter\n");
		return -1;
	}

	if (mInFormat == RK_FORMAT_UNKNOWN || mOutFormat == RK_FORMAT_UNKNOWN) {
		LOGE("Invalid frame pixel format %d, %d\n", mInFormat, mOutFormat);
		return -1;
	}

	src_info.fd = -1;
	src_info.virAddr = pSrcAddr;
	src_info.mmuFlag = 1;

	dst_info.fd = -1;
	dst_info.virAddr = pDstAddr;
	dst_info.mmuFlag = 1;

	src_info.rotation = mRotation;

	if (mFlip == HAL_TRANSFORM_FLIP_H || mFlip == HAL_TRANSFORM_FLIP_V) {
		src_info.rotation |= (mRotation > 0) ? mFlip << 4 : mFlip;
	}

	rc = blitOneFrame(src_info, dst_info);
	if (rc) {
		LOGE("blitOneFrame failed\n");
	}

	return rc;
}

int RGA::convert_FD2FD(int srcFD, int dstFD)
{
	int rc = 0;
	rga_info_t src_info = {0};
	rga_info_t dst_info = {0};

	if (srcFD<0 || dstFD < 0) {
		LOGE("Invalid FD parameter\n");
		return -1;
	}

	if (mInFormat == RK_FORMAT_UNKNOWN || mOutFormat == RK_FORMAT_UNKNOWN) {
		LOGE("Invalid frame pixel format %d, %d\n", mInFormat, mOutFormat);
		return -1;
	}

	src_info.fd = srcFD;
	src_info.mmuFlag = 1;

	dst_info.fd = dstFD;
	dst_info.mmuFlag = 1;

	src_info.rotation = mRotation;

	if (mFlip == HAL_TRANSFORM_FLIP_H || mFlip == HAL_TRANSFORM_FLIP_V) {
		src_info.rotation |= (mRotation > 0) ? mFlip << 4 : mFlip;
	}

	rc = blitOneFrame(src_info, dst_info);
	if (rc) {
		LOGE("blitOneFrame failed\n");
	}

	return rc;
}

int RGA::convert_m2FD(void *pSrcAddr, int fd)
{
	int rc = 0;
	rga_info_t src_info = {0};
	rga_info_t dst_info = {0};

	if (!pSrcAddr || fd < 0) {
		LOGE("Invalid null point parameter\n");
		return -1;
	}

	if (mInFormat == RK_FORMAT_UNKNOWN || mOutFormat == RK_FORMAT_UNKNOWN) {
		LOGE("Invalid frame pixel format %d, %d\n", mInFormat, mOutFormat);
		return -1;
	}

	src_info.fd = -1;
	src_info.virAddr = pSrcAddr;
	src_info.mmuFlag = 1;

	dst_info.fd = fd;
	dst_info.virAddr = nullptr;
	dst_info.mmuFlag = 1;

	src_info.rotation = mRotation;

	if (mFlip == HAL_TRANSFORM_FLIP_H || mFlip == HAL_TRANSFORM_FLIP_V) {
		src_info.rotation |= (mRotation > 0) ? mFlip << 4 : mFlip;
	}

	rc = blitOneFrame(src_info, dst_info);
	if (rc) {
		LOGE("blitOneFrame failed\n");
	}

	return rc;
}

int RGA::convert_FD2m(int fd, void *pDstAddr)
{
	int rc = 0;
	rga_info_t src_info = {0};
	rga_info_t dst_info = {0};

	if ( fd < 0 || !pDstAddr) {
		LOGE("Invalid null point parameter\n");
		return -1;
	}

	if (mInFormat == RK_FORMAT_UNKNOWN || mOutFormat == RK_FORMAT_UNKNOWN) {
		LOGE("Invalid frame pixel format %d, %d\n", mInFormat, mOutFormat);
		return -1;
	}

	src_info.fd = fd;
	src_info.virAddr = nullptr;
	src_info.mmuFlag = 1;

	dst_info.fd = -1;
	dst_info.virAddr = pDstAddr;
	dst_info.mmuFlag = 1;

	src_info.rotation = mRotation;

	if (mFlip == HAL_TRANSFORM_FLIP_H || mFlip == HAL_TRANSFORM_FLIP_V) {
		src_info.rotation |= (mRotation > 0) ? mFlip << 4 : mFlip;
	}

	rc = blitOneFrame(src_info, dst_info);
	if (rc) {
		LOGE("blitOneFrame failed\n");
	}

	return rc;
}

int RGA::blitOneFrame(rga_info_t& srcInfo, rga_info_t& dstInfo)
{
	int rc;

	if (!mFlushed) {
		mRKRga.RkRgaFlush();
		mFlushed = true;
	}

	if (mInFormat == RK_FORMAT_UNKNOWN || mOutFormat == RK_FORMAT_UNKNOWN) {
		LOGE("Invalid frame pixel format %d, %d\n", mInFormat, mOutFormat);
		return -1;
	}

	if (_DEBUG_RECTS_) {
		LOGD("Input RGA SET Rect : W:H=%d:%d, WS:HS=%d:%d, inRgaFmt=%s(0x%x)\n",mInWidth, mInHeight, mInStrideW, mInStrideH, rgaFormatToString(mInFormat), mInFormat);
	}

	rc = rga_set_rect(&srcInfo.rect, 0, 0, mInWidth, mInHeight, mInStrideW, mInStrideH, mInFormat);
	if (rc) {
			LOGE("Error rga set error\n");
			return -1;
	}

	if (_DEBUG_RECTS_) {
		LOGD("Output RGA SET Rect : X:Y=%d:%d, W:H=%d:%d, WS:HS=%d:%d, outRgaFmt=%s(0x%x)\n",
			mOutX, mOutY,  mOutWidth, mOutHeight, mOutStrideW, mOutStrideH, rgaFormatToString(mOutFormat), mOutFormat);
	}

	rc = rga_set_rect(&dstInfo.rect, mOutX, mOutY,  mOutWidth, mOutHeight, mOutStrideW, mOutStrideH, mOutFormat);
	if (rc) {
			LOGE("Error rga set error\n");
			return -1;
	}

	if (mRotation == HAL_TRANSFORM_ROT_90 || mRotation == HAL_TRANSFORM_ROT_270) {
			dstInfo.rect.width    = mOutHeight;
			dstInfo.rect.height   = mOutWidth;
			dstInfo.rect.wstride  = mOutStrideH;
			dstInfo.rect.hstride  = mOutStrideW;
	}

	if ( (rc = mRKRga.RkRgaBlit(&srcInfo, &dstInfo, NULL)) < 0) {
		LOGE("RGA blit failed %d \n", rc);
		return rc;
	}
}

int RGA::convert_with_MppFrame(MppFrame inFrame, MppFrame  outFrame , int rotation)
{
	int rc = 0;

	uint32_t x, y, width, height, hor_stride, ver_stride;
	MppFrameFormat format;
	MppBuffer inBuf = nullptr, outBuf = nullptr;
	int inFD, outFD;
	//void *inPtr = nullptr, *outPtr = nullptr;

	/* Set input */
	width  = mpp_frame_get_width(inFrame);
	height = mpp_frame_get_height(inFrame);
	hor_stride = mpp_frame_get_hor_stride(inFrame);
	ver_stride = mpp_frame_get_ver_stride(inFrame);
	format = mpp_frame_get_fmt(inFrame);

	rc = setInputRGA(width, height, hor_stride, ver_stride, MPP_FMT_YUV420SP);
	if (rc) {
		LOGE("Unable to set input RGA container\n");
		return -1;
	}

	/* Set output */
	width  = mpp_frame_get_width(outFrame);
	height = mpp_frame_get_height(outFrame);
	hor_stride = mpp_frame_get_hor_stride(outFrame);
	ver_stride = mpp_frame_get_ver_stride(outFrame);
	format = mpp_frame_get_fmt(outFrame);
	rc = setOutputRGA(width, height, hor_stride, ver_stride, format);
	if (rc) {
		LOGE("Unable to set output RGA container\n");
		return -1;
	}

	setRotation(rotation);

	inBuf = mpp_frame_get_buffer(inFrame);
	outBuf = mpp_frame_get_buffer(outFrame);

	if (!inBuf || !outBuf) {
		LOGE("Unable to get MPP Buffer\n");
		return -1;
	}

	inFD = mpp_buffer_get_fd(inBuf);
	outFD = mpp_buffer_get_fd(outBuf);

	if (inFD >= 0 && outFD >= 0) {
		rc = convert_FD2FD(inFD, outFD);
		if (rc) {
			LOGE("RGA convert failed\n");
			return -1;
		}
	}

	return 0;
}

