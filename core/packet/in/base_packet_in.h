#ifndef BASE_PACKET_IN_H
#define BASE_PACKET_IN_H

#include "../base_packet.h"

class PacketIn : public Packet{

 public:
  PacketIn();
  PacketIn(byte*);
  byte *get_data();
  virtual ~PacketIn();
 private:
  virtual void gen_packet();
};

#endif
