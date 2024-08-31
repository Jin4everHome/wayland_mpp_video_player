// Copyright 2017 The Cobalt Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef __MPP_VIDEO_FRAME_H__
#define __MPP_VIDEO_FRAME_H__

#include "video_frame.h"
#include "rk_type.h"
#include "log.h"

#ifdef TAG
#undef TAG
#define TAG "MediaCodecVideoFrame"
#endif

// If this is not defined, std::list will be used.
#define USE_DEQUE_FOR_VIDEO_FRAME_CONTAINER

#define DEBUG_DROP_FRAME 1
#define DEBUG_RENDER_FRAME 0
#define DEBUG_FRAMES 0

class MppVideoFrame : public VideoFrame
{
public:
	MppVideoFrame(MppFrame frame, int id)
	: VideoFrame(mpp_frame_get_eos(frame) ? -1 : mpp_frame_get_pts(frame))
	  frame_(frame),
	  id_(id),
	  released_(false) ) { }

	~MppVideoFrame() {
		if (!released_) {
			if (frame_) {
				mpp_frame_deinit(&frame_);
				frame_ = nullptr;
			}

			if (DEBUG_DROP_FRAME) {
				LOGD("MppVideoFrame::MppVideoFrame() : Video drop frame(index=%d, timestamp=%lld)\n", id_, getTimeStamp());
			}
		}
	}

	bool IsEndOfStream() const {
		if (mpp_frame_get_eos(frame)) {
			return true;
		} else {
			return false;
		}
	}

	

	void Render(int64_t release_time_in_nanoseconds, bool render) {
		if (!released_) {
			if (render) {
				if (release_time_in_nanoseconds > 0) {
					if (DEBUG_RENDER_FRAME) {
						LOGD("Video Render(%d) @ %lld", id_, release_time_in_nanoseconds);
					}
					media_codec_bridge_->ReleaseOutputBufferAtTimestamp(dequeue_output_result_.index, release_time_in_nanoseconds);
				}
				else {
					if (DEBUG_RENDER_FRAME) {
						LOGD("Video Render(%d) a farme\n", dequeue_output_result_.index);
					}
					media_codec_bridge_->ReleaseOutputBuffer(dequeue_output_result_.index, true);
				}
			}
			else {
				/* Drop frame */
				if (DEBUG_RENDER_FRAME) {
					LOGD("Video Drop a farme(index=%d, timestamp=%lld)\n", dequeue_output_result_.index, getTimeStamp());
				}
				media_codec_bridge_->ReleaseOutputBuffer(dequeue_output_result_.index, false);
			}
			released_ = true;
		}
		else {
			LOGE("Trying double free error(Render)\n");
		}
	}

	int index() const { return id_; };
	void skipRelease() { released_ = true; }

private:
	MppFrame frame_ = nullptr;
	int id_ = -1;
	volatile bool released_ = false;
};
#endif // __NATIVE_MEDIACODEC_VIDEO_FRAME_H__
