#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
//#include <bitset>

#include "meow_hash_x64_aesni.h"
//#include "meow_intrinsics.h"
//#include "meow_hash.h"

using namespace std;

//#define Hashed_msg sdu_cst_20220610
//#define MSG ge_xiaoyao_202000460091
const char* MSG = "Ge Xiaoyao 202000460091";
const char* Hashed_msg = "sdu_cst_20220610";

#define movdqu(A, B)  A = _mm_loadu_si128((__m128i *)(B))
#define pxor(A, B)    A = _mm_xor_si128(A, B)
#define paddq(A, B) A = _mm_add_epi64(A, B)
#define aesenc(A, B)  A = _mm_aesenc_si128(A, B)

#define MEOW_INV_SHUFFLE(r0, r1, r2, r4, r5, r6) \
pxor(r1, r2); \
pxor(r4, r1); \
paddq(r5, r6); \
aesenc(r4, r6); \
paddq(r1, r5); \
pxor(r0, r4); \
aesenc(r0, r1); \
pxor(r0, r1);
// Xor one more time, so in the last line xor back


static void PrintHash(meow_u128 Hash) {
	printf("    %08X-%08X-%08X-%08X\n",
		MeowU32From(Hash, 3),
		MeowU32From(Hash, 2),
		MeowU32From(Hash, 1),
		MeowU32From(Hash, 0));
}

static void InvToGetKey(meow_umm Len, void* SourceInit, void* SourceEnd) {

	meow_u128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7; // NOTE(casey): xmm0-xmm7 are the hash accumulation lanes
	meow_u128 xmm8, xmm9, xmm10, xmm11, xmm12, xmm13, xmm14, xmm15; // NOTE(casey): xmm8-xmm15 hold values to be appended (residual, length)

	// Initialize the hash accumulation lanes.
	meow_u8* rcx = (meow_u8*)SourceInit;
	movdqu(xmm0, rcx + 0x00);
	movdqu(xmm1, rcx + 0x10);
	movdqu(xmm2, rcx + 0x20);
	movdqu(xmm3, rcx + 0x30);
	movdqu(xmm4, rcx + 0x40);
	movdqu(xmm5, rcx + 0x50);
	movdqu(xmm6, rcx + 0x60);
	movdqu(xmm7, rcx + 0x70);

	//PrintHash(xmm0);
	//PrintHash(xmm1);
	//PrintHash(xmm2);
	//PrintHash(xmm3);
	//PrintHash(xmm4);
	//PrintHash(xmm5);
	//PrintHash(xmm6);
	//PrintHash(xmm7);

	// Inverse Squeeze
	paddq(xmm0, xmm4);

	pxor(xmm0, xmm1);
	pxor(xmm4, xmm5);

	paddq(xmm0, xmm2);
	paddq(xmm1, xmm3);
	paddq(xmm4, xmm6);
	paddq(xmm5, xmm7);

	//PrintHash(xmm0);
	//PrintHash(xmm1);
	//PrintHash(xmm2);
	//PrintHash(xmm3);
	//PrintHash(xmm4);
	//PrintHash(xmm5);
	//PrintHash(xmm6);
	//PrintHash(xmm7);

	// Inverse Finalization
	MEOW_INV_SHUFFLE(xmm3, xmm4, xmm5, xmm7, xmm0, xmm1);
	MEOW_INV_SHUFFLE(xmm2, xmm3, xmm4, xmm6, xmm7, xmm0);
	MEOW_INV_SHUFFLE(xmm1, xmm2, xmm3, xmm5, xmm6, xmm7);
	MEOW_INV_SHUFFLE(xmm0, xmm1, xmm2, xmm4, xmm5, xmm6);
	MEOW_INV_SHUFFLE(xmm7, xmm0, xmm1, xmm3, xmm4, xmm5);
	MEOW_INV_SHUFFLE(xmm6, xmm7, xmm0, xmm2, xmm3, xmm4);
	MEOW_INV_SHUFFLE(xmm5, xmm6, xmm7, xmm1, xmm2, xmm3);
	MEOW_INV_SHUFFLE(xmm4, xmm5, xmm6, xmm0, xmm1, xmm2);
	MEOW_INV_SHUFFLE(xmm3, xmm4, xmm5, xmm7, xmm0, xmm1);
	MEOW_INV_SHUFFLE(xmm2, xmm3, xmm4, xmm6, xmm7, xmm0);
	MEOW_INV_SHUFFLE(xmm1, xmm2, xmm3, xmm5, xmm6, xmm7);
	MEOW_INV_SHUFFLE(xmm0, xmm1, xmm2, xmm4, xmm5, xmm6);

	//PrintHash(xmm0);
	//PrintHash(xmm1);
	//PrintHash(xmm2);
	//PrintHash(xmm3);
	//PrintHash(xmm4);
	//PrintHash(xmm5);
	//PrintHash(xmm6);
	//PrintHash(xmm7);

	// Inverse Absorb message
	
}


int main() {

	int Size = 32;
	char* Buffer = new char[Size];
	int MsgLen = strlen(MSG); // 23
	memset(Buffer, 0, Size);
	//memset(Buffer, (char)0, Size);
	memcpy(Buffer, MSG, strlen(MSG));

	//for (int i = 0; i < Size; i++) {
	//	cout << Buffer[i];
	//}
	//cout << endl;

	char* Key = new char[128];
	memset(Key, '0', 128);
	InvToGetKey(Size, Buffer, Key);

	return 0;
}
