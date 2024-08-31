#include "rockchip_v4l2_rga.h"

#include <unistd.h>
//#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>

#include "log.h"

// Reference : https://www.kernel.org/doc/html/v4.9/media/uapi/v4l/crop.html
namespace {

uint32_t getRGAFormat (MppFrameFormat format) 
{
	uint32_t outFmt = 0;
	switch(format) {
		case MPP_FMT_YUV420SP:
			outFmt = V4L2_PIX_FMT_NV12;
			LOGD("RGA Format = V4L2_PIX_FMT_NV12\n");
			break;
		case MPP_FMT_YUV420P:
			outFmt = V4L2_PIX_FMT_YUV420;
			LOGD("RGA Format = V4L2_PIX_FMT_YUV420\n");
 			break;
 		case MPP_FMT_RGB888:
			outFmt = V4L2_PIX_FMT_RGB24;
			LOGD("RGA Format = V4L2_PIX_FMT_RGB24\n");
 			break;
		case MPP_FMT_ARGB8888:
			outFmt = V4L2_PIX_FMT_ARGB32;
			LOGD("RGA Format = V4L2_PIX_FMT_ARGB32\n");
 			break;
		default :
			LOGE("Unknown MPP Frame format %d\n", format);
	}

	return outFmt;
}

} // namespace

//namespace media {

RGA::RGA()
 : mInputFmtSetDone(false),
   mOutputFmtSetDone(false),
   mInputBufferSetDone(false),
   mOutputBufferSetDone(false),
   mFD(-1)
{
	openDevice();
}

RGA::~RGA()
{
	closeDevice();
}

int RGA::setRGA(RGARect* inRect, RGARect* outRect)
{
	int ret;

	if (mIsOutputStreamOn && mIsInputStreamOn) {
		return 0;
	}
	
	if (!mSrcRect) {
		mSrcRect = std::make_unique<RGARect>();
		if (!mSrcRect) {
			LOGE("Cannot allocate input RGARect\n");
			return -1;
		}
	}

	if (!mDstRect) {
		mDstRect = std::make_unique<RGARect>();
		if (!mDstRect) {
			LOGE("Cannot allocate output RGARect\n");
			return -1;
		}
	}

	mSrcRect->copyRect(inRect);
	mDstRect->copyRect(outRect);

	ret = setFormatDevice(RGA_CONFIG_TYPE_INPUT);
	if (ret) {
		LOGE("Set input device format failed\n");
		return -1;
	}

	ret = setFormatDevice(RGA_CONFIG_TYPE_OUTPUT);
	if (ret) {
		LOGE("Set output device format failed\n");
		return -1;
	}


	ret = setBuffer(RGA_CONFIG_TYPE_INPUT);
	if (ret) {
		LOGE("Set input device buffer init failed\n");
		return -1;
	}


	ret = setBuffer(RGA_CONFIG_TYPE_OUTPUT);
	if (ret) {
		LOGE("Set output device buffer init failed\n");
		return -1;
	}

	return 0;
}

int RGA::setRGA(RGARect& inRect, RGARect& outRect)
{
	int ret;
	
	if (!mSrcRect) {
		mSrcRect = std::make_unique<RGARect>();
		if (!mSrcRect) {
			LOGE("Cannot allocate input RGARect\n");
			return -1;
		}
	}

	mSrcRect->copyRect(inRect);

	ret = setFormatDevice(RGA_CONFIG_TYPE_INPUT);
	if (ret) {
		LOGE("Set input device format failed\n");
		return -1;
	}

	ret = setBuffer(RGA_CONFIG_TYPE_INPUT);
	if (ret) {
		LOGE("Set input device buffer init failed\n");
		return -1;
	}

	if (!mDstRect) {
		mDstRect = std::make_unique<RGARect>();
		if (!mDstRect) {
			LOGE("Cannot allocate output RGARect\n");
			return -1;
		}
	}

	mDstRect->copyRect(outRect);

	ret = setFormatDevice(RGA_CONFIG_TYPE_OUTPUT);
	if (ret) {
		LOGE("Set output device format failed\n");
		return -1;
	}

	ret = setBuffer(RGA_CONFIG_TYPE_OUTPUT);
	if (ret) {
		LOGE("Set output device buffer init failed\n");
		return -1;
	}

	return 0;
}

int RGA::setInputRGA(RGARect& inRect)
{
	int ret;
	
	if (!mSrcRect) {
		mSrcRect = std::make_unique<RGARect>();
		if (!mSrcRect) {
			LOGE("Cannot allocate input RGARect\n");
			return -1;
		}
	}

	mSrcRect->copyRect(inRect);

	ret = setFormatDevice(RGA_CONFIG_TYPE_INPUT);
	if (ret) {
		LOGE("Set input device format failed\n");
		return -1;
	}

	ret = setBuffer(RGA_CONFIG_TYPE_INPUT);
	if (ret) {
		LOGE("Set input device buffer init failed\n");
		return -1;
	}

	return 0;
}

int RGA::setOutputRGA(RGARect& inRect)
{
	int ret;
	
	if (!mDstRect) {
		mDstRect = std::make_unique<RGARect>();
		if (!mDstRect) {
			LOGE("Cannot allocate output RGARect\n");
			return -1;
		}
	}

	mDstRect->copyRect(inRect);

	ret = setFormatDevice(RGA_CONFIG_TYPE_OUTPUT);
	if (ret) {
		LOGE("Set output device format failed\n");
		return -1;
	}

	ret = setBuffer(RGA_CONFIG_TYPE_OUTPUT);
	if (ret) {
		LOGE("Set output device buffer init failed\n");
		return -1;
	}

	return 0;
}

int RGA::rgaConversion(MppFrame inFrame, MppFrame outFrame)
{
	if (!inFrame || !outFrame) {
		LOGE("Invalid parameters\n");
		return -1;
	}

	return 0;
}

int RGA::rgaConversion(int inFd, int outFd)
{
	struct v4l2_buffer buf = {0};
	int ret = 0;

	if (!mFD) {
	    LOGE("Failed to open device %s\n", RGA_DEVICE_PATH);
	    return -1;
	}
	
	if (!mSrcRect || !mDstRect) {
	    LOGE("Input or Output Rect is not configured\n");
	    return -1;
	}

	if (!mInputFmtSetDone || !mOutputFmtSetDone) {
		LOGE("Input or Output device format is not configured\n");
		return -1;
	}

	if (!mInputBufferCount || !mOutputFmtSetDone) {
		LOGE("Input or Output device buffer is not allocated\n");
		return -1;
	}

	if (!mIsInputStreamOn) {
		setStreamON(RGA_CONFIG_TYPE_INPUT);
	}

	if (!mIsOutputStreamOn) {
		setStreamON(RGA_CONFIG_TYPE_OUTPUT);
	}

	memset(&buf, 0, sizeof(buf));
	buf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	buf.memory = V4L2_MEMORY_DMABUF;
	buf.bytesused = mInputBufferSize;
	buf.index = 0;
	buf.m.fd = inFd;
	ret = ioctl(mFD, VIDIOC_QBUF, &buf);
	if (ret != 0) {
		LOGE("failed to ioctl VIDIOC_QBUF for %d %s.\n",
			errno, strerror(errno));
		return -1;
	}

	memset(&buf, 0, sizeof(buf));
	buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buf.memory = V4L2_MEMORY_DMABUF;
	buf.index = 0;
	buf.m.fd = outFd;
	ret = ioctl(mFD, VIDIOC_QBUF, &buf);
	if (ret != 0) {
		LOGE("failed to ioctl VIDIOC_QBUF for %d %s.\n",
				errno, strerror(errno));
		return -2;
	}

	memset(&buf, 0, sizeof(buf));
	buf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	buf.memory = V4L2_MEMORY_DMABUF;
	ret = ioctl(mFD, VIDIOC_DQBUF, &buf);
	if (ret != 0) {
		LOGE("failed to ioctl VIDIOC_DQBUF for %d %s.\n",
				errno, strerror(errno));
		return -3;
	}

	memset(&buf, 0, sizeof(buf));
	buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buf.memory = V4L2_MEMORY_DMABUF;
	ret = ioctl(mFD, VIDIOC_DQBUF, &buf);
	if (ret != 0) {
		LOGE("failed to ioctl VIDIOC_DQBUF for %d %s.\n",
				errno, strerror(errno));
		return -4;
	}

	return 0;
}

int RGA::rgaConversion(MppFrame inFrame, int outFd)
{
	LOGE("Not Implemented YET\n");
	
	return -1;
}

int RGA::openDevice()
{
	struct v4l2_capability cap;
	struct v4l2_format fmt;
	int ret;

	//mFD = open("/dev/v4l/by-path/platform-ff920000.rga-video-index0", O_RDWR | O_CLOEXEC, 0);
	mFD = open(RGA_DEVICE_PATH, O_RDWR);
	if (mFD < 0) {
	    LOGE("Failed to open device %s\n", RGA_DEVICE_PATH);
	    return -1;
	}

	ret = ioctl(mFD, VIDIOC_QUERYCAP, &cap);
	if (ret != 0) {
		LOGE("VIDIOC_QUERYCAP failed (ret=%d)\n", ret);
		return -1;
	}

	if (!(cap.capabilities & V4L2_CAP_VIDEO_M2M)) {
		LOGE("Device %s doesn't support V4L2_CAP_VIDEO_M2M\n", RGA_DEVICE_PATH);
		return -1;
	}

	if (!(cap.capabilities & V4L2_CAP_STREAMING)) {
		LOGE("Device %s doesn't support V4L2_CAP_STREAMING\n", RGA_DEVICE_PATH);
		return -1;
	}

	setRotation(0);

	return -1;	
}

void RGA::closeDevice()
{
	if (mFD >= 0) {
		LOGD("Close RGA Device\n");
		setStreamOFF(RGA_CONFIG_TYPE_INPUT);
		setStreamOFF(RGA_CONFIG_TYPE_OUTPUT);
		close(mFD);
		mFD = -1;
	}
}

int RGA::setFormatDevice(RGAConfigTypes type)
{
	struct v4l2_format fmt;
	struct v4l2_control ctrl;
	int ret;
	
	int width, height;
	enum v4l2_buf_type dev_type;
	int format;

	if (mFD < 0) {
		LOGE("RGA Device is not initalized\n");
		return -1;
	}

	if (type == RGA_CONFIG_TYPE_INPUT) {
		if (!mSrcRect) {
			LOGE("RGA Input RECT is not configured yet\n");
			return -1;
		}
		//width = mSrcRect->GetWidth();
		//height = mSrcRect->GetHeight(); 

		width = mSrcRect->GetStrideW();
		height = mSrcRect->GetStrideH(); 

		dev_type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
		format = getRGAFormat(mSrcRect->GetFormat());
		if (format == 0) {
			LOGE("Pixel format %d is not valid\n", mSrcRect->GetFormat());
			return -1;
		}
		LOGD("Set Input Format w:h=%d:%d, fmt=0x%x, buf_type=%s\n",width, height, format, (dev_type==V4L2_BUF_TYPE_VIDEO_OUTPUT) ? "OUTPUT" : "INVALID");
	}
	else {
		if (!mDstRect) {
			LOGE("RGA Output RECT is not configured yet\n");
			return -1;
		}

		//width = mDstRect->GetWidth();
		//height = mDstRect->GetHeight(); 

		width = mDstRect->GetStrideW();
		height = mDstRect->GetStrideH(); 

		dev_type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		format = getRGAFormat(mDstRect->GetFormat());
		if (format == 0) {
			LOGE("Pixel format %d is not valid\n", mDstRect->GetFormat());
			return -1;
		}

		LOGD("Set Output Format w:h=%d:%d, fmt=0x%x, buf_type=%s\n",width, height, format, (dev_type==V4L2_BUF_TYPE_VIDEO_CAPTURE) ? "CAPTURE" : "INVALID");

	}

	/* Set format for output */
	fmt.type = dev_type;
	fmt.fmt.pix.width = width;
	fmt.fmt.pix.height = height;
	fmt.fmt.pix.pixelformat = format;
	fmt.fmt.pix.field = V4L2_FIELD_ANY;

	ret = ioctl(mFD, VIDIOC_S_FMT, &fmt);
	if (ret != 0) {
		LOGE("VIDIOC_S_FMT failed\n");
		return -1;
	}

	if (type == RGA_CONFIG_TYPE_INPUT) {
		mInputFmtSetDone = true;
	}
	else {
		mOutputFmtSetDone = true;
	}

	return 0;
}

int RGA::setBuffer(RGAConfigTypes type)
{
	int ret, i;
	struct v4l2_buffer buf;
	struct v4l2_requestbuffers reqbuf;
	int buf_count = RGA_INPUT_BUFFER_COUNT;
	enum v4l2_buf_type dev_type;


	if (mFD < 0) {
		LOGE("RGA Device is not initalized\n");
		return -1;
	}

	if (type == RGA_CONFIG_TYPE_INPUT) {
		if (!mSrcRect) {
			LOGE("RGA Input RECT is not configured yet\n");
			return -1;
		}
		buf_count = RGA_INPUT_BUFFER_COUNT;
		dev_type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
		LOGD("Set Input buffer buf_count=%d, type=%s\n", buf_count, (dev_type==V4L2_BUF_TYPE_VIDEO_OUTPUT) ? "OUTPUT" : "INVALID");
	}
	else {
		if (!mDstRect) {
			LOGE("RGA Output RECT is not configured yet\n");
			return -1;
		}
		buf_count = RGA_OUTPUT_BUFFER_COUNT;
		dev_type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		LOGD("Set Output buffer buf_count=%d, type=%s\n", buf_count, (dev_type==V4L2_BUF_TYPE_VIDEO_CAPTURE) ? "CAPTURE" : "INVALID");
	}

	memset(&reqbuf, 0, sizeof(reqbuf));
	reqbuf.count = buf_count;
	reqbuf.type = dev_type;
	reqbuf.memory = V4L2_MEMORY_DMABUF;
	ret = ioctl(mFD, VIDIOC_REQBUFS, &reqbuf);
	if (ret != 0) {
		LOGE("VIDIOC_REQBUFS failed\n");
		return -1;
	}

	// TODO: Check buffer count allocated
	memset(&(buf), 0, sizeof(buf));
	for (int i=0; i<buf_count; i++) {
		buf.type = dev_type;
		buf.memory = V4L2_MEMORY_DMABUF;
		buf.index = i;
		
		ret = ioctl(mFD, VIDIOC_QUERYBUF, &buf);
		if (ret != 0) {
			LOGE("BUF[%d] : VIDIOC_QUERYBUF failed\n", i);
			return -1;
		}
		// bufer_size[i] = buf.length;
	}
	
	if (type == RGA_CONFIG_TYPE_INPUT) {
		mInputBufferCount = buf_count;
		mInputBufferSetDone = true;
		mInputBufferSize = buf.length;
		LOGD("VIDIOC_QUERYBUF[IN:%d] buf_length = %d, count=%d\n",buf.index, buf.length, reqbuf.count);
	}
	else {
		mOutputBufferCount = buf_count;
		mOutputBufferSetDone = true;
		mOutputBufferSize = buf.length;
		LOGD("VIDIOC_QUERYBUF[OUT:%d] buf_length = %d, count=%d\n",buf.index, buf.length, reqbuf.count);
	}

	return 0;
}

int RGA::setRotation(int degree)
{
	int ret;
	struct v4l2_control ctrl = {0};

	if (mFD < 0) {
		LOGE("RGA Device is not initalized\n");
		return -1;
	}

	if (mRotationSetDone)
		return 0;

	ctrl.id = V4L2_CID_ROTATE;
	ctrl.value = degree; 
	ret = ioctl(mFD, VIDIOC_S_CTRL, &ctrl);
	if (ret) {
		LOGE("failed to ioctrl VIDIOC_S_CTRL");
		return -1;
	}

	mRotationSetDone = true;
	return 0;
}

int RGA::setStreamON(RGAConfigTypes type)
{
	int ret;
	enum v4l2_buf_type buf_type;

	if (mFD < 0) {
		LOGE("RGA Device is not initalized\n");
		return -1;
	}

	if (type == RGA_CONFIG_TYPE_INPUT) {
		if (mIsInputStreamOn == true) {
			return 0;
		}
	
		buf_type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
		if (!mInputFmtSetDone || !mInputBufferCount) {
			LOGE("RGA Input configuration is not done\n");
			return -1;
		}

		LOGD("STREAM_ON : V4L2_BUF_TYPE_VIDEO_OUTPUT\n");
	}
	else {
		if (mIsOutputStreamOn == true) {
			return 0;
		}

		buf_type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		if (!mOutputFmtSetDone || !mOutputBufferCount) {
			LOGE("RGA Output configuration is not done\n");
			return -1;
		}
		LOGD("STREAM_ON : V4L2_BUF_TYPE_VIDEO_CAPTURE\n");
	}
	
	ret = ioctl(mFD, VIDIOC_STREAMON, &buf_type);
	if (ret != 0) {
		LOGE("VIDIOC_STREAMON failed\n");
		return -1;
	}

	if (type == RGA_CONFIG_TYPE_INPUT) {
		mIsInputStreamOn = true;
	}
	else {
		mIsOutputStreamOn = true;
	}

	return 0;
}

int RGA::setStreamOFF(RGAConfigTypes type)
{
	int ret;
	enum v4l2_buf_type buf_type;

	if (mFD < 0) {
		LOGE("RGA Device is not initalized\n");
		return -1;
	}

	if (type == RGA_CONFIG_TYPE_INPUT) {
		if (mIsInputStreamOn == false) {
			return 0;
		}
	
		buf_type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
		if (!mInputFmtSetDone || !mInputBufferCount) {
			LOGE("RGA Input configuration is not done\n");
			return -1;
		}
		LOGD("STREAM_OFF : V4L2_BUF_TYPE_VIDEO_OUTPUT\n");
	}
	else {
		if (mIsOutputStreamOn == false) {
			return 0;
		}

		buf_type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		if (!mOutputFmtSetDone || !mOutputBufferCount) {
			LOGE("RGA Output configuration is not done\n");
			return -1;
		}
		LOGD("STREAM_OFF : V4L2_BUF_TYPE_VIDEO_CAPTURE\n");
	}
	
	ret = ioctl(mFD, VIDIOC_STREAMOFF, &buf_type);
	if (ret != 0) {
		LOGE("VIDIOC_STREAMON failed\n");
		return -1;
	}

	if (type == RGA_CONFIG_TYPE_INPUT) {
		mIsInputStreamOn = false;
	}
	else {
		mIsOutputStreamOn = false;
	}

	return 0;
}


//} //namespace media

