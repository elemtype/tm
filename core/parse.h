#ifndef PARSE_H
#define PARSE_H

#include "../common/util.h"
#include "../common/common.h"
#include "../common/global.h"
#include "../crypter/crypter.h"

class Parse{
 public:
  byte *head;
  byte *version;
  byte *command;
  byte *sequence;
  byte *id;
  byte *threeZero;
  byte *data;
  byte *end;
  byte *event_command;
  
  Parse();
  void set_packet(byte*,int);
  ~Parse();
};

#endif
