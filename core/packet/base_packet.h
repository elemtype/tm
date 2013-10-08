#ifndef BASE_PACKET_H
#define BASE_PACKET_H

#include "../../common/util.h"
#include "../../common/common.h"
#include "../../crypter/crypter.h"

#define MARK02       0x02            //0x02标识，QQ协议以0x02开始
#define VERSION      0x30,0x18       //TM2013版本号
#define MARK03       0x03            //0x03标识，QQ协议以0x03结尾

class Packet
{
 public:
  Packet();
  virtual ~Packet();
 
 protected:
  byte *head;
  byte *version;
  byte *end; 
  
  byte *command;
  byte *data;
  byte *sequence;
};
#endif
