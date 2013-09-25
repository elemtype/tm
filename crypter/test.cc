#include <iostream>
#include <string>

#include "util.h"
#include "crypter.h"

using namespace std;

int main() {
	
	byte key[] = {0x75,0x1C,0x6E,0x17,0xEF,0xDF,0xD6,0x0D,0xC2,0x87,0xBC,0x03,0x29,0xB4,0x4E,0x3C};
	byte plain[] = {0x00,0x18,0x00,0x16,0x00,0x01,0x00,0x00,0x04,0x31,0x00,0x00,0x00,0x01,0x00,0x00,0x13,0xD5,0x50,0x93,0xA4,0xA5,0x00,0x00,0x00,0x00,0x03,0x09,0x00,0x08,0x00,0x01,0x7B,0x97,0x28,0x47,0x00,0x02,0x00,0x36,0x00,0x12,0x00,0x02,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x14,0x00,0x1D,0x01,0x02,0x00,0x19,0x02,0x8D,0x25,0x57,0xB1,0xCF,0x01,0x38,0xF6,0x0A,0x8A,0x08,0xCD,0x5C,0x3D,0xEB,0x75,0x50,0x65,0xA2,0x64,0x80,0x2D,0xC0,0x9D};
	
	int len = 0;
	byte *crypt = NULL;
	CRYPTER *crpyter = new CRYPTER(key);	
	len = crpyter->encrypt(plain,93,crypt);
	pnt_byte(crypt,len);
	byte *result = NULL;
	len = crpyter->decrypt(crypt,len,result);
	pnt_byte(result,len);

	delete crpyter;

	
	/*
	byte *crypt = NULL;
	aaa *a = new aaa();
	a->t(plain,93,crypt);
	cout << crypt[0];;
	*/

	//pnt_byte(crypt,len);

	//delete[] key;
	//delete[] plain;
	//delete crypt;
	//delete crpyter;

	//encrypt(plain_all,93,key,16);
	//decrypt(out,out_len,key,16);
		
	/*
    unsigned long  v[2] = {0x20, 0x10};
    printf("Encrypt And Decrypt:\n");
    printf("%08X%08X\n", v[0], v[1]);
    encrypt(v, k);
    printf("%08X%08X\n", v[0], v[1]);
    decrypt(v, k);
    printf("%08X%08X\n", v[0], v[1]);
    printf("Key:\n");
    printf("%08X%08X%08X%08X\n", k[0], k[1], k[2], k[3]);
	*/
    return 0;
}
