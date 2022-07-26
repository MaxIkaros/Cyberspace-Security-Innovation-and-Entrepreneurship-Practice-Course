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

#define movdqu(A, B)	    A = _mm_loadu_si128((__m128i *)(B))
#define pxor(A, B)	        A = _mm_xor_si128(A, B)
#define psubq(A, B)	        A = _mm_sub_epi64(A, B)
#define aesenc(A, B)	    A = _mm_aesenc_si128(A, B)
#define pxor_clear(A, B)	A = _mm_setzero_si128(); // NOTE(casey): pxor_clear is a nonsense thing that is only here because compilers don't detect xor(a, a) is clearing a :(
#define movq(A, B)          A = _mm_set_epi64x(0, B);
#define palignr(A, B, i)    A = _mm_alignr_epi8(A, B, i)
#define pshufb(A, B)        A = _mm_shuffle_epi8(A, B)
#define pand(A, B)          A = _mm_and_si128(A, B)


#define MEOW_INV_SHUFFLE(r0, r1, r2, r4, r5, r6) \
pxor(r1, r2);   \
pxor(r4, r1);   \
psubq(r5, r6);  \
aesenc(r4, r6); \
psubq(r1, r5);  \
pxor(r0, r4);   \
aesenc(r0, r1); \
pxor(r0, r1);
// Xor one more time, so in the last line xor back

#define INSTRUCTION_REORDER_BARRIER _ReadWriteBarrier()
#define MEOW_MIX_REG(r1, r2, r3, r4, r5,  i1, i2, i3, i4) \
pxor(r4, i4);                \
psubq(r5, i3);               \
pxor(r2, r4);                \
aesenc(r2, r4);              \
INSTRUCTION_REORDER_BARRIER; \
pxor(r2, r4);                \
pxor(r2, i2);                \
psubq(r3, i1);               \
pxor(r1, r2);                \
aesenc(r1, r2);              \
INSTRUCTION_REORDER_BARRIER; \
pxor(r1, r2);
// Xor one more time, so xor back

static void PrintHash(meow_u128 Hash) {
	printf("    %08X-%08X-%08X-%08X\n",
		MeowU32From(Hash, 3),
		MeowU32From(Hash, 2),
		MeowU32From(Hash, 1),
		MeowU32From(Hash, 0));
}

static void PrintKey(meow_u128 Hash1, meow_u128 Hash2) {
	printf("\t%08X%08X%08X%08X%08X%08X%08X%08X\n",
		MeowU32From(Hash1, 3),
		MeowU32From(Hash1, 2),
		MeowU32From(Hash1, 1),
		MeowU32From(Hash1, 0),
		MeowU32From(Hash2, 3),
		MeowU32From(Hash2, 2),
		MeowU32From(Hash2, 1),
		MeowU32From(Hash2, 0));
}

/// <summary>
/// Given a message m and target hash value h, one may compute a key k such that MeowHash(k, m) = h simply by running all the steps of the hash function backward from the output state all the way to the initial state.
/// </summary>
/// <param name="Len">
/// Length of message
/// </param>
/// <param name="HashedMsg">
/// Hash value
/// </param>
/// <param name="msg">
/// Message
/// </param>
static void InvToGetKey(meow_umm Len, void* HashedMsg, void* msg) {

	// NOTE(casey): xmm0-xmm7 are the hash accumulation lanes
	meow_u128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7;
	// NOTE(casey): xmm8-xmm15 hold values to be appended (residual, length)
	meow_u128 xmm8, xmm9, xmm10, xmm11, xmm12, xmm13, xmm14, xmm15;

	// Initialize the hash accumulation lanes.
	meow_u8* rcx = (meow_u8*)HashedMsg;
	movdqu(xmm0, rcx + 0x00); // 30313630-32323032-5F747363-5F756473
	movdqu(xmm1, rcx + 0x10); // 8000...
	movdqu(xmm2, rcx + 0x20); // random
	movdqu(xmm3, rcx + 0x30); // random
	movdqu(xmm4, rcx + 0x40); // random
	movdqu(xmm5, rcx + 0x50); // random
	movdqu(xmm6, rcx + 0x60); // random
	movdqu(xmm7, rcx + 0x70); // random

	//cout << "Hash message and other random messages: " << endl;
	//PrintHash(xmm0);
	//PrintHash(xmm1);
	//PrintHash(xmm2);
	//PrintHash(xmm3);
	//PrintHash(xmm4);
	//PrintHash(xmm5);
	//PrintHash(xmm6);
	//PrintHash(xmm7);
	//cout << endl;

	// Inverse Squeeze
	psubq(xmm0, xmm4);

	pxor(xmm0, xmm1);
	pxor(xmm4, xmm5);

	psubq(xmm0, xmm2);
	psubq(xmm1, xmm3);
	psubq(xmm4, xmm6);
	psubq(xmm5, xmm7);

	//cout << "Inverse Squeeze: " << endl;
	//PrintHash(xmm0);
	//PrintHash(xmm1);
	//PrintHash(xmm2);
	//PrintHash(xmm3);
	//PrintHash(xmm4);
	//PrintHash(xmm5);
	//PrintHash(xmm6);
	//PrintHash(xmm7);
	//cout << endl;

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

	//cout << "Inverse Finalization: " << endl;
	//PrintHash(xmm0);
	//PrintHash(xmm1);
	//PrintHash(xmm2);
	//PrintHash(xmm3);
	//PrintHash(xmm4);
	//PrintHash(xmm5);
	//PrintHash(xmm6);
	//PrintHash(xmm7);
	//cout << endl;

	/*-------------------------------------------------------------------------------------------------------*/
	// Honestly, I didn't understand the code for the end of the hash and the length information 
	// in the original article, so I can only put up the original author's related process from
	// meow_hash_x64_aesni.h.
	// BEGIN
	/*-------------------------------------------------------------------------------------------------------*/

	// NOTE(casey): Load any less-than-32-byte residual
	pxor_clear(xmm9, xmm9);
	pxor_clear(xmm11, xmm11);

	// TODO(casey): I need to put more thought into how the end-of-buffer stuff is actually working out here,
	// because I _think_ it may be possible to remove the first branch (on Len8) and let the mask zero out the
	// result, but it would take a little thought to make sure it couldn't read off the end of the buffer due
	// to the & 0xf on the align computation.

	// NOTE(casey): First, we have to load the part that is _not_ 16-byte aligned
	meow_u8* Last = (meow_u8*)msg + (Len & ~0xf);
	int unsigned Len8 = (Len & 0xf);
	if (Len8) {
		// NOTE(casey): Load the mask early
		movdqu(xmm8, &MeowMaskLen[0x10 - Len8]);

		meow_u8* LastOk = (meow_u8*)((((meow_umm)(((meow_u8*)msg) + Len - 1)) | (MEOW_PAGESIZE - 1)) - 16);
		int Align = (Last > LastOk) ? ((int)(meow_umm)Last) & 0xf : 0;
		movdqu(xmm10, &MeowShiftAdjust[Align]);
		movdqu(xmm9, Last - Align);
		pshufb(xmm9, xmm10);

		// NOTE(jeffr): and off the extra bytes
		pand(xmm9, xmm8);
	}

	// NOTE(casey): Next, we have to load the part that _is_ 16-byte aligned
	if (Len & 0x10) {
		xmm11 = xmm9;
		movdqu(xmm9, Last - 0x10);
	}

	// NOTE(casey): Construct the residual and length injests
	xmm8 = xmm9;
	xmm10 = xmm9;
	palignr(xmm8, xmm11, 15);
	palignr(xmm10, xmm11, 1);

	// NOTE(casey): We have room for a 128-bit nonce and a 64-bit none here, but
	// the decision was made to leave them zero'd so as not to confuse people
	// about hwo to use them or what security implications they had.
	pxor_clear(xmm12, xmm12);
	pxor_clear(xmm13, xmm13);
	pxor_clear(xmm14, xmm14);
	movq(xmm15, Len);
	palignr(xmm12, xmm15, 15);
	palignr(xmm14, xmm15, 1);

	/*-------------------------------------------------------------------------------------------------------*/
	// END
	/*-------------------------------------------------------------------------------------------------------*/

	// Inverse Absorb message

	// Append the length, to avoid problems with our 32-byte padding
	MEOW_MIX_REG(xmm1, xmm5, xmm7, xmm2, xmm3, xmm12, xmm13, xmm14, xmm15);

	// To maintain the mix-down pattern, we always Meow Mix the less-than-32-byte residual, even if it was empty
	MEOW_MIX_REG(xmm0, xmm4, xmm6, xmm1, xmm2, xmm8, xmm9, xmm10, xmm11);

	//cout << "Inverse Absorb message: " << endl;
	//PrintHash(xmm0);
	//PrintHash(xmm1);
	//PrintHash(xmm2);
	//PrintHash(xmm3);
	//PrintHash(xmm4);
	//PrintHash(xmm5);
	//PrintHash(xmm6);
	//PrintHash(xmm7);
	//cout << endl;

	cout << "==========================================================================================" << endl;
	cout << "KEY: " << endl;
	PrintKey(xmm0, xmm1);
	PrintKey(xmm2, xmm3);
	PrintKey(xmm4, xmm5);
	PrintKey(xmm6, xmm7);
	cout << endl;
	cout << "==========================================================================================" << endl;

	return;
}


int main() {

	int MsgLen = strlen(MSG); // 23
	char* message = new char[MsgLen + 1];
	memset(message, 0, MsgLen + 1);
	memcpy(message, MSG, MsgLen);

	int Hashed_MsgLen = strlen(Hashed_msg);
	char* Hashed_message = new char[Hashed_MsgLen + 1];
	memset(Hashed_message, 0, Hashed_MsgLen + 1);
	memcpy(Hashed_message, Hashed_msg, Hashed_MsgLen);

	cout << "Message: " << message << endl;
	cout << "Hashed Message: " << Hashed_message << endl;

	InvToGetKey(MsgLen, Hashed_message, message);
	//	1D41D39CAAFA345E910B12931FA48960E69A41F04DA2820C6E57684635554B54
	//	A42D5947375862999C43BD535BD8B06A79CE1FE4C3918589E41761CE2AD045E9
	//	BE6C92388741D67CFB528162B96FBAC409B4C28A538BE482B4E3DF06A639BB52
	//	7E26E1BBC65F7450DD1522890ED9550E7A597BB6AFF644325C3EF83066E5DD7E

	return 0;
}
