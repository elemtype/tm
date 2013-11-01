#ifndef LOGIN_PACKCET_OUT_H
#define LOGIN_PACKET_OUT_H

#include "base_packet_out.h"
#include <openssl/md5.h>

class LoginPacketOut : public PacketOut{

 public:
  LoginPacketOut(byte*);
  ~LoginPacketOut();

  virtual void gen_packet();
};

#endif
