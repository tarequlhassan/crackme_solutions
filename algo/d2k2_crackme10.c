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
	char *basedec = "bXVkbG9yZGlzZ3JlYXQhP0JCQkJCQkJCQkJCQkJCQkJBQUFBQUFBQUFBQUFBQUFBQ0NDQ0NDQ0NDQ0NDQ0NDQ0RERERERERERERERERERERFRUVFRUVFRUVFRUVFRUVFRkZGRkZGRkZGRkZGRkZGRjEyMzQ1Njc4OTBBQkNERUY=";
	BYTE b64enc[255] = { 0 };

	//base64_encode(b64enc, "mudlordisgreat", strlen("mudlordisgreat"));

	base64_decode(b64enc, basedec, 0);
	
	int64_t* base64_ptr = b64enc;
	__m128i buf2_mask_mmx = _mm_loadl_epi64(buf2);
	for (int i = 0; i < 16; i++)
	{
		__m128i var1_mmx = _mm_loadl_epi64(base64_ptr);
	    var1_mmx= _mm_xor_si128(buf2_mask_mmx, var1_mmx);
		_mm_storeu_si64(base64_ptr, var1_mmx);
		base64_ptr++;
	}



	BYTE data[0x80]=
	{
		0x3A, 0x5B, 0xED, 0x01, 0x6B, 0xCD, 0x7E, 0xAA, 0x24, 0x49, 0xFB, 0x08, 0x65, 0xCB, 0x3B, 0xFC,
			0x15, 0x6C, 0xCB, 0x2F, 0x46, 0xFD, 0x58, 0x81, 0x15, 0x6C, 0xCB, 0x2F, 0x46, 0xFD, 0x58, 0x81,
			0x16, 0x6F, 0xC8, 0x2C, 0x45, 0xFE, 0x5B, 0x82, 0x16, 0x6F, 0xC8, 0x2C, 0x45, 0xFE, 0x5B, 0x82,
			0x14, 0x6D, 0xCA, 0x2E, 0x47, 0xFC, 0x59, 0x80, 0x14, 0x6D, 0xCA, 0x2E, 0x47, 0xFC, 0x59, 0x80,
			0x13, 0x6A, 0xCD, 0x29, 0x40, 0xFB, 0x5E, 0x87, 0x13, 0x6A, 0xCD, 0x29, 0x40, 0xFB, 0x5E, 0x87,
			0x12, 0x6B, 0xCC, 0x28, 0x41, 0xFA, 0x5F, 0x86, 0x12, 0x6B, 0xCC, 0x28, 0x41, 0xFA, 0x5F, 0x86,
			0x11, 0x68, 0xCF, 0x2B, 0x42, 0xF9, 0x5C, 0x85, 0x11, 0x68, 0xCF, 0x2B, 0x42, 0xF9, 0x5C, 0x85,
			0x66, 0x1C, 0xBA, 0x59, 0x31, 0x89, 0x2D, 0xFB, 0x6E, 0x1E, 0xC8, 0x2F, 0x47, 0xFB, 0x5F, 0x85
	};
	

	wsprintf(serial_out, "shit!");
}


