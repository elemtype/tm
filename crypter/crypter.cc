#include "crypter.h"


CRYPTER::CRYPTER(void)
{
}


CRYPTER::~CRYPTER(void)
{

}

CRYPTER::CRYPTER(byte *key)
{
	memset(_key,    0, KEY_LENGTH * sizeof(byte));
	memcpy(_key,  key, KEY_LENGTH * sizeof(byte));
}


void CRYPTER::encipher(unsigned long *v, unsigned long *k) {
    unsigned long y=v[0], z=v[1], sum=0, i;         /* set up */
    unsigned long delta=0x9e3779b9;                 /* a key schedule constant */
    unsigned long a=k[0], b=k[1], c=k[2], d=k[3];   /* cache key */
    for (i=0; i < 16; i++) {                        /* basic cycle start */
        sum += delta;
        y += ((z<<4) + a) ^ (z + sum) ^ ((z>>5) + b);
        z += ((y<<4) + c) ^ (y + sum) ^ ((y>>5) + d);/* end cycle */
    }
    v[0]=y;
    v[1]=z;
}

void CRYPTER::decipher(unsigned long *v, unsigned long *k) {
    unsigned long y=v[0], z=v[1], sum=0xC6EF3720, i; /* set up */

	sum = 0xE3779B90; /* 由于进行16轮运算，所以将delta左移4位，减16次后刚好为0.sum = delta << 4;*/
            
    unsigned long delta=0x9e3779b9;                  /* a key schedule constant */
    unsigned long a=k[0], b=k[1], c=k[2], d=k[3];    /* cache key */
    for(i=0; i<16; i++) {                            /* basic cycle start */
        z -= ((y<<4) + c) ^ (y + sum) ^ ((y>>5) + d);
        y -= ((z<<4) + a) ^ (z + sum) ^ ((z>>5) + b);
        sum -= delta;                                /* end cycle */
    }
    v[0]=y;
    v[1]=z;
}

int CRYPTER::filling_algorithm(byte *in,int in_len,byte *&out){
	
	// 计算头部填充字节数
    int pos = (in_len + 0x0A) % 8;
	//这个0x0A个字节中，一个用来记录需要填充的字节数；两个为头部随机数；七个为尾部填充的0x00。
    if(pos != 0)
	{
		pos = 8 - pos;
	}
    // 计算输出的密文长度
    int len = in_len + pos + 10;	
	int index = 0;
	
	out = new byte[len];

	// 这里的操作把pos存到了plain的第一个字节里面
    // 0xF8后面三位是空的，正好留给pos，因为pos是0到7的值，表示文本开始的字节位置
    out[index++] = (byte)((rand() & 0xF8) | pos);

	// 这里用随机产生的数填充plain[1]到plain[pos]之间的内容
    for(int i = 1; i <= pos; i++)
	{
        out[index++] = (byte)(rand() & 0xFF);
	}

    // 继续填充2个字节的随机数，这个过程中如果满了8字节就加密之
    int padding = 1;
    while(padding <= 2) 
	{
       out[index++] = (byte)(rand() & 0xFF);
       padding++;
    }
        
    // 头部填充完了，这里开始填真正的明文了，也是满了8字节就加密，一直到明文读完
    int i = 0;
    while(in_len > 0) 
	{

        out[index++] = in[i++];
        in_len--;

    }
        
    // 最后填上0，以保证是8字节的倍数
    padding = 1;
    while(padding <= 7) 
	{
        out[index++] = 0x0;
        padding++;
    }

	return len;
}

int CRYPTER::encrypt(byte *in,int in_len,byte *&out) {
	//临时存放填充后的明文
	byte *p = NULL;
	//得到填充后的明文和明文长度
	int len = filling_algorithm(in,in_len,p);
	out = new byte[len];

	//pnt_byte(p,len);

	//header用来标识是否是第一个明文块
	bool header = true;
	byte *plain		= new byte[8];			//当前明文块
	byte *preplain  = new byte[8];			//上一个明文块
	byte *crypt		= new byte[8];			//当前TEA加密所得密文块
	byte *precrypt  = new byte[8];			//上一个TEA加密所得密文块
	byte *b			= new byte[4];			//临时存放加密、解密内容

	unsigned long *k = new unsigned long[4];
	byte2ulong(this->_key,	0,	k	 );
	byte2ulong(this->_key,	4,	k + 1);
	byte2ulong(this->_key,	8,	k + 2);
	byte2ulong(this->_key, 12,	k + 3);

	// 这个就是prePlain，第一个8字节块当然没有prePlain，所以我们做一个全0的给第一个8字节块
    for(int i = 0; i < 8; i++)
	{
        preplain[i] = 0x00;
	}

	//开始加密
    for(int i = 0; i < len; i = i + 8) 
	{
		memcpy(plain,p + i,8 * sizeof(byte));
		//pnt_byte(currplain,8);
		
		// 这部分完成我上面所说的 plain ^ preCrypt，注意这里判断了是不是第一个8字节块，如果是的话，那个prePlain就当作preCrypt用
		for(int j = 0;j < 8;j++)
		{
			if(header) 
			{
				plain[j] ^= preplain[j];
			}
			else
			{
				plain[j] ^= precrypt[j];
			}
		}

		unsigned long *v = new unsigned long[2];

		byte2ulong(plain,0,v);
		byte2ulong(plain,4,v + 1);
		
		encipher(v,k);
		
		ulong2byte(v[0],b);
		memcpy(crypt	,b,8 * sizeof(byte));
		ulong2byte(v[1],b);
		memcpy(crypt + 4,b,8 * sizeof(byte));
		
		for(int j = 0;j < 8;j++)
		{
			crypt[j] ^= preplain[j];
		}
		memcpy(precrypt	,crypt,8 * sizeof(byte));
		memcpy(out + i	,crypt,8 * sizeof(byte));
		memcpy(preplain	,plain,8 * sizeof(byte));
		
		header = false;	
		//pnt_byte(precrypt,8);
    }
	
	delete p;
	p			= NULL;
	delete plain;
	plain		= NULL;
	delete preplain;
	preplain	= NULL;
	delete crypt;
	crypt		= NULL;
	delete precrypt;	
	precrypt	= NULL;
	delete b;
	b			= NULL;

	//pnt_byte(out,104);
	return len;
}

int CRYPTER::decrypt(byte *in,int in_len,byte *&out) {
	//临时存放解密后的明文
	byte *p = new byte[in_len];

	//header用来标识是否是第一个明文块
	bool header = true;
	byte *plain		= new byte[8];			//当前明文块
	byte *preplain  = new byte[8];			//上一个明文块
	byte *crypt		= new byte[8];			//当前TEA加密所得密文块
	byte *precrypt  = new byte[8];			//上一个TEA加密所得密文块
	byte *b			= new byte[4];			//临时存放加密、解密内容

	unsigned long *k = new unsigned long[4];
	byte2ulong(this->_key,	0,	k	 );
	byte2ulong(this->_key,	4,	k + 1);
	byte2ulong(this->_key,	8,	k + 2);
	byte2ulong(this->_key, 12,	k + 3);

	memcpy(crypt,in,8 * sizeof(byte));

	unsigned long *v = new unsigned long[2];
	byte2ulong(crypt,0,v);
	byte2ulong(crypt,4,v + 1);

	//解密第一个明文块，可以得到填充前实际数据的长度。
	decipher(v,k);

	ulong2byte(v[0],b);
	memcpy(plain	,b,4 * sizeof(byte));
	ulong2byte(v[1],b);
	memcpy(plain + 4,b,4 * sizeof(byte));

	// 得到填充值个数
	int pos = plain[0] & 0x7;
    // 得到真正明文的长度
    int len = in_len - pos - 10;
	out = new byte[len];

    // 这个是临时的preCrypt，和加密时第一个8字节块没有prePlain一样，解密时
    // 第一个8字节块也没有preCrypt，所有这里建一个全0的
	for(int i = 0; i < 8; i++)
	{
        precrypt[i] = 0x00;
	}


	// 加1，和加密算法是对应的，指用来记录填充字节长度的第一个字节
    pos++;
    
	//指填充的两个随机数
	pos++;
    pos++;

	//开始解密
	for(int i = 0;i < in_len; i = i + 8){
		memcpy(crypt,in + i,8 * sizeof(byte));
		for(int j = 0;j < 8;j++)
		{
			if(header) 
			{
				crypt[j] ^= precrypt[j];
			}
			else
			{
				crypt[j] ^= preplain[j];
			}
		}

		unsigned long *v = new unsigned long[2];
		byte2ulong(crypt,0,v);
		byte2ulong(crypt,4,v + 1);

		decipher(v,k);

		ulong2byte(v[0],b);
		memcpy(plain	,b,4 * sizeof(byte));
		ulong2byte(v[1],b);
		memcpy(plain + 4,b,4 * sizeof(byte));

		memcpy(preplain	,plain,8 * sizeof(byte));

		for(int j = 0;j < 8;j++)
		{
			plain[j] ^= precrypt[j];
		}

		memcpy(precrypt	,in + i	,8 * sizeof(byte));
		memcpy(p + i	,plain	,8 * sizeof(byte));
		header = false; 
	}
	//pnt_byte(p,in_len);
	memcpy(out,p + pos,len * sizeof(byte));

	delete p;
	p			= NULL;
	delete plain;
	plain		= NULL;
	delete preplain;
	preplain	= NULL;
	delete crypt;
	crypt		= NULL;
	delete precrypt;	
	precrypt	= NULL;
	delete b;
	b			= NULL;

	return len;
}
