#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>

typedef unsigned char byte;			//�������ֽ�����Ӧ��һ��byteռ8λ����һ��unsigned char��ʾ��
typedef unsigned long ulong;		//һ��ulongռ32λ���൱���ĸ�byte����һ��unsigned long��ʾ��

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

void ulong2byte(unsigned long l,byte *b);

void pnt_byte(byte *b,int len);

void copybyte(byte *dest,byte *src,byte size);

#endif/*UTIL_H*/