#ifndef LOGIN_PACKET_IN_H
#define LOGIN_PACKET_IN_H

#include "base_packet_in.h"

class LoginPacketIn : public PacketIn{

 public:
   LoginPacketIn(byte*,int);
  ~LoginPacketIn();
};

#endif
