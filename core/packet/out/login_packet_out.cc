#include "login_packet_out.h"

LoginPacketOut::LoginPacketOut(byte *s){
  
  byte c[] = {0x08,0x28};
  PacketOut::create_packet(c,s);
} 

LoginPacketOut::~LoginPacketOut(){
  delete[] this->data;
}


void LoginPacketOut::gen_packet(){
/*
  int crypt_size = 0;
  byte *crypt = NULL;
  crpyter = new CRYPTER(tea_key);	
  crypt_size = crpyter->encrypt(plain,443,crypt);
  //std::cout << crypt_size << std::endl;
  //pnt_byte(plain,443);
  //pnt_byte(crypt,crypt_size);
  delete crpyter;

  int offset = 0,size = 499,len = 0;
  data = new byte[size];

  offset = 1; 
  memcpy(this->data + len,this->head,offset * sizeof(byte));
  len    = len + offset; 

  offset = 2; 
  memcpy(this->data + len,this->version,offset * sizeof(byte));
  len    = len + offset; 

  offset = 2; 
  memcpy(this->data + len,this->command,offset * sizeof(byte));
  len    = len + offset; 

  offset = 2; 
  memcpy(this->data + len,this->sequence,offset * sizeof(byte));
  len    = len + offset; 

  offset = 4; 
  memcpy(this->data + len,g_id,offset * sizeof(byte));
  len    = len + offset; 

  offset = 15; 
  memcpy(this->data + len,rand15byte,offset * sizeof(byte));
  len    = len + offset; 

  offset = 16; 
  memcpy(this->data + len,tea_key,offset * sizeof(byte));
  len    = len + offset; 

  offset = crypt_size; 
  memcpy(this->data + len,crypt,offset * sizeof(byte));
  len    = len + offset;
  
  offset = 1; 
  memcpy(this->data + len,this->end,offset * sizeof(byte));
  
  pnt_byte(this->data,size);
*/
}
