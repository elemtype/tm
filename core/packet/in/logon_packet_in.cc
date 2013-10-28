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


  memcpy(g_0828_key_0,this->plain + 7,16 * sizeof(byte));
  std::cout << "g_0828_key_0_start" << std::endl;
  pnt_byte(g_0828_key_0,16);
  std::cout << "g_0828_key_0_end" << std::endl;

  std::cout << "g_0826_token_start" << std::endl;
  memcpy(g_0826_token,this->plain + 25,0x38 * sizeof(byte));
  pnt_byte(g_0826_token,0x38);
  std::cout << "g_0826_token_end" << std::endl;

  memcpy(g_0828_key_1,this->plain + 16  * 15 - 5,16 * sizeof(byte));
  std::cout << "g_0828_key_1_start" << std::endl;
  pnt_byte(g_0828_key_1,16);
  std::cout << "g_0828_key_1_end" << std::endl;


  delete crpyter;

  
} 

LogonPacketIn::~LogonPacketIn(){

}


