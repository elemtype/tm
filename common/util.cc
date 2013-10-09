#include "util.h"

using namespace std;

char intToHexChar(int x) {
    static const char HEX[16] = {
        '0', '1', '2', '3',
        '4', '5', '6', '7',
        '8', '9', 'A', 'B',
        'C', 'D', 'E', 'F'
    };
    return HEX[x];
}

int hexCharToInt(char hex) {
    hex = toupper(hex);
    if (isdigit(hex))
        return (hex - '0');
    if (isalpha(hex))
        return (hex - 'A' + 10);
    return 0;
}

string bytesToHexString(const byte *in, size_t size) {
    string str;
    for (size_t i = 0; i < size; ++i) {
        int t = in[i];
        int a = t / 16;
        int b = t % 16;
        str.append(1, intToHexChar(a));
        str.append(1, intToHexChar(b));
        if (i != size - 1)
            str.append(1, ' ');
    }
    return str;
}

size_t hexStringToBytes(const string &str, byte *out) {

    vector<string> vec;
    string::size_type currPos = 0, prevPos = 0;
    while ((currPos = str.find(' ', prevPos)) != string::npos) {
        string b(str.substr(prevPos, currPos - prevPos));
        vec.push_back(b);
        prevPos = currPos + 1;
    }
    if (prevPos < str.size()) {
        string b(str.substr(prevPos));
        vec.push_back(b);
    }
    typedef vector<string>::size_type sz_type;
    sz_type size = vec.size();
    for (sz_type i = 0; i < size; ++i) {
        int a = hexCharToInt(vec[i][0]);
        int b = hexCharToInt(vec[i][1]);
        out[i] = a * 16 + b;
    }
    return size;
}

void byte2ulong(byte *b,int offset,unsigned long *l)
{
	 
	/*
	  һ��unsigned longռ32λ��һ��byteռ8λ��������Ҫ4��byte����䡣
	  һ��byteռ8λ�������ƿ��Ա�ʾ2��8�η���һ��ʮ��������ֻ�ܱ�ʾ2��4�η�������һ��byte��Ҫ������ʮ������������ʾ��
	  һ��byte�������Ϊһ��unsigned char�����Ա�ʾһ��ascii�ַ���������һ��ʹ�ô˷����������ݡ�
	*/

        *l =	    (unsigned long)(b[offset + 3])      & 0x000000FF ;
        *l = *l |  ((unsigned long)(b[offset + 2])<<8   & 0x0000FF00) ;
        *l = *l |  ((unsigned long)(b[offset + 1])<<16  & 0x00FF0000) ;
	*l = *l |  ((unsigned long)(b[offset    ])<<24  & 0xFF000000) ;

        *l = *l & 0xFFFFFFFF;
	
	/*
	int index = offset / len;
	memcpy(l + index, b + offset, sizeof(unsigned long));
	*/
	//cout << l << endl;
}

void ulong2byte(unsigned long l,byte *b)
{
	b[0] = (l >> 24) & 0xFF;
    b[1] = (l >> 16) & 0xFF;
    b[2] = (l >> 8)  & 0xFF;
    b[3] = l         & 0xFF;
}

void pnt_byte(byte *b,int len)
{   
    string str;
    for (int i = 0; i < len; ++i) {
        int t = b[i];
        int m = t / 16;
        int n = t % 16;
		str.append("0x");
        str.append(1, intToHexChar(m));
        str.append(1, intToHexChar(n));
        if (i != len - 1)
            str.append(1, ' ');
    }
	cout << str << endl;
}

void copybyte(byte *dest,byte *src,byte size)
{
	for(int j = 0;j < size;j++)
	{
		*dest++ = *src++;
	}
}

byte rand_byte()
{
  return (byte)(rand() & 0xFF);
}

byte* rand_nbyte(int n)
{
  byte *b = new byte[n];
  for(int i = 0;i < n;i++){
    b[i] = (byte)(rand() & 0xFF);
  }

  return b;
}
