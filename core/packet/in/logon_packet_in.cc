#include "logon_packet_in.h"

LogonPacketIn::LogonPacketIn(byte *packet,int size){
  PacketIn::set_packet(packet,size);
  /*
  int len  = size - 15;
  head     = new byte[1];
  version  = new byte[2];
  command  = new byte[2];
  sequence = new byte[2];
  id       = new byte[4];
  threeZero = new byte[3];
  data     = new byte[len];
  end      = new byte[1];


  memcpy(head    ,packet     ,1 * sizeof(byte));
  memcpy(version ,packet +  1,2 * sizeof(byte));
  memcpy(command ,packet +  3,2 * sizeof(byte));
  memcpy(sequence,packet +  5,2 * sizeof(byte));
  memcpy(id      ,packet +  7,4 * sizeof(byte));
  memcpy(threeZero,packet+ 11,3 * sizeof(byte));
  memcpy(data    ,packet + 14,len * sizeof(byte));
  memcpy(end     ,packet + len+14,1 * sizeof(byte));
  */

  CRYPTER *crpyter = new CRYPTER(g_0826_key);	
  int l = crpyter->decrypt(this->data,this->data_size,this->plain);
  std::cout << "logon_packet_in_plain_start" << std::endl;
  pnt_byte(this->plain,l);
  std::cout << "logon_packet_in_plain_end" << std::endl;


  delete crpyter;

  
} 

LogonPacketIn::~LogonPacketIn(){

}


