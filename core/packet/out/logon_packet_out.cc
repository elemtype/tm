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
  byte *tea_key     = rand_nbyte(16); //0826 随机生成的tea key

  byte data1[]      = {0x01,0x12};
  byte g_0825_token_size[] = {0x00,0x38};
  byte data2[]      = {0x00,0x05,0x00,0x06,0x00,0x02}; //00 05 00 06 00 02
  byte data3[]      = {0x00,0x06};  
  byte crpyt_120_size[] = {0x00,0x78};
 
  byte *plain_120_data1  = rand_nbyte(4);//刚刚开始时4的长度，，随机的
  byte plain_120_data2[] = {0x00,0x01};  //00 01 固定的 
  byte plain_120_data3[] = {0x00};
  byte plain_120_data4[] = {0x00,0x04,0x11,0x00,0x00,0x00,0x01,0x00,0x00,0x12,0xD8};
  byte plain_120_data5[] = {0x00,0x00,0x00};
  byte *plain_120_data6  = new byte[4];//{0x50,0xF2,0xC9,0x3F};
  time_byte(plain_120_data6);  
  byte plain_120_data7[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  byte plain_120_data8[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  byte plain_120_data9[] = {0x00};
  byte plain_120_data10[] = {0x00,0x10};
  byte plain_120_data11[] = {0x31,0x12,0xA2,0xDE,0x42,0x8E,0x22,0x45,0x8D,0x2C,0xB7,0x9D,0xD4,0xFA,0xA5,0x41};
  byte *plain_120_data12 = rand_nbyte(16);

  memcpy(g_0826_key,plain_120_data12,16 * sizeof(byte));
  std::cout << "g_0826_key_start" << std::endl;
  pnt_byte(g_0826_key,16);
  std::cout << "g_0826_key_end" << std::endl;

  string pswd = "elemtype";
  //unsigned char* d = (unsigned char*)(pswd.c_str());
  unsigned char md5[16];
  MD5((unsigned char*)(pswd.c_str()),strlen(pswd.c_str()),md5);

  //以下104个字节，使用MD5(MD5(密码) + 00000000 + ID)加密
  byte plain_120[104];
  memcpy(plain_120     ,plain_120_data1 , 4 * sizeof(byte));
  memcpy(plain_120 +  4,plain_120_data2 , 2 * sizeof(byte));
  memcpy(plain_120 +  6,g_id            , 4 * sizeof(byte));
  memcpy(plain_120 + 10,plain_120_data3 , 1 * sizeof(byte));
  memcpy(plain_120 + 11,plain_120_data4 ,11 * sizeof(byte));
  memcpy(plain_120 + 22,plain_120_data5 , 3 * sizeof(byte));
  memcpy(plain_120 + 25,md5             ,16 * sizeof(byte));
  memcpy(plain_120 + 41,plain_120_data6 , 4 * sizeof(byte));
  memcpy(plain_120 + 45,plain_120_data7 ,13 * sizeof(byte));
  memcpy(plain_120 + 58,g_local_ip      , 4 * sizeof(byte));
  memcpy(plain_120 + 62,plain_120_data8 , 7 * sizeof(byte));
  memcpy(plain_120 + 69,plain_120_data9 , 1 * sizeof(byte));
  memcpy(plain_120 + 70,plain_120_data10, 2 * sizeof(byte));
  memcpy(plain_120 + 72,plain_120_data11,16 * sizeof(byte));
  memcpy(plain_120 + 88,plain_120_data12,16 * sizeof(byte));
  
  unsigned char fourZero[4] = {0x00,0x00,0x00,0x00};
  unsigned char md5_code[24];
  memcpy(md5_code     ,md5     ,16 * sizeof(unsigned char));
  memcpy(md5_code + 16,fourZero, 4 * sizeof(unsigned char));
  memcpy(md5_code + 20,g_id    , 4 * sizeof(unsigned char));
  unsigned char md5md5[16];
  MD5(md5_code,24,md5md5);
  //pnt_byte(md5md5,16);
  
  int crypt_120_size = 0;
  byte *crypt_120 = NULL;
  CRYPTER *crpyter = new CRYPTER(md5md5);	
  crypt_120_size = crpyter->encrypt(plain_120,104,crypt_120);
  //std::cout << std::endl;
  //pnt_byte(md5md5,16);
  delete crpyter;

  byte data4[] = {0x00,0x18,0x00,0x16,0x00,0x01,0x00};
  byte data5[] = {0x00,0x04,0x11,0x00,0x00,0x00,0x01,0x00,0x00,0x12,0xD8};
  byte data6[] = {0x00,0x00,0x00,0x00,0x01,0x03,0x00,0x14,0x00,0x01};
  byte data7[] = {0x00,0x10};
  byte data8[] = {0xCD,0xC8,0xCB,0x6F,0xE1,0xDA,0x3B,0xED,0x9E,0xFE,0xEB,0x85,0xAC,0x9F,0x58,0xD7};
  byte data9[] = {0x01,0x02,0x00,0x62,0x00,0x01};
  byte *data10 = rand_nbyte(16);
  byte data11[]={0x00,0x38};  
  byte *rand56byte  = rand_nbyte(0x38);
  std::cout << "g_0826_token_start" << std::endl;
  memcpy(g_0826_token,rand56byte,0x38 * sizeof(byte));
  pnt_byte(g_0826_token,0x38);
  std::cout << "g_0826_token_end" << std::endl;
  byte data12[]={0x00,0x14};
  byte data13[] = {0x60,0x4D,0x48,0xAD,0x1A,0x65,0x16,0x6C,0xA6,0x0F,0x86,0x48,0x97,0x7B,0xD2,0x85,0x31,0x60,0x73,0xFE};//rand_nbyte(20);
  byte data14[]={0x00,0x1A};
  byte data15[]={0x00,0x40};

  byte data16[]={0x00,0x15,0x00,0x30,0x00,0x00,0x01,0x8C,0x1B,0xA5,0x4D,0x00,0x10,0xD7,0x55,0x9B,0x0A,0x0B,0xBA,0x2A,0xF9,0x5C,0xD9,0xDB,0x4E,0x3C,0xBA,0x2A,0x69,0x02,0x83,0xC9,0xE0,0x6D,0x00,0x10,0x35,0xD7,0xE2,0x40,0x45,0xD3,0xCB,0x2E,0x09,0xEF,0xA4,0x0F,0x55,0xC1,0xE5,0xF0};  

  int crypt_64_size = 0;
  byte *crypt_64 = NULL;
  crpyter = new CRYPTER(plain_120_data12);	
  crypt_64_size = crpyter->encrypt(data16,52,crypt_64);
  //std::cout << crypt_size << std::endl;
  //// // pnt_byte(crypt_120,crypt_size);
  delete crpyter;


  byte *plain = new byte[443];
  memcpy(plain      ,data1       ,  2 * sizeof(byte));
  memcpy(plain +   2,g_0825_token_size,  2 * sizeof(byte));
  memcpy(plain +   4,g_0825_token, 56 * sizeof(byte)); 
  memcpy(plain +  60,data2       ,  6 * sizeof(byte)); 
  memcpy(plain +  66,g_id        ,  4 * sizeof(byte)); 
  memcpy(plain +  70,data3       ,  2 * sizeof(byte));
  memcpy(plain +  72,crpyt_120_size   ,  2 * sizeof(byte)); 
  memcpy(plain +  74,crypt_120   ,120 * sizeof(byte));
  memcpy(plain + 194,data4       ,  7 * sizeof(byte)); 
  memcpy(plain + 201,data5       , 11 * sizeof(byte)); 
  memcpy(plain + 212,g_id        ,  4 * sizeof(byte)); 
  memcpy(plain + 216,data6       , 10 * sizeof(byte)); 
  memcpy(plain + 226,data7       ,  2 * sizeof(byte)); 
  memcpy(plain + 228,data8       , 16 * sizeof(byte));
  memcpy(plain + 244,g_0825_data , 29 * sizeof(byte));  
  memcpy(plain + 273,data9       ,  6 * sizeof(byte));
  memcpy(plain + 279,data10      , 16 * sizeof(byte));
  memcpy(plain + 295,data11      ,  2 * sizeof(byte));
  memcpy(plain + 297,rand56byte  , 56 * sizeof(byte));
  memcpy(plain + 353,data12      ,  2 * sizeof(byte));
  memcpy(plain + 355,data13      , 20 * sizeof(byte));
  memcpy(plain + 375,data14      ,  2 * sizeof(byte));
  memcpy(plain + 377,data15      ,  2 * sizeof(byte));
  memcpy(plain + 379,crypt_64    , 64 * sizeof(byte));


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
}
