#include "base_packet_out.h"

PacketOut::PacketOut(){
}

void PacketOut::create_packet(byte *c,byte *s){
  this->sequence = new byte[2];
  this->command  = new byte[2];
  memcpy(this->sequence,s,2 * sizeof(byte));
  memcpy(this->command ,c,2 * sizeof(byte));

  //this->gen_packet();
}

byte* PacketOut::get_data(){
  return this->data;
}



PacketOut::~PacketOut(){
  delete[] this->command;
  delete[] this->sequence;
}

