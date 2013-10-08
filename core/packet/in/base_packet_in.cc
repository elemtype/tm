#include "base_packet_in.h"

PacketIn::PacketIn(){
}

void PacketIn::create_packet(byte *c,byte *s){
  this->sequence = new byte[2];
  this->command  = new byte[2];
  memcpy(this->sequence,s,2 * sizeof(byte));
  memcpy(this->command ,c,2 * sizeof(byte));

  //this->gen_packet();
}

byte* PacketIn::get_data(){
  return this->data;
}



PacketIn::~PacketIn(){
  delete[] this->command;
  delete[] this->sequence;
}

