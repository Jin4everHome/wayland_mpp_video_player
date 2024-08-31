#ifndef __NATIVE_PACKET_QUEUE__
#define __NATIVE_PACKET_QUEUE__

#include <stdint.h>

#include <deque>
#include <mutex>

extern "C" {
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
}

using namespace std;

class PacketQueue {

public:
	PacketQueue();
	PacketQueue(int stream_idx);
	~PacketQueue();

	int push_back(AVPacket *pkt);
	int push_front(AVPacket *pkt);    // will not be used.

	int pop_front(AVPacket* pkt);     // will be deplecated.
	int pop_front(AVPacket** packet);
	int pop_front( ); // pop and free

	int pop_back(AVPacket* pkt);      // will be deplecated.
	int pop_back(AVPacket** packet);
	int pop_back( ); // pop and free

	AVPacket* front();
	AVPacket* back();

	bool empty();
	void clear(); // flush

	int getSize(); // number of elments
	int getDataSize(); // Total Data Size, will be deprecated.
	uint64_t getDuration();

	int getStreamId( ) const {return stream_id;}
	int  stream_id;
	AVPacket eos_pkt;

private:
	bool initialized_;

	uint64_t duration_;
	int  dataSize_;
	int  numPacket_;

	std::deque<AVPacket *> packetQueue_;
	std::mutex lock_;

	void clearPacketsLocked(); // clear all packet.
};

#endif // __NATIVE_PACKET_QUEUE__

