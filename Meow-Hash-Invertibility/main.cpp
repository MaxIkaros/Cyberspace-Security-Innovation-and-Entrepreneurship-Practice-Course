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
const char* MSG = "ge_xiaoyao_202000460091";
const char* Hashed_msg = "sdu_cst_20220610";

#define movdqu(A, B)  A = _mm_loadu_si128((__m128i *)(B))


static void PrintHash(meow_u128 Hash) {
    printf("    %08X-%08X-%08X-%08X\n",
        MeowU32From(Hash, 3),
        MeowU32From(Hash, 2),
        MeowU32From(Hash, 1),
        MeowU32From(Hash, 0));
}

int main() {
	
	int MsgLen = strlen(MSG); // 23
	int BlockNum = MsgLen / 32 + 1; // 1

	cout << "MsgLen: " << MsgLen << endl;
	cout << "BlockNum: " << BlockNum << endl;
	
	meow_u128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7; // NOTE(casey): xmm0-xmm7 are the hash accumulation lanes
	meow_u128 xmm8, xmm9, xmm10, xmm11, xmm12, xmm13, xmm14, xmm15; // NOTE(casey): xmm8-xmm15 hold values to be appended (residual, length)

	meow_u8* rcx = (meow_u8*)Hashed_msg;
	movdqu(xmm0, Hashed_msg + 0x00); // Load the hashed message into xmm0
	movdqu(xmm1, 0); // Load the 0's into xmm1
	movdqu(xmm2, 0); // Load the 0's into xmm2
	movdqu(xmm3, 0); // Load the 0's into xmm3
	movdqu(xmm4, 0); // Load the 0's into xmm4
	movdqu(xmm5, 0); // Load the 0's into xmm5
	movdqu(xmm6, 0); // Load the 0's into xmm6
	movdqu(xmm7, 0); // Load the 0's into xmm7

	PrintHash(xmm0);
	
    return 0;
}
