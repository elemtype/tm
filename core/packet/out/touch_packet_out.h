#ifndef TOUCH_PACKET_OUT_H
#define TOUCH_PACKET_OUT_H

#include "base_packet_out.h"

class TouchPacketOut : public PacketOut{

 public:
  TouchPacketOut(byte*);
  ~TouchPacketOut();
};

#endif
