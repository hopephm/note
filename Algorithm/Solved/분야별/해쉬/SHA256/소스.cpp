#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

typedef unsigned char       uint8_t;
typedef          char        int8_t;
typedef unsigned short     uint16_t;
typedef          short      int16_t;
typedef unsigned int       uint32_t;
typedef          int        int32_t;
typedef unsigned long long uint64_t;
typedef          long long  int64_t;

#define SWAP32(l) ((((l) & 0xff000000) >> 24) | (((l) & 0x00ff0000) >> 8)  | (((l) & 0x0000ff00) << 8)  | (((l) & 0x000000ff) << 24))  

#define ROTL(x,n,w)   ((x << n) | (x >> (w-n)))  
#define ROTR(x,n,w)   ((x >> n) | (x << (w-n)))  
#define SHR(x,n)      (x >> n)  

#define Ch(x,y,z)   ((x & y) ^ (~x & z))  
#define Maj(x,y,z)  ((x & y) ^ (x & z) ^ (y & z))  

/* Constant for SHA-224 & SHA-256 */
uint32_t K32[64] = {
0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

uint32_t S256_H[8];

uint32_t sigma0_32(uint32_t x)
{
	return ROTR(x, 7, 32) ^ ROTR(x, 18, 32) ^ SHR(x, 3);
}

uint32_t sigma1_32(uint32_t x)
{
	return ROTR(x, 17, 32) ^ ROTR(x, 19, 32) ^ SHR(x, 10);
}

uint32_t SIGMA0_32(uint32_t x)
{
	return ROTR(x, 2, 32) ^ ROTR(x, 13, 32) ^ ROTR(x, 22, 32);
}

uint32_t SIGMA1_32(uint32_t x)
{
	return ROTR(x, 6, 32) ^ ROTR(x, 11, 32) ^ ROTR(x, 25, 32);
}

void S256_init_Hash(void)
{
	S256_H[0] = 0x6a09e667;
	S256_H[1] = 0xbb67ae85;
	S256_H[2] = 0x3c6ef372;
	S256_H[3] = 0xa54ff53a;
	S256_H[4] = 0x510e527f;
	S256_H[5] = 0x9b05688c;
	S256_H[6] = 0x1f83d9ab;
	S256_H[7] = 0x5be0cd19;
}

void S256_message_schedule(uint32_t M[16], uint32_t W[64])
{
	uint16_t t;

	for (t = 0; t < 64; t++)
	{
		if (t < 16) W[t] = SWAP32(M[t]);
		else W[t] = sigma1_32(W[t - 2]) + W[t - 7] + sigma0_32(W[t - 15]) + W[t - 16];
	}
}



void S256_init_working_variables(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d,
	uint32_t *e, uint32_t *f, uint32_t *g, uint32_t *h)
{
	*a = S256_H[0];
	*b = S256_H[1];
	*c = S256_H[2];
	*d = S256_H[3];
	*e = S256_H[4];
	*f = S256_H[5];
	*g = S256_H[6];
	*h = S256_H[7];
}

void S256_Hash_computation(uint32_t M[16], uint32_t W[64],
	uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d,
	uint32_t *e, uint32_t *f, uint32_t *g, uint32_t *h)
{
	uint16_t t;
	uint32_t T1, T2;

	printf("          A        B        C        D        E        F        G        H\n");
	for (t = 0; t < 64; t++)
	{
		T1 = *h + SIGMA1_32(*e) + Ch(*e, *f, *g) + K32[t] + W[t];
		T2 = SIGMA0_32(*a) + Maj(*a, *b, *c);
		*h = *g;
		*g = *f;
		*f = *e;
		*e = *d + T1;
		*d = *c;
		*c = *b;
		*b = *a;
		*a = T1 + T2;
		printf("t=%2u: %08X %08X %08X %08X %08X %08X %08X %08X \n", t, *a, *b, *c, *d, *e, *f, *g, *h);
	}

	S256_H[0] = *a + S256_H[0];
	S256_H[1] = *b + S256_H[1];
	S256_H[2] = *c + S256_H[2];
	S256_H[3] = *d + S256_H[3];
	S256_H[4] = *e + S256_H[4];
	S256_H[5] = *f + S256_H[5];
	S256_H[6] = *g + S256_H[6];
	S256_H[7] = *h + S256_H[7];
}

int main(int argc, char* argv[])
{
	uint32_t a32, b32, c32, d32, e32, f32, g32, h32;
	uint32_t W32[64];
	uint32_t M32[16];
	uint8_t  *M;
	char *ptr;
	uint32_t i, j;
	uint32_t message_len = 0;
	uint32_t check_more = 0;

	//ptr = argv[1];  
	//ptr = "abc";  
	ptr = (char*)"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";

	if (*ptr == '0' && *(ptr + 1) == 'x') ptr += 2;
	S256_init_Hash();

	printf("Initial hash value:\n");
	for (i = 0; i < 8; i++) printf("H[%u] = %08lX\n", i, S256_H[i]);

	while (*ptr != '\0' || check_more == 1)
	{
		M = (uint8_t *)M32;

		for (i = 0; i < 56; i++)
		{
			if (*ptr == '\0') break;
			M[i] = *ptr;
			*ptr++;
		}
		message_len += i * 8;
		printf("ml = %lu\n", message_len);

		if (i == 56)
		{
			check_more = 1;
			M[i++] = 0x80;
			for (; i < 64; i++) M[i] = 0x00;
		}
		else
		{
			check_more = 0;
			for (; i < 60; i++) M[i] = 0x00;
			*(uint32_t*)&M[60] = SWAP32(message_len);
		}

		printf("Block Contents:\n");
		for (i = 0, j = 0; i < 64; i += 4, j++) printf("M[%u] = %02X%02X%02X%02X\n", j, M[i], M[i + 1], M[i + 2], M[i + 3]);

		S256_message_schedule(M32, W32);
		S256_init_working_variables(&a32, &b32, &c32, &d32, &e32, &f32, &g32, &h32);
		S256_Hash_computation(M32, W32, &a32, &b32, &c32, &d32, &e32, &f32, &g32, &h32);
	}

	printf("SHA256 Message Digest: %08lX %08lX %08lX %08lX %08lX %08lX %08lX %08lX\n", S256_H[0], S256_H[1], S256_H[2], S256_H[3], S256_H[4], S256_H[5], S256_H[6], S256_H[7]);


	return 0;
}

