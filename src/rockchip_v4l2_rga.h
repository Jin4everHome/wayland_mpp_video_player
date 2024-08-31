#ifndef MEDIA_FILTERS_ROCKCHIP_V4L2_RGA_H_
#define MEDIA_FILTERS_ROCKCHIP_V4L2_RGA_H_

#include "rockchip/rk_mpi.h"
#include "rockchip_rgarect.h"

namespace {

#define RGA_DEVICE_PATH "/dev/video0"

enum RGAConfigTypes
{
	RGA_CONFIG_TYPE_INPUT,
	RGA_CONFIG_TYPE_OUTPUT
};

#define RGA_INPUT_BUFFER_COUNT    1
#define RGA_OUTPUT_BUFFER_COUNT   5

}

//namespace media {
class RGA {
public:
	RGA();
	~RGA();

	int setRGA(RGARect& inRect, RGARect& outRect);
	int setRGA(RGARect* inRect, RGARect* outRect);
	int setInputRGA(RGARect& inRect);
	int setOutputRGA(RGARect& inRect);

	RGARect& getInputRGARect();
	RGARect& getOutputRGARect();

	int rgaConversion(MppFrame inFrame, MppFrame outFrame);
	int rgaConversion(int inFd, int outFd);
	int rgaConversion(MppFrame inFrame, int outFd);

private:
	int mFD;
	std::unique_ptr<RGARect> mSrcRect;
	std::unique_ptr<RGARect> mDstRect;

	int openDevice();
	void closeDevice();

	int setFormatDevice(RGAConfigTypes type);
	int setBuffer(RGAConfigTypes type);
	int setRotation(int value);
	int setStreamON(RGAConfigTypes type);
	int setStreamOFF(RGAConfigTypes type);

	bool mSrcRectVaild = false;
	bool mDetRectVaild = false;
	bool mInputFmtSetDone = false;
	bool mOutputFmtSetDone = false;
	bool mInputBufferSetDone = false;
	bool mOutputBufferSetDone = false;
	bool mRotationSetDone = false;

	bool mIsInputStreamOn = false;
	bool mIsOutputStreamOn = false;

	int mInputConfigured = false;
	int mOutputConfifured = false;
	int mInputBufferCount = 0;
	int mOutputBufferCount = 0;
	int mInputBufferSize = 0;
	int mOutputBufferSize = 0;

}; // class RGA

//} // namespace media

#endif //MEDIA_FILTERS_ROCKCHIP_V4L2_RGA_H_
