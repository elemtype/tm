#include "logon_packet_out.h"

LogonPacketOut::LogonPacketOut(byte *s){
  
  byte c[] = {0x08,0x26};
  PacketOut::create_packet(c,s);
} 

LogonPacketOut::~LogonPacketOut(){
  delete[] this->data;
}


void LogonPacketOut::gen_packet(){
  byte rand15byte[] = {0x03,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x66,0x07,0x00,0x00,0x00,0x00}; //15个随机数
  byte *tea_key     = rand_nbyte(0x15); //0826 随机生成的tea key
  byte data1[]      = {0x01,0x12};
  byte g_0825_token_size[] = {0x00,0x38};
  byte data2[]      = {0x00,0x05,0x00,0x06,0x00,0x02}; //00 05 00 06 00 02
  byte data3[]      = {0x00,0x06};  
  byte crpyt_120_size[] = {0x00,0x78};

  byte *crypt_120 = new byte[0x78];
 
  byte *plain_120_data1  = rand_nbyte(4);//刚刚开始时4的长度，，随机的
  byte plain_120_data2[] = {0x00,0x01};  //00 01 固定的 
  //byte plain_120_data3[] = {0x00};
  byte plain_120_data4[] = {0x00,0x00,0x04,0x11,0x00,0x00,0x00,0x01,0x00,0x00,0x12,0xD8};
  byte plain_120_data5[] = {0x00,0x00,0x00};
  byte plain_120_data6[] = {0x00,0x00,0x00,0x00};  
  byte plain_120_data7[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  byte plain_120_data8[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  byte plain_120_data9[] = {0x0C};
  byte plain_120_data10[] = {0x00,0x10};
  byte plain_120_data11[] = {0x49,0x85,0xA1,0xB8,0x21,0x04,0xDA,0x46,0x9E,0x3F,0x17,0xC4,0x99,0x6E,0x4F,0xDB};
  byte *plain_120_data12 = rand_nbyte(0x16);

  string pswd = "elemtype";
  //unsigned char* d = (unsigned char*)(pswd.c_str());
  unsigned char md5[16];
  MD5((unsigned char*)(pswd.c_str()),strlen(pswd.c_str()),md5);

  memcpy(crypt_120     ,plain_120_data1 , 4 * sizeof(byte));
  memcpy(crypt_120 +  4,plain_120_data2 , 2 * sizeof(byte));
  memcpy(crypt_120 +  6,g_id            , 4 * sizeof(byte));
  //memcpy(crypt_120 + 10,plain_120_data3 , 1 * sizeof(byte));
  memcpy(crypt_120 + 12,plain_120_data4 ,12 * sizeof(byte));
  memcpy(crypt_120 + 24,plain_120_data5 , 3 * sizeof(byte));
  memcpy(crypt_120 + 27,md5             ,16 * sizeof(byte));
  memcpy(crypt_120 + 43,plain_120_data6 , 4 * sizeof(byte));
  memcpy(crypt_120 + 47,plain_120_data7 ,16 * sizeof(byte));
  memcpy(crypt_120 + 63,g_local_ip      , 4 * sizeof(byte));
  memcpy(crypt_120 + 67,plain_120_data8 , 7 * sizeof(byte));
  memcpy(crypt_120 + 74,plain_120_data9 , 1 * sizeof(byte));
  memcpy(crypt_120 + 75,plain_120_data10, 2 * sizeof(byte));
  memcpy(crypt_120 + 77,plain_120_data11, 16 * sizeof(byte));
  memcpy(crypt_120 + 93,plain_120_data12, 16 * sizeof(byte));
  
  unsigned char fourZero[4] = {0x00,0x00,0x00,0x00};
  unsigned char md5_code[24];
  memcpy(md5_code,md5,16 * sizeof(unsigned char));
  memcpy(md5_code + 16,fourZero,4 * sizeof(unsigned char));
  memcpy(md5_code + 20,g_id,4 * sizeof(unsigned char));
  unsigned char md5md5[16];
  MD5(md5_code,16,md5md5);
  pnt_byte(md5md5,16);
  

  int crypt_size = 0;
  byte *crypt = NULL;
  CRYPTER *crpyter = new CRYPTER(g_key);	
  crypt_size = crpyter->encrypt(crypt_120,100,crypt);
  
  //byte,0xtoken1[],0x=,0x{0x00,0x18,0x00,0x16,0x00,0x01}//
}
