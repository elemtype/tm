#ifndef BASE_PACKET_OUT_H
#define BASE_PACKET_OUT_H

#include "../base_packet.h"

class PacketOut : public Packet{

 public:
  PacketOut();
  void create_packet(byte*,byte*);
  byte *get_data();
  virtual ~PacketOut();
  virtual void gen_packet(){};
};

#endif
