#ifndef CRYPTER_H
#define CRYPTER_H

#include <cstring>
#include "util.h"

#define TEA_ROUND	0x10		//Ĭ�������ʹ��16��TEA���ܡ�
#define KEY_LENGTH	0x10		//KEY�ĳ���Ϊ16λ��

class CRYPTER
{
public:
	CRYPTER(void);
	~CRYPTER(void);

	CRYPTER(byte *key);

	/*
	 * prePlain��ʾǰһ�����Ŀ飬plain��ʾ��ǰ���Ŀ飬crypt��ʾ��ǰ���Ŀ���ܵõ������Ŀ飬preCrypt��ʾǰһ�����Ŀ�
	 * f��ʾ�����㷨��d��ʾ�����㷨 ��ô��plain�õ�crypt�Ĺ�����: crypt = f(plain ^ preCrypt) ^ prePlain
	 *
	 */
	int encrypt(byte *in,int len,byte *&out);
	/*
	 * prePlain��ʾǰһ�����Ŀ飬plain��ʾ��ǰ���Ŀ飬crypt��ʾ��ǰ���Ŀ���ܵõ������Ŀ飬preCrypt��ʾǰһ�����Ŀ�
	 * f��ʾ�����㷨��d��ʾ�����㷨 �Ǵ�crypt�õ�plain�Ĺ�����Ȼ�� plain = d(crypt ^ prePlain) ^ preCrypt
	 *
	 */
	int decrypt(byte *in,int len,byte *&out);

private:
	/**
	 *      ------- ��Ϣ����㷨 ----------- 
	 *      a = (���ĳ��� + 10) mod 8;				���10���ҵ�����ǣ�1λ�����ĸ�����2λ��������7λ������β�����0��
	 *      if(a ������ 0) a = 8 - a;				��Ϣ���ܳ���Ϊ8���������������λ����䡣���������Ҫ���ĸ���
	 *      b = ����� & 0xF8 | a;                  ��a��ֵ������������0xF8��11111000��a��0-7��֮�䣬����3λ�����ƿ��Ա��档
	 *      plain[0] = b;         					Ȼ���b��Ϊ���ĵĵ�0���ֽڣ�������0���ֽھͱ�����a����Ϣ�������Ϣ�ڽ���ʱ��Ҫ�����ҵ��������ĵ���ʼλ��
	 *      plain[1 �� a+2] = ����� &amp; 0xFF;    �����������������ĵĵ�1����a+2���ֽ�
	 *      plain[a+3 �� a+3+���ĳ���-1] = ����;		��a+3�ֽڿ�ʼ��������������
	 *      plain[a+3+���ĳ���, ���] = 0;			��������0����䵽�ܳ���Ϊ8������Ϊֹ������Ϊֹ�������ˣ���������õ���Ҫ���ܵ���������
	 *      ------- ��Ϣ����㷨 ------------
	 */
	int filling_algorithm(byte *in,int len,byte *&out);
	void encipher(unsigned long *v, unsigned long *k);	//TEA�㷨����
	void decipher(unsigned long *v, unsigned long *k);	//TEA�㷨����

private:
	byte _key[KEY_LENGTH];		//��Կ
};
#endif/*UTIL_H*/

