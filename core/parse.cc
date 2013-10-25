#include "parse.h"

Parse::Parse(){

}

Parse::~Parse(){
  delete[] data;
  delete[] head;
  delete[] version;
  delete[] command;
  delete[] sequence;
  delete[] id;
  delete[] threeZero;
  delete[] event_command;
}

void Parse::set_packet(byte *packet,int size){
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

  CRYPTER *crpyter = new CRYPTER(g_key);	
  byte *result = NULL;
  int l = crpyter->decrypt(this->data,len,result);
  pnt_byte(result,l);

  event_command = new byte[1];
  memcpy(this->event_command,result,1 * sizeof(byte));
  //pnt_byte(this->event_command,1);
  delete crpyter;
  

};
