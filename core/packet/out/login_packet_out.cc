#include "login_packet_out.h"

LoginPacketOut::LoginPacketOut(byte *s){
  
  byte c[] = {0x08,0x28};
  PacketOut::create_packet(c,s);
} 

LoginPacketOut::~LoginPacketOut(){
  delete[] this->data;
}


void LoginPacketOut::gen_packet(){
  byte data1[]     = {0x00,0x07,0x00,0x88,0x00,0x04};
  byte data4Zero[] = {0x00,0x00,0x00,0x00};
  byte data2[]     = {0x00,0x0C,0x00,0x16,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  byte data3[]     = {0x00,0x18,0x00,0x16,0x00,0x01,0x00,0x00,0x04,0x11,0x00,0x00,0x00,0x01,0x00,0x00,0x12,0xD8};
  byte data4[]     = {0x00,0x00,0x00,0x00,0x00,0x1F,0x00,0x22,0x00,0x01};
  byte *data5      = rand_nbyte(32);
  byte data6[]     = {0x01,0x05};
  byte data7[]     = {0x00,0x88};
  byte data8[]     = {0x00,0x01,0x01};
  byte data9[]     = {0x02};
  byte data10[]    = {0x00,0x40,0x02,0x01,0x03,0x3C,0x01,0x03,0x00,0x00,0x7E,0xEB,0x3C,0x82,0xBB,0x29,0xA9,0x47,0x46,0xBC,0xD5,0xDB,0x5D,0x38,0x84,0xA4,0xD6,0xAF,0xEF,0x2F,0xB3,0xBA,0x71,0x78,0xF4,0xA0,0x9F,0x39,0x5B,0xF8,0x6F,0xA8,0x91,0xC2,0xD6,0x43,0x59,0x85,0x86,0xA5,0xAC,0x7B,0x70,0xB4,0x27,0x60,0x9E,0x06,0x23,0x10,0xD2,0xF7,0x3F,0x1F,0x4B,0xE1};

  byte data11[]   = {0x00,0x40,0x02,0x02,0x03,0x3C,0x01,0x03,0x00,0x00,0x15,0xD4,0xE4,0xDD,0x02,0x76,0xEE,0x20,0x09,0xB2,0xF0,0xA8,0xCD,0xB7,0x24,0xC1,0x55,0x4F,0xAB,0x19,0x04,0x95,0x7F,0xD1,0x27,0xA2,0x9C,0x2B,0xB2,0x66,0xA4,0x36,0x1D,0xCF,0x6E,0xE2,0x5C,0x40,0x27,0xE4,0x42,0x6D,0xA5,0xB0,0xE0,0x90,0x92,0x87,0x8D,0xE9,0xC4,0x8A,0x8F,0x9F,0x8E,0xC4};
  byte data12[]   = {0x01,0x0B,0x00,0x20,0x00,0x01};
  byte *data13      = rand_nbyte(16);
  byte data14[]   = {0x07};
  byte data15[]   = {0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  byte data16[]   = {0x00,0x00};
  byte data17[]   = {0x00,0x00,0x00,0x2D,0x00,0x06,0x00,0x01};
  byte size78[]   = {0x00,0x78};
  byte s_port[]   = {0x1F,0x40};
  
  byte i[] = {0xAC,0x13,0x69,0x02};

  byte *t = new byte[4];
  time_byte(t);

  byte plain[468];
  memcpy(plain      ,data1       ,  6 * sizeof(byte));
  memcpy(plain +   6,t           ,  4 * sizeof(byte));
  memcpy(plain +  10,g_local_ip  ,  4 * sizeof(byte));
  memcpy(plain +  14,data4Zero   ,  4 * sizeof(byte));
  memcpy(plain +  18,size78      ,  2 * sizeof(byte));
  memcpy(plain +  20,g_0826_token_1,120 * sizeof(byte));
  memcpy(plain + 140,data2       , 16 * sizeof(byte));
  memcpy(plain + 156,g_server_ip ,  4 * sizeof(byte));
  memcpy(plain + 160,s_port      ,  2 * sizeof(byte));
  memcpy(plain + 162,data4Zero   ,  4 * sizeof(byte));
  memcpy(plain + 166,g_crc32     , 52 * sizeof(byte));
  memcpy(plain + 218,data3       , 18 * sizeof(byte));
  memcpy(plain + 236,g_id        ,  4 * sizeof(byte));
  memcpy(plain + 240,data4       , 10 * sizeof(byte));
  memcpy(plain + 250,data5       , 32 * sizeof(byte));
  memcpy(plain + 282,data6       ,  2 * sizeof(byte));
  memcpy(plain + 284,data7       ,  2 * sizeof(byte));
  memcpy(plain + 286,data8       ,  3 * sizeof(byte));
  memcpy(plain + 289,data9       ,  1 * sizeof(byte));
  memcpy(plain + 290,data10      , 66 * sizeof(byte));
  memcpy(plain + 356,data11      , 66 * sizeof(byte));
  memcpy(plain + 422,data12      ,  6 * sizeof(byte));
  memcpy(plain + 428,data13      , 16 * sizeof(byte));
  memcpy(plain + 444,data14      ,  1 * sizeof(byte));
  memcpy(plain + 445,data15      ,  9 * sizeof(byte));
  memcpy(plain + 454,data16      ,  2 * sizeof(byte));
  memcpy(plain + 456,data17      ,  8 * sizeof(byte));
  memcpy(plain + 464,i  ,  4 * sizeof(byte));

  int crypt_size = 0;
  byte *crypt = NULL;
  CRYPTER *crpyter = new CRYPTER(g_0828_key_0);	
  crypt_size = crpyter->encrypt(plain,468,crypt);
  //std::cout << crypt_size << std::endl;
  //pnt_byte(plain,443);
  //pnt_byte(crypt,crypt_size);
  delete crpyter;

  byte size38[]   = {0x00,0x38};
  byte d[58 + crypt_size];
  memcpy(d    ,size38      ,  2 * sizeof(byte));
  memcpy(d + 2,g_0826_token, 56 * sizeof(byte));
  memcpy(d +58,crypt       ,crypt_size * sizeof(byte));


  byte special_data[] = {0x02,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x66,0x07,0x00,0x30,0x00,0x3a};

  int offset = 0,size = 58 + crypt_size + 27,len = 0;
  data = new byte[size];
  data_size = size;

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
  memcpy(this->data + len,special_data,offset * sizeof(byte));
  len    = len + offset; 

  offset = 58 + crypt_size; 
  memcpy(this->data + len,d,offset * sizeof(byte));
  len    = len + offset;
  
  offset = 1; 
  memcpy(this->data + len,this->end,offset * sizeof(byte));
  
  pnt_byte(this->data,size);

}
