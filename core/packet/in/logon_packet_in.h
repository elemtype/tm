#ifndef LOGON_PACKET_IN_H
#define LOGON_PACKET_IN_H

#include "base_packet_in.h"

class LogonPacketIn : public PacketIn{

 public:
   LogonPacketIn(byte*,int);
  ~LogonPacketIn();
};

#endif
