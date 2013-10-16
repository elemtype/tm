#ifndef BASE_PACKET_IN_H
#define BASE_PACKET_IN_H

#include "../base_packet.h"

class PacketIn : public Packet{

 public:
  byte *packet;     //收到的包

  byte *id;         //登录ID
  byte *threeZero;  //存放包体的三个0
  byte *plain;      //存放解密的明文

  PacketIn();
  virtual ~PacketIn();
  void set_packet(byte*,int);
};

#endif
