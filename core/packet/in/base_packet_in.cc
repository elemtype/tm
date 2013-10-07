#include "base_packet_in.h"

PacketIn::PacketIn(){
}

PacketIn::PacketIn(byte *s){
  this->sequence = new byte[2];
  memcpy(this->sequence,s,2 * sizeof(byte));

  //this->gen_packet();
}

byte* PacketIn::get_data(){
  return this->data;
}



PacketIn::~PacketIn(){
  delete[] this->sequence;
  delete[] this->data;
}

