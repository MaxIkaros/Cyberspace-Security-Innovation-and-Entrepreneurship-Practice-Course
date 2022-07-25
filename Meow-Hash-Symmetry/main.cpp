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
    //symmetrize32 = hex_to_bytes(
    //    "aa694fb61039bf2c7e2d743dc1bb2e19a97070a970f2a9c1a9700172f20195a9"
    //    "2000000000000000000000000000000000000000000000000000000000000000"
    //    "63e4e370970793d3ac543500ba51dc9d09636363636363d06363b76363b76363"
    //    "0000000000000000000000000000000000000000000000000000000000000000"
    //)
	
    int BufSize = 32;
	char* Buffer = new char[BufSize];
	//char* Buffer = new char[BufSize + 1];
	memset(Buffer, 0, BufSize);
	//memset(Buffer, 0, BufSize + 1);
	memcpy(Buffer, "abcdefghabcdefghaijklmnhaijklmnh", BufSize);

	cout << "Message: " << Buffer << endl;
	
	//http://tools.bugscaner.com/text/hex2bytes.html
    static meow_u8 Key[128] = {
        0xaa, 0x69, 0x4f, 0xb6, 0x10, 0x39, 0xbf, 0x2c, 
        0x7e, 0x2d, 0x74, 0x3d, 0xc1, 0xbb, 0x2e, 0x19, 
        0xa9, 0x70, 0x70, 0xa9, 0x70, 0xf2, 0xa9, 0xc1, 
        0xa9, 0x70, 0x01, 0x72, 0xf2, 0x01, 0x95, 0xa9, //
        0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
        0x63, 0xe4, 0xe3, 0x70, 0x97, 0x07, 0x93, 0xd3, 
        0xac, 0x54, 0x35, 0x00, 0xba, 0x51, 0xdc, 0x9d, 
        0x09, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0xd0, 
        0x63, 0x63, 0xb7, 0x63, 0x63, 0xb7, 0x63, 0x63, //
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
    };
	
 //   int KeySize = 256;
	//char* Key = new char[KeySize + 1];
	//memset(Key, 0, KeySize + 1);
	//memcpy(Key, "aa694fb61039bf2c7e2d743dc1bb2e19a97070a970f2a9c1a9700172f20195a9" \
 //           "2000000000000000000000000000000000000000000000000000000000000000" \
 //           "63e4e370970793d3ac543500ba51dc9d09636363636363d06363b76363b76363" \
 //           "0000000000000000000000000000000000000000000000000000000000000000", KeySize);

	//cout << "Key: " << Key << endl;
	
    // NOTE(casey): Make a buffer with repeating numbers.
    //int Size = 16000;
    //char* Buffer = (char*)malloc(Size);
    //for (int Index = 0;
    //    Index < Size;
    //    ++Index)
    //{
    //    Buffer[Index] = (char)Index;
    //}

    // NOTE(casey): Ask Meow for the hash
    //meow_u128 Hash = MeowHash(Key, BufSize, "abcdefghabcdefghaijklmnhaijklmnh");
    meow_u128 Hash = MeowHash(Key, BufSize, Buffer);

    // NOTE(casey): Extract example smaller hash sizes you might want:
    long long unsigned Hash64 = MeowU64From(Hash, 0);
    int unsigned Hash32 = MeowU32From(Hash, 0);

    // NOTE(casey): Print the hash
    printf("  Hash of a test buffer:\n");
    PrintHash(Hash);

    delete(Buffer);
	
	return 0;
}
