#include "base_packet.h"

Packet::Packet(){
  this->head    = new byte;
  this->head[0] = 0x02;
  this->version = new byte[2];
  this->version[0] = 0x30;
  this->version[1] = 0x18;
  this->end    = new byte;
  this->end[0] = 0x03; 
}

Packet::~Packet(){
  delete this->head;
  delete this->version;
  delete this->end;
}


