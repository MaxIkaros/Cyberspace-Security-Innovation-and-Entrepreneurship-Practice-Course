#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "meow_hash_x64_aesni.h"
//#include "meow_intrinsics.h"
//#include "meow_hash.h"

//#define Hashed_msg sdu_cst_20220610
//#define Msg ge_xiaoyao_202000460091
const char* Msg = "ge_xiaoyao_202000460091";
const char* Hashed_msg = "sdu_cst_20220610";


static void PrintHash(meow_u128 Hash) {
    printf("    %08X-%08X-%08X-%08X\n",
        MeowU32From(Hash, 3),
        MeowU32From(Hash, 2),
        MeowU32From(Hash, 1),
        MeowU32From(Hash, 0));
}

int main() {
	
	// Make a buffer with repeating numbers (after Msg).
	int MsgLen = strlen(Msg);
	int Size = MsgLen / 32;
	if (MsgLen % 32 != 0) Size++; // Add one for the last block.
	char *Buffer = new char[Size];
	for (int i = 0; i < MsgLen; i++) {
		Buffer[i] = Msg[i]; // Copy Msg into Buffer.
	}
	for (int i = MsgLen; i < Size; i++) {
		Buffer[i] = (char)0; // Fill the rest with zeros.
	}
	
	
	
    return 0;
}
