#ifndef LOGON_PACKCET_OUT_H
#define LOGON_PACKET_OUT_H

#include "base_packet_out.h"

class LogonPacketOut : public PacketOut{

 public:
  LogonPacketOut(byte*);
  ~LogonPacketOut();
};

#endif
