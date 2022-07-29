// https://github.com/cmuratori/meow_hash
// https://peter.website/meow-hash-cryptanalysis
// https://www.anquanke.com/post/id/260323

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "meow_hash_x64_aesni.h"

using namespace std;

const char* MSG = "Ge Xiaoyao 202000460091";
const char* Hashed_msg = "sdu_cst_20220610";

#define movdqu(A, B)	    A = _mm_loadu_si128((__m128i *)(B))
#define movdqu_mem(A, B)        _mm_storeu_si128((__m128i *)(A), B)
#define pxor(A, B)	        A = _mm_xor_si128(A, B)
#define psubq(A, B)	        A = _mm_sub_epi64(A, B)
#define aesenc(A, B)	    A = _mm_aesenc_si128(A, B)
#define pxor_clear(A, B)	A = _mm_setzero_si128(); // NOTE(casey): pxor_clear is a nonsense thing that is only here because compilers don't detect xor(a, a) is clearing a :(
#define movq(A, B)          A = _mm_set_epi64x(0, B);
#define palignr(A, B, i)    A = _mm_alignr_epi8(A, B, i)
#define pshufb(A, B)        A = _mm_shuffle_epi8(A, B)
#define pand(A, B)          A = _mm_and_si128(A, B)

static meow_u128 xmm_allzero = _mm_setzero_si128(); // All zero

//https://www.anquanke.com/post/id/260323
#define inv_mixcol(A)		A = _mm_aesimc_si128(A) // AES-128-ECB invert mix columns
#define MixColumns(A)		A = _mm_aesdeclast_si128(A, xmm_allzero); A = _mm_aesenc_si128(A, xmm_allzero) // AES-128-ECB mix columns
#define SubBytes(A)			A = _mm_shuffle_epi8(A, xmm_SubBytes); A = _mm_aesenc_si128(A, xmm_allzero) // AES-128-ECB sub bytes
#define ShiftRows(A)		A = _mm_shuffle_epi8(A, xmm_ShiftRows) // AES-128-ECB shift rows

#define inv_aesdec(A, B) \
pxor(A, B);              \
MixColumns(A);           \
aesenc(A, xmm_allzero);  \
inv_mixcol(A)

#define MEOW_INV_SHUFFLE(r0, r1, r2, r4, r5, r6) \
pxor(r1, r2);         \
inv_aesdec(r4, r1);   \
psubq(r5, r6);        \
pxor(r4, r6);         \
psubq(r1, r5);        \
inv_aesdec(r0, r4);

#define INSTRUCTION_REORDER_BARRIER _ReadWriteBarrier()
#define MEOW_INV_MIX_REG(r1, r2, r3, r4, r5,  i1, i2, i3, i4) \
pxor(r4, i4);                \
psubq(r5, i3);               \
INSTRUCTION_REORDER_BARRIER; \
inv_aesdec(r2, r4);          \
pxor(r2, i2);                \
psubq(r3, i1);               \
INSTRUCTION_REORDER_BARRIER; \
inv_aesdec(r1, r2);          \

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

static void PrintBytes(meow_u128 Hash1, meow_u128 Hash2) {
	//for (int i = 0; i < 32; i++) {
	//	int tmp = MeowU8From(Hash1, i);
	//	printf("%02X", tmp);
	//}
	//printf("\n");
	//for (int i = 0; i < 32; i++) {
	//	int tmp = MeowU8From(Hash2, i);
	//	printf("%02X", tmp);
	//}
	//printf("\n");

	printf("\t%02X%02X%02X%02X %02X%02X%02X%02X %02X%02X%02X%02X %02X%02X%02X%02X \n\t%02X%02X%02X%02X %02X%02X%02X%02X %02X%02X%02X%02X %02X%02X%02X%02X \n",
		MeowU8From(Hash1, 0), MeowU8From(Hash1, 1),
		MeowU8From(Hash1, 2), MeowU8From(Hash1, 3),
		MeowU8From(Hash1, 4), MeowU8From(Hash1, 5),
		MeowU8From(Hash1, 6), MeowU8From(Hash1, 7),

		MeowU8From(Hash1, 8), MeowU8From(Hash1, 9),
		MeowU8From(Hash1, 10), MeowU8From(Hash1, 11),
		MeowU8From(Hash1, 12), MeowU8From(Hash1, 13),
		MeowU8From(Hash1, 14), MeowU8From(Hash1, 15),

		MeowU8From(Hash2, 0), MeowU8From(Hash2, 1),
		MeowU8From(Hash2, 2), MeowU8From(Hash2, 3),
		MeowU8From(Hash2, 4), MeowU8From(Hash2, 5),
		MeowU8From(Hash2, 6), MeowU8From(Hash2, 7),

		MeowU8From(Hash2, 8), MeowU8From(Hash2, 9),
		MeowU8From(Hash2, 10), MeowU8From(Hash2, 11),
		MeowU8From(Hash2, 12), MeowU8From(Hash2, 13),
		MeowU8From(Hash2, 14), MeowU8From(Hash2, 15));
}

static void PrintByte(meow_u128 Hash) {
	printf("\t%02X%02X%02X%02X %02X%02X%02X%02X %02X%02X%02X%02X %02X%02X%02X%02X\n",
		MeowU8From(Hash, 0), MeowU8From(Hash, 1),
		MeowU8From(Hash, 2), MeowU8From(Hash, 3),
		MeowU8From(Hash, 4), MeowU8From(Hash, 5),
		MeowU8From(Hash, 6), MeowU8From(Hash, 7),

		MeowU8From(Hash, 8), MeowU8From(Hash, 9),
		MeowU8From(Hash, 10), MeowU8From(Hash, 11),
		MeowU8From(Hash, 12), MeowU8From(Hash, 13),
		MeowU8From(Hash, 14), MeowU8From(Hash, 15));
}

static void PrintHex(meow_u128 Hash) {
	printf("0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X,\n",
		MeowU8From(Hash, 0), MeowU8From(Hash, 1),
		MeowU8From(Hash, 2), MeowU8From(Hash, 3),
		MeowU8From(Hash, 4), MeowU8From(Hash, 5),
		MeowU8From(Hash, 6), MeowU8From(Hash, 7));
	printf("0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X,\n\n",
		MeowU8From(Hash, 8), MeowU8From(Hash, 9),
		MeowU8From(Hash, 10), MeowU8From(Hash, 11),
		MeowU8From(Hash, 12), MeowU8From(Hash, 13),
		MeowU8From(Hash, 14), MeowU8From(Hash, 15));
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
static void InvToGetKey(meow_umm Len, void* HashedMsg, void* msg, void* Key_Gen) {

	// NOTE(casey): xmm0-xmm7 are the hash accumulation lanes
	meow_u128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7;
	// NOTE(casey): xmm8-xmm15 hold values to be appended (residual, length)
	meow_u128 xmm8, xmm9, xmm10, xmm11, xmm12, xmm13, xmm14, xmm15;

// Initialize the hash accumulation lanes.
	meow_u8* rcx = (meow_u8*)HashedMsg;
	movdqu(xmm0, rcx + 0x00); // PrintHash = 30313630-32323032-5F747363-5F756473
	movdqu(xmm1, rcx + 0x10); // PrintHash = 8000...
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

// Inverse Squeeze(1-round)
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

// Inverse Finalization (12-round)
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

// Inverse Absorb message

	// Append the length, to avoid problems with our 32-byte padding
	MEOW_INV_MIX_REG(xmm1, xmm5, xmm7, xmm2, xmm3, xmm12, xmm13, xmm14, xmm15);

	// To maintain the mix-down pattern, we always Meow Mix the less-than-32-byte residual, even if it was empty
	MEOW_INV_MIX_REG(xmm0, xmm4, xmm6, xmm1, xmm2, xmm8, xmm9, xmm10, xmm11);

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

	//// Print the answer
	//printf("%s\n", "===================================================");
	//printf("%s\n", "KEY: ");
	
	// The same type of https://peter.website/meow-hash-cryptanalysis
	//PrintBytes(xmm0, xmm1);
	//PrintBytes(xmm2, xmm3);
	//PrintBytes(xmm4, xmm5);
	//PrintBytes(xmm6, xmm7);
	//printf("\n");
	
	// copy for meow_u8 []
	//PrintHex(xmm0);
	//PrintHex(xmm1);
	//PrintHex(xmm2);
	//PrintHex(xmm3);
	//PrintHex(xmm4);
	//PrintHex(xmm5);
	//PrintHex(xmm6);
	//PrintHex(xmm7);

	//printf("%s", "===================================================");

	meow_u8* rax = (meow_u8*)Key_Gen;
	movdqu_mem(rax + 0x00, xmm0);
	movdqu_mem(rax + 0x10, xmm1);
	movdqu_mem(rax + 0x20, xmm2);
	movdqu_mem(rax + 0x30, xmm3);
	movdqu_mem(rax + 0x40, xmm4);
	movdqu_mem(rax + 0x50, xmm5);
	movdqu_mem(rax + 0x60, xmm6);
	movdqu_mem(rax + 0x70, xmm7);
	Key_Gen = rax;

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

// Get Key
	meow_u8 Key_Gen[129];
	memset(Key_Gen, 0, 129);
	InvToGetKey(MsgLen, Hashed_message, message, Key_Gen); // Different everytime

// Print the generated key
	printf("\n%s\n", "===================================================");
	printf("%s\n\t", "Generated key: ");
	for (int i = 0; i < 128; i++) {
		printf("%02X", (int)Key_Gen[i]);
		if (i % 4 == 3) {
			printf(" ");
		}
		if (i % 16 == 15) {
			printf("\n\t");
		}
	}
	printf("\b\b\b\b\b\b\b\b%s\n", "===================================================");
	
// Verify the key
	// NOTE(casey): Ask Meow for the hash
	//meow_u128 Hash = MeowHash(Key, BufSize, Buffer);
	meow_u128 Hash = MeowHash(Key_Gen, MsgLen, message);

	// NOTE(casey): Print the hash
	cout << "\n===================================================" << endl;
	cout << "Hash of the message above: " << endl;
	//PrintHash(Hash);
	//PrintByte(Hash);
	
	meow_u8 Hash_Gen[17];
	memset(Hash_Gen, 0, 17);
	movdqu_mem(Hash_Gen + 0x00, Hash);
	printf("\t%s\n", Hash_Gen);
	//printf("\t");
	//for (int i = 0; i < 16; i++) {
	//	printf("%c", Hash_Gen[i]);
	//}
	cout << "===================================================" << endl;

	
	return 0;
}
