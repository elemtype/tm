#ifndef BASE_PACKET_H
#define BASE_PACKET_H

#include "../../common/util.h"
#include "../../common/common.h"

#define MARK02       0x02            //0x02标识，QQ协议以0x02开始
#define VERSION      0x30,0x18       //TM2013版本号
#define MARK03       0x03            //0x03标识，QQ协议以0x03结尾

class Packet
{
 public:
  Packet();
  virtual ~Packet();
 
 private:
  static const byte head;
  static const byte version[];
  static const byte end;

 protected:  
  byte *command;
  byte *data;
  byte *sequence;
};
#endif
