#ifndef CRYPTER_H
#define CRYPTER_H

#include <cstring>
#include "util.h"

#define TEA_ROUND	0x10		//默认情况下使用16轮TEA加密。
#define KEY_LENGTH	0x10		//KEY的长度为16位。

class CRYPTER
{
public:
	CRYPTER(void);
	~CRYPTER(void);

	CRYPTER(byte *key);

	/*
	 * prePlain表示前一个明文块，plain表示当前明文块，crypt表示当前明文块加密得到的密文块，preCrypt表示前一个密文块
	 * f表示加密算法，d表示解密算法 那么从plain得到crypt的过程是: crypt = f(plain ^ preCrypt) ^ prePlain
	 *
	 */
	int encrypt(byte *in,int len,byte *&out);
	/*
	 * prePlain表示前一个明文块，plain表示当前明文块，crypt表示当前明文块加密得到的密文块，preCrypt表示前一个密文块
	 * f表示加密算法，d表示解密算法 那从crypt得到plain的过程自然是 plain = d(crypt ^ prePlain) ^ preCrypt
	 *
	 */
	int decrypt(byte *in,int len,byte *&out);

private:
	/**
	 *      ------- 消息填充算法 ----------- 
	 *      a = (明文长度 + 10) mod 8;				这个10，我的理解是，1位存填充的个数，2位填充随机，7位是明文尾部填充0。
	 *      if(a 不等于 0) a = 8 - a;				消息的总长度为8的整数倍，不足八位则填充。这里计算需要填充的个数
	 *      b = 随机数 & 0xF8 | a;                  把a的值保存了下来，0xF8：11111000。a（0-7）之间，所以3位二进制可以保存。
	 *      plain[0] = b;         					然后把b做为明文的第0个字节，这样第0个字节就保存了a的信息，这个信息在解密时就要用来找到真正明文的起始位置
	 *      plain[1 至 a+2] = 随机数 &amp; 0xFF;    这里用随机数填充明文的第1到第a+2个字节
	 *      plain[a+3 至 a+3+明文长度-1] = 明文;		从a+3字节开始才是真正的明文
	 *      plain[a+3+明文长度, 最后] = 0;			在最后，填充0，填充到总长度为8的整数为止。到此为止，结束了，这就是最后得到的要加密的明文内容
	 *      ------- 消息填充算法 ------------
	 */
	int filling_algorithm(byte *in,int len,byte *&out);
	void encipher(unsigned long *v, unsigned long *k);	//TEA算法加密
	void decipher(unsigned long *v, unsigned long *k);	//TEA算法解密

private:
	byte _key[KEY_LENGTH];		//密钥
};
#endif/*UTIL_H*/

