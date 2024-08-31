#ifndef __MPP_RGA_H__
#define __MPP_RGA_H__

#include <rockchip/rk_mpi.h>
#include <rga/RockchipRga.h>
#include <rga/RgaUtils.h>

class RGA {

public:

	RGA();
	~RGA();

	int setInputRGA(int width, int height, int strideW, int strideH, MppFrameFormat inFmt);
	int setOutputRGA(int width, int height, int strideW, int strideH, MppFrameFormat inFmt);
	int convert_m2m(void *pSrcAddr, void *pDstAddr);
	int convert_FD2FD(int srcFD, int DstFD);
	int convert_m2FD(void *pSrcAddr, int fd);
	int convert_FD2m(int fd, void *pDstAddr);

	int setRotation(int degree);
	// FIXME : flip doesn't work
	int setFlip(int flip);

	int convert_with_MppFrame(MppFrame inframe, MppFrame  ouFrame , int rotation);

private:
	RockchipRga& mRKRga;

	int mRotation; // 0, 90, 180, 270
	int mFlip; // 0(none), 1(H), 2(V)
	bool mFlushed = false;

	int blitOneFrame(rga_info_t& srcInfo, rga_info_t& dstInfo);

	int mInX;
	int mInY;
	int mInWidth;
	int mInHeight;
	int mInStrideW;
	int mInStrideH;
	RgaSURF_FORMAT mInFormat;

	int mOutX;
	int mOutY;
	int mOutWidth;
	int mOutHeight;
	int mOutStrideW;
	int mOutStrideH;
	RgaSURF_FORMAT mOutFormat;
};


#endif //  __MPP_RGA_H__
