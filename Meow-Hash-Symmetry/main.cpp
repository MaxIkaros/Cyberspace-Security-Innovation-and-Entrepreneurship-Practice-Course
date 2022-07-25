// https://github.com/cmuratori/meow_hash
// https://peter.website/meow-hash-cryptanalysis

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
//#include <bitset>

#include "meow_hash_x64_aesni.h"

using namespace std;

static void PrintHash(meow_u128 Hash) {
    printf("    %08X-%08X-%08X-%08X\n",
        MeowU32From(Hash, 3),
        MeowU32From(Hash, 2),
        MeowU32From(Hash, 1),
        MeowU32From(Hash, 0));
}


int main() {
    // NOTE(casey): Make a buffer with repeating numbers.
    int Size = 16000;
    char* Buffer = (char*)malloc(Size);
    for (int Index = 0;
        Index < Size;
        ++Index)
    {
        Buffer[Index] = (char)Index;
    }

    // NOTE(casey): Ask Meow for the hash
    meow_u128 Hash = MeowHash(MeowDefaultSeed, Size, Buffer);

    // NOTE(casey): Extract example smaller hash sizes you might want:
    long long unsigned Hash64 = MeowU64From(Hash, 0);
    int unsigned Hash32 = MeowU32From(Hash, 0);

    // NOTE(casey): Print the hash
    printf("  Hash of a test buffer:\n");
    PrintHash(Hash);

    free(Buffer);
	
	return 0;
}
