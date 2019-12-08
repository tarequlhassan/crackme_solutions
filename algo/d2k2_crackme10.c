#include <windows.h>
#include <wincrypt.h>
#include <stdbool.h>
#include <stdint.h>

typedef union
{
	uint64_t rx;
	uint32_t ex;
	uint16_t x;
	struct { uint8_t lo, hi; }b;
} Register;

void MD5(BYTE * data, ULONG len, BYTE* hash_data)
{
	HCRYPTPROV hProv = 0;
	HCRYPTPROV hHash = 0;
	CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0);
	CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash);
	CryptHashData(hHash, data, len, 0);
	DWORD cbHash = 16;
	CryptGetHashParam(hHash, HP_HASHVAL, hash_data, &cbHash, 0);
	CryptDestroyHash(hHash);
	CryptReleaseContext(hProv, 0);
}

void process_serial(char* name, char* serial_out)
{
	BYTE md5_hash[16] = { 0 };
	BYTE buf1[16] = { 0 };
	BYTE buf2[16] = { 0 };

	unsigned char name2[50] = { 0 };
	strcpy(name2, name);
	strcat(name2, "-diablo2oo2");
	int namelen = lstrlen(name2);
	MD5((BYTE*)name2, namelen, (BYTE*)md5_hash);

	for (int i = 0; i < 16; i++) buf1[i] = i;
	//1234567890ABCDEF
	//0040153B - alters MD5 hash.
	for (int k = 0; k < 16; k++)
	{
		for (int i = 0; i < 16; i++)
		{
			Register EAX, EDX, EBX;
			EAX.ex = md5_hash[i];
			EDX = EAX;
			EAX.b.lo &= 0xF;
			EDX.b.lo >>= 4;
			EBX.b.lo = buf1[EAX.ex];
			buf1[EAX.ex] = buf1[EDX.ex];
			buf1[EDX.ex] = EBX.b.lo;
			md5_hash[i] += EBX.b.lo;
			md5_hash[i] ^= 0x17;
		}
	}

	
	for (int i = 0,k=0; i < 8; i++,k+=2)
		buf2[i] = (buf1[k] << 4 )+ (buf1[k + 1] % 0x0F);
	wsprintf(serial_out, "test");
}


