#include "touch_packet_in.h"

TouchPacketIn::TouchPacketIn(byte *packet,int size){
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

  CRYPTER *crpyter = new CRYPTER(g_key);	
  int l = crpyter->decrypt(this->data,this->data_size,this->plain);
  std::cout << "touch_packet_in_plain_start" << std::endl;
  pnt_byte(this->plain,l);
  std::cout << "touch_packet_in_plain_end" << std::endl;

  event = new byte[1];
  memcpy(this->event,this->plain,1 * sizeof(byte));
  data1 = new byte[2];
  memcpy(this->data1,this->plain + 1,2 * sizeof(byte));
  token_size = new byte[2];
  memcpy(this->token_size,this->plain + 3,2 * sizeof(byte));
  int s = (int)token_size[1];
  token = new byte[s];
  memcpy(this->token,this->plain + 5,s * sizeof(byte));
  //memcpy(g_0825_token,this->token,s*sizeof(byte));
  data2 = new byte[6]; 
  memcpy(this->data2,this->plain + 5 + s,6 * sizeof(byte));
  time  = new byte[4];
  memcpy(this->time,this->plain + 11 + s,4 * sizeof(byte));
  local_ip = new byte[4];
  memcpy(this->local_ip,this->plain + 15 + s,4 * sizeof(byte));
  local_port = new byte[2];
  memcpy(this->local_port,this->plain + 19 + s,2 * sizeof(byte));
  success = new byte[2];
  memcpy(this->success,this->plain + 19 + s,2 * sizeof(byte));

  delete crpyter;

  
} 

TouchPacketIn::~TouchPacketIn(){
  delete[] event;
  delete[] data1;          //固定0x01 0x12
  delete[] token_size;     //token的长度
  delete[] token;          
  delete[] data2;          //固定0x00 0x17 0x00 0x0E 0x00 0x01
  delete[] local_ip;       //本地ip
  delete[] time;           //链接时间
  delete[] local_port;
  delete[] success;
}


