#ifndef COMMON_UTIL_H
#define COMMON_UTIL_H

#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <sstream>
#include <time.h>

typedef unsigned char byte;			//与网络字节流对应，一个byte占8位，用一个unsigned char表示。
typedef unsigned long ulong;		//一个ulong占32位，相当于四个byte，用一个unsigned long表示。

inline double logbase(double base, double x) {
    return log(x)/log(base);
}

/*
*convert int to hex char.
*example:10 -> 'A',15 -> 'F'
*/
char intToHexChar(int x);

/*
*convert hex char to int.
*example:'A' -> 10,'F' -> 15
*/
int hexCharToInt(char hex);

using std::string;
/*
*convert a byte array to hex string.
*hex string format example:"AF B0 80 7D"
*/
string bytesToHexString(const byte *in, size_t size);

/*
*convert a hex string to a byte array.
*hex string format example:"AF B0 80 7D"
*/
size_t hexStringToBytes(const string &str, byte *out);

void byte2ulong(byte *b,int offset,unsigned long *l);
void byte2ulong2b(byte *b,int offset,unsigned long *l);

void ulong2byte(unsigned long l,byte *b);

void pnt_byte(byte *b,int len);

void copybyte(byte *dest,byte *src,byte size);

byte rand_byte();

byte* rand_nbyte(int n);

string byte2ipaddr(byte *b);

void ipaddr2byte(string s,byte *b);

void time_byte(byte *t);

size_t formatString(const string &str);

#endif/*UTIL_H*/
