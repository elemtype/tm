#ifndef BASE_PACKET_IN_H
#define BASE_PACKET_IN_H

#include "../base_packet.h"

class PacketIn : public Packet{

 public:
  PacketIn();
  void create_packet(byte*,byte*);
  byte *get_data();
  virtual ~PacketIn();
  virtual void gen_packet();
};

#endif
