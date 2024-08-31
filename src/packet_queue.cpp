#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

#include <vector>
#include "packet_queue.h"

#include "log.h"

#include <xf86drm.h>


#ifdef TAG
#undef TAG
#define TAG "PacketQueue"
#endif

static uint8_t eos_data[] = "EOS";

PacketQueue::PacketQueue()
{
	duration_  = 0LL;
	dataSize_  = 0;
	numPacket_ = 0;
	stream_id  = 0;
	av_init_packet(&eos_pkt);
	//strcpy((char*)eos_pkt.data, "EOS");
	eos_pkt.data = eos_data;
	
	packetQueue_.clear();
	initialized_ = true;
}

PacketQueue::PacketQueue(int stream_idx)
{
	duration_ = 0LL;
	dataSize_ = 0;
	numPacket_ = 0;

	stream_id = stream_idx;

	av_init_packet(&eos_pkt);
	eos_pkt.stream_index = stream_idx;
	eos_pkt.data = eos_data;
	packetQueue_.clear();

	initialized_ = true;
}

PacketQueue::~PacketQueue()
{
    // Deque all packet
	std::unique_lock<std::mutex> guard(lock_);
	clearPacketsLocked();
	initialized_ = false;
}

int PacketQueue::push_back(AVPacket *pkt)
{
	AVPacket *pkt1 = nullptr;

	if (!pkt)
	{
		return -1;
	}

	if (pkt != &eos_pkt) {
		pkt1 = av_packet_alloc();
		if (!pkt1) {
			av_packet_unref(pkt);
			return -1;
		}
		
		/* copy pkt and init src pkt*/
		av_packet_move_ref(pkt1, pkt);
	}
	else {
		// EOS Packet
		pkt1 = pkt;
	}

	std::unique_lock<std::mutex> guard(lock_);

	dataSize_ += pkt1->size;
	if (pkt1->duration > 0) {
		duration_ += pkt1->duration;
	}
	numPacket_++;
	packetQueue_.push_back(pkt1);

	if (numPacket_ != packetQueue_.size()) {
		LOGW("Packet Push Queue Count mismatch %d != %d\n", numPacket_, packetQueue_.size());
	}

	return 0;
}

int PacketQueue::push_front(AVPacket *pkt)
{
	AVPacket *pkt1 = nullptr;

	if (!pkt)
	{
		return -1;
	}

	if (pkt != &eos_pkt) {
		pkt1 = av_packet_alloc();
		if (!pkt1) {
			av_packet_unref(pkt);
			return -1;
		}
		/* copy pkt and init src pkt*/
		av_packet_move_ref(pkt1, pkt);
	}
	else {
		pkt1 = pkt;
	}

	std::unique_lock<std::mutex> guard(lock_);

	dataSize_ += pkt1->size;
	if (pkt1->duration > 0) {
		duration_ += pkt1->duration;
	}
	numPacket_++;
	packetQueue_.push_front(pkt1);

	if (numPacket_ != packetQueue_.size()) {
		LOGW("Packet Push Queue Count mismatch %d != %d\n", numPacket_, packetQueue_.size());
	}

	return 0;
}

int PacketQueue::pop_front(AVPacket** packet)
{
	int ret = 0;

	AVPacket *pkt1= nullptr;

	std::unique_lock<std::mutex> guard(lock_);

	if (packetQueue_.size() > 0 && !packetQueue_.empty())
	{
		int eos = 0;

		pkt1 = packetQueue_.front();
		if (!pkt1) {
			LOGE("No packet found whiel pop_front()\n");
			ret = -1;
			goto exit_;
		}

		if (pkt1 != &eos_pkt) {
			av_packet_move_ref(*packet, pkt1);
			av_packet_free(&pkt1);
		}
		else {
			*packet = &eos_pkt;
			eos = 1;
		}

		packetQueue_.erase(packetQueue_.begin()); //packetQueue.pop_front();
		numPacket_--;

		if (numPacket_ != packetQueue_.size()) {
			LOGW("Packet Pop Queue Count mismatch %d != %d\n", numPacket_, packetQueue_.size());
		}

		if (numPacket_ < 0) {
			// someghint wrong.
			LOGW("Packet count(%d) should not < 0\n", numPacket_);
			clearPacketsLocked();
			ret = -1;
			goto exit_;
		}

		if (!eos) {
			if ((*packet)->duration > 0) {
				duration_ -= (*packet)->duration;
			}
			dataSize_ -= (*packet)->size;
		}
	}
	else {
		usleep(1000);
		ret = -1;
	}

exit_:

	return ret;
}


int PacketQueue::pop_front(AVPacket* packet)
{
	int ret = 0;

	AVPacket *pkt1= nullptr;

	std::unique_lock<std::mutex> guard(lock_);

	if (packetQueue_.size() > 0 && !packetQueue_.empty())
	{
		int eos = 0;

		pkt1 = packetQueue_.front();
		if (!pkt1) {
			LOGE("No packet found whiel pop_front()\n");
			ret = -1;
			goto exit_;
		}

		if (pkt1 != &eos_pkt) {
			av_packet_move_ref(packet, pkt1);
			av_packet_free(&pkt1);
		}
		else {
			// TODO: mark eos packet by data
			av_init_packet(packet);
			packet->data = eos_pkt.data;
			packet->pts = eos_pkt.pts;
			eos = 1;
			//LOGE("[DEBUG] Queue Pop EOS Packet (PTS=%lld, data=%s)\n", packet->pts, packet->data);
		}

		packetQueue_.erase(packetQueue_.begin()); //packetQueue.pop_front();
		numPacket_--;

		if (numPacket_ != packetQueue_.size()) {
			LOGW("Packet Pop Queue Count mismatch %d != %d\n", numPacket_, packetQueue_.size());
		}

		if (numPacket_ < 0) {
			// someghint wrong.
			LOGW("Packet count(%d) should not < 0\n", numPacket_);
			clearPacketsLocked();
			ret = -1;
			goto exit_;
		}

		if (!eos) {
			if (packet->duration > 0) {
				duration_ -= packet->duration;
			}
			dataSize_ -= packet->size;
		}
	}
	else {
		usleep(1000);
		ret = -1;
	}

exit_:
	return ret;
}

int PacketQueue::pop_front()
{
	int ret = 0;

	AVPacket *pkt1= nullptr;
	uint64_t duration = 0LL;
	int dataSize = 0;

	std::unique_lock<std::mutex> guard(lock_);

	if (packetQueue_.size() > 0 && !packetQueue_.empty())
	{
		int eos = 0;

		pkt1 = packetQueue_.front();
		if (!pkt1) {
			LOGE("No packet found whiel pop_front()\n");
			ret = -1;
			goto exit_;
		}

		if (pkt1 != &eos_pkt) {
			duration = pkt1->duration;
			dataSize = pkt1->size;
			av_packet_free(&pkt1);
		}
		else {
			eos = 1;
			//LOGE("[DEBUG] Queue Pop EOS Packet (PTS=%lld, data=%s)\n", packet->pts, packet->data);
		}

		packetQueue_.erase(packetQueue_.begin()); //packetQueue.pop_front();
		numPacket_--;

		if (numPacket_ != packetQueue_.size()) {
			LOGW("Packet Pop Queue Count mismatch %d != %d\n", numPacket_, packetQueue_.size());
		}

		if (numPacket_ < 0) {
			// someghint wrong.
			LOGW("Packet count(%d) should not < 0\n", numPacket_);
			clearPacketsLocked();
			ret = -1;
			goto exit_;
		}

		if (!eos) {
			if (duration > 0) {
				duration_ -= duration;
			}
			dataSize_ -= dataSize;
		}
	}
	else {
		usleep(1000);
		ret = -1;
	}

exit_:
	return ret;
}


int PacketQueue::pop_back(AVPacket** packet)
{
	int ret = 0;

	AVPacket *pkt1= nullptr;

	std::unique_lock<std::mutex> guard(lock_);

	if (packetQueue_.size() > 0 && !packetQueue_.empty())
	{
		int eos = 0;

		pkt1 = packetQueue_.back();
		if (!pkt1) {
			LOGE("No packet found whiel pop_front()\n");
			ret = -1;
			goto exit_;
		}

		if (pkt1 != &eos_pkt) {
			av_packet_move_ref(*packet, pkt1);
			av_packet_free(&pkt1);
		}
		else {
			*packet = &eos_pkt;
			eos = 1;
		}

		packetQueue_.pop_back();
		numPacket_--;

		if (numPacket_ != packetQueue_.size()) {
			LOGW("Packet Pop Queue Count mismatch %d != %d\n", numPacket_, packetQueue_.size());
		}

		if (numPacket_ < 0) {
			// someghint wrong.
			LOGW("Packet count(%d) should not < 0\n", numPacket_);
			clearPacketsLocked();
			ret = -1;
			goto exit_;
		}

		if (!eos) {
			if ((*packet)->duration > 0) {
				duration_ -= (*packet)->duration;
			}
			dataSize_ -= (*packet)->size;
		}
	}
	else {
		usleep(1000);
		ret = -1;
	}

exit_:

	return ret;
}

int PacketQueue::pop_back(AVPacket *packet)
{
	int ret = 0;

	AVPacket *pkt1= nullptr;

	std::unique_lock<std::mutex> guard(lock_);

	if (packetQueue_.size() > 0 && !packetQueue_.empty())
	{
		int eos = 0;

		pkt1 = packetQueue_.back();
		if (!pkt1) {
			LOGE("No packet found whiel pop_front()\n");
			ret = -1;
			goto exit_;
		}

		if (pkt1 != &eos_pkt) {
			av_packet_move_ref(packet, pkt1);
			av_packet_free(&pkt1);
		}
		else {
			// TODO: mark eos packet by data
			av_init_packet(packet);
			packet->data = eos_pkt.data;
			packet->pts = eos_pkt.pts;
			eos = 1;
		}

		packetQueue_.pop_back();
		numPacket_--;

		if (numPacket_ != packetQueue_.size()) {
			LOGW("Packet Pop Queue Count mismatch %d != %d\n", numPacket_, packetQueue_.size());
		}

		if (numPacket_ < 0) {
			// someghint wrong.
			LOGW("Packet count(%d) should not < 0\n", numPacket_);
			clearPacketsLocked();
			ret = -1;
			goto exit_;
		}

		if (!eos) {
			if (packet->duration > 0) {
				duration_ -= packet->duration;
			}
			dataSize_ -= packet->size;
		}
	}
	else
	{
		usleep(1000);
		ret = -1;
	}

exit_:
	return ret;
}

int PacketQueue::pop_back()
{
	int ret = 0;

	AVPacket *pkt1= nullptr;
	uint64_t duration = 0LL;
	int dataSize = 0;
	std::unique_lock<std::mutex> guard(lock_);

	if (packetQueue_.size() > 0 && !packetQueue_.empty())
	{
		int eos = 0;

		pkt1 = packetQueue_.back();
		if (!pkt1) {
			LOGE("No packet found whiel pop_front()\n");
			ret = -1;
			goto exit_;
		}

		if (pkt1 != &eos_pkt) {
			duration = pkt1->duration;
			dataSize = pkt1->size;
			av_packet_free(&pkt1);
		}
		else {
			eos = 1;
		}

		packetQueue_.pop_back();
		numPacket_--;

		if (numPacket_ != packetQueue_.size()) {
			LOGW("Packet Pop Queue Count mismatch %d != %d\n", numPacket_, packetQueue_.size());
		}

		if (numPacket_ < 0) {
			// someghint wrong.
			LOGW("Packet count(%d) should not < 0\n", numPacket_);
			clearPacketsLocked();
			ret = -1;
			goto exit_;
		}

		if (!eos) {
			if (duration > 0) {
				duration_ -= duration;
			}
			dataSize_ -= dataSize;
		}
	}
	else {
		usleep(1000);
		ret = -1;
	}

exit_:

	return ret;
}


AVPacket* PacketQueue::front()
{
	std::unique_lock<std::mutex> guard(lock_);

	if (packetQueue_.size() > 0)
	{
		return packetQueue_.front();
	}

	return nullptr;
}

AVPacket* PacketQueue::back()
{
	std::unique_lock<std::mutex> guard(lock_);

	if (packetQueue_.size() > 0)
	{
		return packetQueue_.back();
	}

	return nullptr;
}

bool PacketQueue::empty()
{
	bool isEmpty = false;

	std::unique_lock<std::mutex> guard(lock_);

	isEmpty = packetQueue_.empty();
	if (isEmpty && numPacket_ != 0) {
		LOGD("PacketQueue count mismatch (queue(empty) != numpacket(%d)\n", numPacket_);
	}

	return isEmpty;
}

void PacketQueue::clear()
{
	std::unique_lock<std::mutex> guard(lock_);
	clearPacketsLocked();
}

int PacketQueue::getSize()
{
	int size_ = 0;

	std::unique_lock<std::mutex> guard(lock_);
	size_ = packetQueue_.size();

	return size_;
}

uint64_t PacketQueue::getDuration()
{
	uint64_t duration_calc = 0LL;

	std::unique_lock<std::mutex> guard(lock_);

	if (duration_ > 0) {
		duration_calc = duration_;
	}
	else {
		if (packetQueue_.size() > 1) {
			AVPacket *pkt_front= nullptr, *pkt_back= nullptr;
			pkt_front = packetQueue_.front();
			pkt_back = packetQueue_.back();
			if (pkt_front && pkt_back && (pkt_front->pts > 0 && pkt_back->pts > 0)) {
				if (pkt_back->pts > pkt_front->pts) {
					duration_calc = pkt_back->pts - pkt_front->pts;
				}
			}
		}
	}

	return duration_calc;
}

int PacketQueue::getDataSize()
{
	std::unique_lock<std::mutex> guard(lock_);

	return dataSize_;
}

void PacketQueue::clearPacketsLocked()
{
	while (!packetQueue_.empty())
	{
		AVPacket *packet = packetQueue_.front();
		if (packet) {
			packetQueue_.erase(packetQueue_.begin());
			if (packet != &eos_pkt) {
				av_packet_free(&packet);
				packet = nullptr;
				numPacket_--;
			}
			else {
				LOGD("skip delete EOS static packet(left=%d)\n", numPacket_);
				break;
			}
		}
		else
		{
			LOGW("Packet count mismatch : !empty() but no packet exist\n");
			break;
		}
	}

	numPacket_= 0;
	duration_ = 0;
	dataSize_ = 0;
}

