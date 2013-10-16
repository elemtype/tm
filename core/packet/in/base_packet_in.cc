#include "base_packet_in.h"

PacketIn::PacketIn(){
}


PacketIn::~PacketIn(){
}

void PacketIn::set_packet(byte *p,int l){
  this->packet = new byte[l];
  memcpy(this->packet,p,l * sizeof(byte));

  this->data_size  = l - 15;
  head     = new byte[1];
  version  = new byte[2];
  command  = new byte[2];
  sequence = new byte[2];
  id       = new byte[4];
  threeZero = new byte[3];
  data     = new byte[this->data_size];
  end      = new byte[1];

  memcpy(head    ,p     ,1 * sizeof(byte));
  memcpy(version ,p +  1,2 * sizeof(byte));
  memcpy(command ,p +  3,2 * sizeof(byte));
  memcpy(sequence,p +  5,2 * sizeof(byte));
  memcpy(id      ,p +  7,4 * sizeof(byte));
  memcpy(threeZero,p+ 11,3 * sizeof(byte));
  memcpy(data    ,p + 14,this->data_size * sizeof(byte));
  memcpy(end     ,p + this->data_size+14,1 * sizeof(byte));
}

