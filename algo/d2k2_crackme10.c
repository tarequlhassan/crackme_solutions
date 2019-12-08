#include <windows.h>
#include <wincrypt.h>
#include <stdbool.h>
#include <stdint.h>
#include <intrin.h>
#include "d2k2_crackme10_base64.h"

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

	for (int i = 0, k = 0; i < 8; i++, k += 2)
	{
		int j = buf1[k] << 4;
		int l = buf1[k + 1] & 0x0F;
		buf2[i] = j+l;
	}
		
	//just some test data.
	//char *basedec = "bXVkbG9yZGlzZ3JlYXQhP0JCQkJCQkJCQkJCQkJCQkJBQUFBQUFBQUFBQUFBQUFBQ0NDQ0NDQ0NDQ0NDQ0NDQ0RERERERERERERERERERERFRUVFRUVFRUVFRUVFRUVFRkZGRkZGRkZGRkZGRkZGRjEyMzQ1Njc4OTBBQkNERUY=";
	//BYTE b64enc[255] = { 0 };

	

	//base64_decode(b64enc, basedec, 0);
	
	/*int64_t* base64_ptr = b64enc;
	__m128i buf2_mask_mmx = _mm_loadl_epi64(buf2);
	for (int i = 0; i < 16; i++)
	{
		__m128i var1_mmx = _mm_loadl_epi64(base64_ptr);
	    var1_mmx= _mm_xor_si128(buf2_mask_mmx, var1_mmx);
		_mm_storeu_si64(base64_ptr, var1_mmx);
		base64_ptr++;
	}*/


	BYTE soduku[16][16] = { 0 };
	for (int i=0;i<16;i++)
	{
        soduku[i][i] = buf1[i];
	}

	


	BYTE b64encstr[255] = { 0 };
	base64_encode(b64encstr, soduku, 0x80);



	/*
	BYTE buf3[0x80] = { 0 };
	for (int i = 0; i < 0x80; i++)
	{
		Register EAX, EDX;
		EAX.ex = b64enc[i];
		EDX.ex = EAX.ex;
		EAX.b.lo &= 0x0F;
		EDX.b.lo >>= 0x04;
		buf3[i*2] = EDX.b.lo;
		buf3[i*2 + 1] = EAX.b.lo;
	}*/

	//base64_encode(b64enc, "mudlordisgreat", strlen("mudlordisgreat"));
	
	wsprintf(serial_out,"%s", b64encstr);

	
}


