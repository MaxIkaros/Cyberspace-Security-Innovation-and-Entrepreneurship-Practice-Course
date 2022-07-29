// https://github.com/cmuratori/meow_hash
// https://peter.website/meow-hash-cryptanalysis

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
//#include <bitset>

#include "meow_hash_x64_aesni.h"

using namespace std;

const char* MESSAGE = "abcdefghabcdefghaijklmnhaijklmnh";
const int MSG_LEN = strlen(MESSAGE);

//http://tools.bugscaner.com/text/hex2bytes.html
	//symmetrize32 = hex_to_bytes(
	//    "aa694fb61039bf2c7e2d743dc1bb2e19a97070a970f2a9c1a9700172f20195a9"
	//    "2000000000000000000000000000000000000000000000000000000000000000"
	//    "63e4e370970793d3ac543500ba51dc9d09636363636363d06363b76363b76363"
	//    "0000000000000000000000000000000000000000000000000000000000000000"
	//)
meow_u8 Key[128] = { // Key for 32-bit message
	0xaa, 0x69, 0x4f, 0xb6, 0x10, 0x39, 0xbf, 0x2c,
	0x7e, 0x2d, 0x74, 0x3d, 0xc1, 0xbb, 0x2e, 0x19,
	0xa9, 0x70, 0x70, 0xa9, 0x70, 0xf2, 0xa9, 0xc1,
	0xa9, 0x70, 0x01, 0x72, 0xf2, 0x01, 0x95, 0xa9, // "aa694fb61039bf2c7e2d743dc1bb2e19a97070a970f2a9c1a9700172f20195a9"
	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // "2000000000000000000000000000000000000000000000000000000000000000"
	0x63, 0xe4, 0xe3, 0x70, 0x97, 0x07, 0x93, 0xd3,
	0xac, 0x54, 0x35, 0x00, 0xba, 0x51, 0xdc, 0x9d,
	0x09, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0xd0,
	0x63, 0x63, 0xb7, 0x63, 0x63, 0xb7, 0x63, 0x63, // "63e4e370970793d3ac543500ba51dc9d09636363636363d06363b76363b76363"
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // "0000000000000000000000000000000000000000000000000000000000000000"
};


void PrintHash(meow_u128 Hash) {
	printf("    %08X-%08X-%08X-%08X\n",
		MeowU32From(Hash, 3),
		MeowU32From(Hash, 2),
		MeowU32From(Hash, 1),
		MeowU32From(Hash, 0));
}


int main() {

	int BufSize = MSG_LEN;
	char* Buffer = new char[BufSize + 1]; // +1 for null terminator
	memset(Buffer, 0, BufSize + 1); // +1 for null terminator
	memcpy(Buffer, MESSAGE, BufSize);

	cout << "Message: " << Buffer << endl;
	cout << "Message size: " << BufSize << endl;


	// NOTE(casey): Ask Meow for the hash
	meow_u128 Hash = MeowHash(Key, BufSize, Buffer);

	// NOTE(casey): Print the hash
	cout << "==========================================================" << endl;
	cout << "Hash of the message above: " << endl;
	PrintHash(Hash);
	cout << "==========================================================" << endl;

	delete[] Buffer;

	return 0;
}
