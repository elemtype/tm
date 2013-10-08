#ifndef TOUCH_PACKET_IN_H
#define TOUCH_PACKET_IN_H

#include "base_packet_in.h"

class TouchPacketIn : public PacketIn{

 public:
  TouchPacketIn(byte*);
  ~TouchPacketIn();
};

#endif
