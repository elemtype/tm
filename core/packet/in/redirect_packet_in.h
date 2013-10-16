#ifndef REDIRECT_PACKET_IN_H
#define REDIRECT_PACKET_IN_H

#include "base_packet_in.h"

class RedirectPacketIn : public PacketIn{

 public:
  byte *event;
  byte *data1;          //固定0x01 0x12
  byte *token_size;     //token的长度
  byte *token;          
  byte *data2;          //固定0x00 0x17 0x00 0x0E 0x00 0x01
  byte *time;           //链接时间
  byte *local_ip;       //本地ip
  byte *data3;
  byte *server_ip;      //服务器ip
  byte *sixZero;

  RedirectPacketIn(byte*,int);
  ~RedirectPacketIn();
};

#endif
