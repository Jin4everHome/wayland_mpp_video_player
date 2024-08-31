#ifndef MEDIA_FILTERS_ROCKCHIP_RGA_RECT_H_
#define MEDIA_FILTERS_ROCKCHIP_RGA_RECT_H_

#include "rockchip/rk_mpi.h"
#include <memory>

//namespace media {

class RGARect {
public:
	RGARect()
		: mX(0),
		  mY(0),
		  mWidth(0),
		  mHeight(0),
		  mStrideW(0),
		  mStrideH(0),
		  mFormat(MPP_FMT_YUV420SP) {}

	//~RGARect();
	RGARect(int width, int height, MppFrameFormat format)
		: mX(0),
		  mY(0),
		  mWidth(width),
		  mHeight(height),
		  mFormat(format) {

		#define ALIGN_SIZE(x, a)   (((x)+(a)-1)&~((a)-1))

		mStrideW = ALIGN_SIZE(width, 16);
		mStrideH = ALIGN_SIZE(height, 16);
    } 

	RGARect(int width, int height, int strideW, int strideH, MppFrameFormat format)
		: mX(0),
		  mY(0),
		  mWidth(width),
		  mHeight(height),
		  mStrideW(strideW),
		  mStrideH(strideH),
		  mFormat(format) {} 

	RGARect(int x, int y, int width, int height, int strideW, int strideH, MppFrameFormat format)
		: mX(x),
		  mY(y),
		  mWidth(width),
		  mHeight(height),
		  mStrideW(strideW),
		  mStrideH(strideH),
		  mFormat(format) {}

	/* copy constructor */
	RGARect(RGARect &rect) {
		mX = rect.GetOffsetX();
		mY = rect.GetOffsetY();
		mWidth = rect.GetWidth();
		mHeight = rect.GetHeight();
		mStrideW = rect.GetStrideW();
		mStrideH = rect.GetStrideH();
		mFormat = rect.GetFormat();
	}

	static std::unique_ptr<RGARect> CreateRGARect(int width, int height, MppFrameFormat format)
	{
		std::unique_ptr<RGARect> rga_rect = std::make_unique<RGARect>(width, height, format);

		if (!rga_rect) {
			return nullptr;
		}

		return std::move(rga_rect);
	}

	static std::unique_ptr<RGARect> CreateRGARect(int width, int height, int strideW, int strideH, MppFrameFormat format)
	{
		std::unique_ptr<RGARect> rga_rect = std::make_unique<RGARect>(width, height, strideW, strideH, format);

		if (!rga_rect) {
			return nullptr;
		}

		return std::move(rga_rect);
	}

	static std::unique_ptr<RGARect> CreateRGARect(int x, int y, int width, int height, int strideW, int strideH, MppFrameFormat format)
	{
		std::unique_ptr<RGARect> rga_rect = std::make_unique<RGARect>(x, y, width, height, strideW, strideH, format);

		if (!rga_rect) {
			return nullptr;
		}

		return std::move(rga_rect);
	}

	void copyRect(RGARect& rect) {
		mX = rect.GetOffsetX();
		mY = rect.GetOffsetY();
		mWidth = rect.GetWidth();
		mHeight = rect.GetHeight();
		mStrideW = rect.GetStrideW();
		mStrideH = rect.GetStrideH();
		mFormat = rect.GetFormat();
	}

	void copyRect(RGARect* rect) {
		if (!rect) {
			return;
		}
		mX = rect->GetOffsetX();
		mY = rect->GetOffsetY();
		mWidth = rect->GetWidth();
		mHeight = rect->GetHeight();
		mStrideW = rect->GetStrideW();
		mStrideH = rect->GetStrideH();
		mFormat = rect->GetFormat();
	}

	int GetOffsetX() const {return mX;}
	int GetOffsetY() const {return mY;}
	int GetWidth() const {return mWidth;}
	int GetHeight() const {return mHeight;}
	int GetStrideW() const {return mStrideW;}
	int GetStrideH() const {return mStrideH;}
	MppFrameFormat GetFormat() const {return mFormat;}

	void SetOffsetX(int v) {mX = v;}
	void SetOffsetY(int v) {mY = v;}
	void SetWidth(int v) {mWidth = v;}
	void SetHeight(int v) {mHeight = v;}
	void SetStrideW(int v) {mStrideW = v;}
	void SetStrideH(int v) {mStrideH = v;}
	void SetFormat(MppFrameFormat v) {mFormat = v;}

private:
	int mX;
	int mY;
	int mWidth;
	int mHeight;
	int mStrideW;
	int mStrideH;
	MppFrameFormat mFormat;
};

//} // nanespace media

#endif // MEDIA_FILTERS_ROCKCHIP_RGA_RECT_H_
