#include "touch_packet_out.h"

TouchPacketOut::TouchPacketOut(byte *s){
  
  byte c[] = {0x08,0x25};
  PacketOut::create_packet(c,s);
} 

TouchPacketOut::~TouchPacketOut(){
  delete[] this->data;
}

void TouchPacketOut::gen_packet(){
  //unsigned long id = 365063521;
  //byte *tm_id = new byte[4];
  //ulong2byte(id,tm_id);
  //extern byte *tm_id;
  //byte *g_key = rand_nbyte(16);
  //byte tea_key[] = {0xf5,0x9a,0x7f,0xc1,0xda,0xe4,0xf4,0xaa,0x86,0xeb,0xfe,0x6d,0xda,0x5c,0xa7,0xbc};
  pnt_byte(g_key,16);

  byte token1[] = {0x00,0x18,0x00,0x16,0x00,0x01};
  byte token2[] = {0x00,0x00,0x04,0x11,0x00,0x00,0x00,0x01,0x00,0x00,0x12,0xD8};
  byte data1[]  = {0x00,0x00,0x00,0x00,0x01,0x14,0x00,0x19,0x01,0x01};
  byte data2_size[] = {0x00,0x15};
  byte *data2  = rand_nbyte(0x15);

  
  //byte data2[] = {0x02,0xEE,0x33,0x84,0xE6,0xB7,0x9C,0x6B,0x85,0x05,0xA1,0x5C,0xB8,0x6A,0x23,0x5A,0x7F,0xEC,0x54,0x02,0x5A}; 
  //pnt_byte(data2,21);

  byte *plain = new byte[55];
  memcpy(plain     ,token1,6  * sizeof(byte));
  memcpy(plain + 6 ,token2,12 * sizeof(byte));
  memcpy(plain + 18,g_id,4 * sizeof(byte));
  memcpy(plain + 22,data1 ,10 * sizeof(byte));
  memcpy(plain + 32,data2_size, 2 * sizeof(byte));
  memcpy(plain + 34,data2,21 * sizeof(byte));

  memcpy(g_0825_data       ,data1 + 4 , 6 * sizeof(byte));
  memcpy(g_0825_data +  6  ,data2_size, 2 * sizeof(byte));
  memcpy(g_0825_data +  8  ,data2     ,21 * sizeof(byte));


  int crypt_size = 0;
  byte *crypt = NULL;
  CRYPTER *crpyter = new CRYPTER(g_key);	
  crypt_size = crpyter->encrypt(plain,55,crypt);
  //std::cout << crypt_size;//72
 
  //pnt_byte(plain,55);
  //pnt_byte(crypt,crypt_size);
  //byte *result = NULL;
  //int alen = crpyter->decrypt(crypt,crypt_size,result);
  //pnt_byte(result,alen);
 
  /*
   byte crypt[] = {0x4f,0x49,0x90,0xec,0x3c,0x3b,
   0xa7,0xe0,0xfb,0x22,0x40,0x97,0xfd,0xa9,0xd6,0x38,0x60,0x06,0xa3,0xc6,0x4a,0x0a,
   0x98,0x4b,0x34,0x56,0xb1,0x15,0x83,0x4f,0x6b,0x48,0x6f,0x6a,0x96,0x6f,0xfc,0xdd,
   0xd5,0x0e,0xce,0xff,0x64,0x03,0x91,0x48,0x43,0x69,0x00,0xc5,0xa8,0x7c,0xf2,0x37,
   0x02,0xca,0x4a,0x37,0x27,0xf5,0x18,0xb5,0x75,0x4b,0x3e,0x15,0xbf,0xc4,0x48,0xde,
   0x71,0x75};  
   crypt_size = 72;
   byte *result = NULL;
   int alen = crpyter->decrypt(crypt,crypt_size,result);
   pnt_byte(result,alen);
  */
  
  int offset = 0,size = 115,len = 0;
  data = new byte[size];

  byte rand15byte[] = {0x03,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x66,0x07,0x00,0x00,0x00,0x00}; 
  
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
  memcpy(this->data + len,g_key,offset * sizeof(byte));
  len    = len + offset; 

  offset = crypt_size; 
  memcpy(this->data + len,crypt,offset * sizeof(byte));
  len    = len + offset; 
  
  offset = 1; 
  memcpy(this->data + len,this->end,offset * sizeof(byte));
  
pnt_byte(this->data,size);

  
/*
  byte d[] = {
   0x02,0x30,0x18,0x08,0x25,0x01,0x4c,0x05,0x21,0x78,0xed,0x03,0x00,0x00,0x00,0x01,
   0x01,0x01,0x00,0x00,0x66,0x07,0x00,0x00,0x00,0x00,0xf5,0x9a,0x7f,0xc1,0xda,0xe4,
   0xf4,0xaa,0x86,0xeb,0xfe,0x6d,0xda,0x5c,0xa7,0xbc,0x4f,0x49,0x90,0xec,0x3c,0x3b,
   0xa7,0xe0,0xfb,0x22,0x40,0x97,0xfd,0xa9,0xd6,0x38,0x60,0x06,0xa3,0xc6,0x4a,0x0a,
   0x98,0x4b,0x34,0x56,0xb1,0x15,0x83,0x4f,0x6b,0x48,0x6f,0x6a,0x96,0x6f,0xfc,0xdd,
   0xd5,0x0e,0xce,0xff,0x64,0x03,0x91,0x48,0x43,0x69,0x00,0xc5,0xa8,0x7c,0xf2,0x37,
   0x02,0xca,0x4a,0x37,0x27,0xf5,0x18,0xb5,0x75,0x4b,0x3e,0x15,0xbf,0xc4,0x48,0xde,
   0x71,0x75,0x03
   };

  memcpy(this->data,d,115);
*/
}
