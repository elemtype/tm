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

	sum = 0xE3779B90; /* ���ڽ���16�����㣬���Խ�delta����4λ����16�κ�պ�Ϊ0.sum = delta << 4;*/
            
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
	
	// ����ͷ������ֽ���
    int pos = (in_len + 0x0A) % 8;
	//���0x0A���ֽ��У�һ��������¼��Ҫ�����ֽ���������Ϊͷ����������߸�Ϊβ������0x00��
    if(pos != 0)
	{
		pos = 8 - pos;
	}
    // ������������ĳ���
    int len = in_len + pos + 10;	
	int index = 0;
	
	out = new byte[len];

	// ����Ĳ�����pos�浽��plain�ĵ�һ���ֽ�����
    // 0xF8������λ�ǿյģ���������pos����Ϊpos��0��7��ֵ����ʾ�ı���ʼ���ֽ�λ��
    out[index++] = (byte)((rand() & 0xF8) | pos);

	// ��������������������plain[1]��plain[pos]֮�������
    for(int i = 1; i <= pos; i++)
	{
        out[index++] = (byte)(rand() & 0xFF);
	}

    // �������2���ֽڵ������������������������8�ֽھͼ���֮
    int padding = 1;
    while(padding <= 2) 
	{
       out[index++] = (byte)(rand() & 0xFF);
       padding++;
    }
        
    // ͷ��������ˣ����￪ʼ�������������ˣ�Ҳ������8�ֽھͼ��ܣ�һֱ�����Ķ���
    int i = 0;
    while(in_len > 0) 
	{

        out[index++] = in[i++];
        in_len--;

    }
        
    // �������0���Ա�֤��8�ֽڵı���
    padding = 1;
    while(padding <= 7) 
	{
        out[index++] = 0x0;
        padding++;
    }

	return len;
}

int CRYPTER::encrypt(byte *in,int in_len,byte *&out) {
	//��ʱ������������
	byte *p = NULL;
	//�õ���������ĺ����ĳ���
	int len = filling_algorithm(in,in_len,p);
	out = new byte[len];

	//pnt_byte(p,len);

	//header������ʶ�Ƿ��ǵ�һ�����Ŀ�
	bool header = true;
	byte *plain		= new byte[8];			//��ǰ���Ŀ�
	byte *preplain  = new byte[8];			//��һ�����Ŀ�
	byte *crypt		= new byte[8];			//��ǰTEA�����������Ŀ�
	byte *precrypt  = new byte[8];			//��һ��TEA�����������Ŀ�
	byte *b			= new byte[4];			//��ʱ��ż��ܡ���������

	unsigned long *k = new unsigned long[4];
	byte2ulong(this->_key,	0,	k	 );
	byte2ulong(this->_key,	4,	k + 1);
	byte2ulong(this->_key,	8,	k + 2);
	byte2ulong(this->_key, 12,	k + 3);

	// �������prePlain����һ��8�ֽڿ鵱Ȼû��prePlain������������һ��ȫ0�ĸ���һ��8�ֽڿ�
    for(int i = 0; i < 8; i++)
	{
        preplain[i] = 0x00;
	}

	//��ʼ����
    for(int i = 0; i < len; i = i + 8) 
	{
		memcpy(plain,p + i,8 * sizeof(byte));
		//pnt_byte(currplain,8);
		
		// �ⲿ�������������˵�� plain ^ preCrypt��ע�������ж����ǲ��ǵ�һ��8�ֽڿ飬����ǵĻ����Ǹ�prePlain�͵���preCrypt��
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
	//��ʱ��Ž��ܺ������
	byte *p = new byte[in_len];

	//header������ʶ�Ƿ��ǵ�һ�����Ŀ�
	bool header = true;
	byte *plain		= new byte[8];			//��ǰ���Ŀ�
	byte *preplain  = new byte[8];			//��һ�����Ŀ�
	byte *crypt		= new byte[8];			//��ǰTEA�����������Ŀ�
	byte *precrypt  = new byte[8];			//��һ��TEA�����������Ŀ�
	byte *b			= new byte[4];			//��ʱ��ż��ܡ���������

	unsigned long *k = new unsigned long[4];
	byte2ulong(this->_key,	0,	k	 );
	byte2ulong(this->_key,	4,	k + 1);
	byte2ulong(this->_key,	8,	k + 2);
	byte2ulong(this->_key, 12,	k + 3);

	memcpy(crypt,in,8 * sizeof(byte));

	unsigned long *v = new unsigned long[2];
	byte2ulong(crypt,0,v);
	byte2ulong(crypt,4,v + 1);

	//���ܵ�һ�����Ŀ飬���Եõ����ǰʵ�����ݵĳ��ȡ�
	decipher(v,k);

	ulong2byte(v[0],b);
	memcpy(plain	,b,4 * sizeof(byte));
	ulong2byte(v[1],b);
	memcpy(plain + 4,b,4 * sizeof(byte));

	// �õ����ֵ����
	int pos = plain[0] & 0x7;
    // �õ��������ĵĳ���
    int len = in_len - pos - 10;
	out = new byte[len];

    // �������ʱ��preCrypt���ͼ���ʱ��һ��8�ֽڿ�û��prePlainһ��������ʱ
    // ��һ��8�ֽڿ�Ҳû��preCrypt���������ｨһ��ȫ0��
	for(int i = 0; i < 8; i++)
	{
        precrypt[i] = 0x00;
	}


	// ��1���ͼ����㷨�Ƕ�Ӧ�ģ�ָ������¼����ֽڳ��ȵĵ�һ���ֽ�
    pos++;
    
	//ָ�������������
	pos++;
    pos++;

	//��ʼ����
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
