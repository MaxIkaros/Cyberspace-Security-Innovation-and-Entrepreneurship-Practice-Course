// https://github.com/cmuratori/meow_hash
// https://peter.website/meow-hash-cryptanalysis
// https://www.anquanke.com/post/id/260323

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "meow_hash_x64_aesni.h"

using namespace std;

//const char* MESSAGE = "abcdefghabcdefghaijklmnhaijklmnh"; // 32
//const char* MESSAGE = "abcdefghabcdefghabcdefghabcdefgh";

// Every 32-Byte can satisfy the format of "abcdefghabcdefghaijklmnhaijklmnh"
//const char* MESSAGE = "abcdefghabcdefghabcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh"; // 64
//const char* MESSAGE = "abcdefghabcdefghaijklmnhaijklmnhabcdefghabcdefghaijklmnhaijklmnh"; // 64
const char* MESSAGE = "abcdefghabcdefghaijklmnhaijklmnhopqrstuvopqrstuvowxyz01vowxyz01v"; // 64-Byte standard style

const int MSG_LEN = strlen(MESSAGE);

	//symmetrize32 = hex_to_bytes(
	//    "aa694fb61039bf2c7e2d743dc1bb2e19a97070a970f2a9c1a9700172f20195a9"
	//    "2000000000000000000000000000000000000000000000000000000000000000"
	//    "63e4e370970793d3ac543500ba51dc9d09636363636363d06363b76363b76363"
	//    "0000000000000000000000000000000000000000000000000000000000000000"
	//)
	//AA694FB6 1039BF2C 7E2D743D C1BB2E19
	//A97070A9 70F2A9C1 A9700172 F20195A9
	//20000000 00000000 00000000 00000000
	//00000000 00000000 00000000 00000000
	//63E4E370 970793D3 AC543500 BA51DC9D
	//09636363 636363D0 6363B763 63B76363
	//00000000 00000000 00000000 00000000
	//00000000 00000000 00000000 00000000
//meow_u8 Key[128] = { // Key for 32-bit message
//  //"aa694fb61039bf2c7e2d743dc1bb2e19a97070a970f2a9c1a9700172f20195a9"
//	0xaa, 0x69, 0x4f, 0xb6, 0x10, 0x39, 0xbf, 0x2c,
//	0x7e, 0x2d, 0x74, 0x3d, 0xc1, 0xbb, 0x2e, 0x19,
//	0xa9, 0x70, 0x70, 0xa9, 0x70, 0xf2, 0xa9, 0xc1,
//	0xa9, 0x70, 0x01, 0x72, 0xf2, 0x01, 0x95, 0xa9, 
// 
//	// "2000000000000000000000000000000000000000000000000000000000000000"
//	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 
//	// "63e4e370970793d3ac543500ba51dc9d09636363636363d06363b76363b76363"
//	0x63, 0xe4, 0xe3, 0x70, 0x97, 0x07, 0x93, 0xd3,
//	0xac, 0x54, 0x35, 0x00, 0xba, 0x51, 0xdc, 0x9d,
//	0x09, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0xd0,
//	0x63, 0x63, 0xb7, 0x63, 0x63, 0xb7, 0x63, 0x63, 
// 
//	// "0000000000000000000000000000000000000000000000000000000000000000"
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
//};

	//4C6AC299 20C87915 C1FE48BC 7A6FFD69
	//36F4A901 F4C1017E 01A9BD74 C1BD7D01
	//40000000 00000000 00000000 00000000
	//00000000 00000000 00000000 00000000
	//2ECAFCB8 48E1976B F1F7C4E2 1236D516
	//CD636363 636363BA 63630963 63096363
	//00000000 00000000 00000000 00000000
	//00000000 00000000 00000000 00000000
meow_u8 Key[128] = { // Key for 32-bit message
	0x4C, 0x6A, 0xC2, 0x99, 0x20, 0xC8, 0x79, 0x15,
	0xC1, 0xFE, 0x48, 0xBC, 0x7A, 0x6F, 0xFD, 0x69,

	0x36, 0xF4, 0xA9, 0x01, 0xF4, 0xC1, 0x01, 0x7E,
	0x01, 0xA9, 0xBD, 0x74, 0xC1, 0xBD, 0x7D, 0x01,

	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	0x2E, 0xCA, 0xFC, 0xB8, 0x48, 0xE1, 0x97, 0x6B,
	0xF1, 0xF7, 0xC4, 0xE2, 0x12, 0x36, 0xD5, 0x16,

	0xCD, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0xBA,
	0x63, 0x63, 0x09, 0x63, 0x63, 0x09, 0x63, 0x63,

	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};



// Original print style
void PrintHash(meow_u128 Hash) {
	printf("    %08X-%08X-%08X-%08X\n",
		MeowU32From(Hash, 3),
		MeowU32From(Hash, 2),
		MeowU32From(Hash, 1),
		MeowU32From(Hash, 0));
}

static void PrintKey(meow_u128 Hash1, meow_u128 Hash2) {
	printf("\t%08X%08X%08X%08X-%08X%08X%08X%08X\n",
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
		MeowU8From(Hash2, 14), MeowU8From(Hash2, 15) );
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
		MeowU8From(Hash, 14), MeowU8From(Hash, 15) );
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
		MeowU8From(Hash, 14), MeowU8From(Hash, 15) );
}



int main() {

	// Get message
	int BufSize = MSG_LEN;
	char* Buffer = new char[BufSize + 1]; // +1 for null terminator
	memset(Buffer, 0, BufSize + 1); // +1 for null terminator
	memcpy(Buffer, MESSAGE, BufSize);

	cout << "Message: " << Buffer << endl;
	cout << "Message size: " << BufSize << endl;

	// Get Key
	//Invertibility(BufSize); // Key cannot be sent out
	meow_u8 Key_Gen[129];
	memset(Key_Gen, 0, 129);
	Invertibility(Key_Gen, BufSize); // Key can be sent out
	
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

	// NOTE(casey): Ask Meow for the hash
	//meow_u128 Hash = MeowHash(Key, BufSize, Buffer);
	meow_u128 Hash = MeowHash(Key_Gen, BufSize, Buffer);

	// NOTE(casey): Print the hash
	cout << "\n===================================================" << endl;
	cout << "Hash of the message above: " << endl;
	//PrintHash(Hash);
	PrintByte(Hash);
	cout << "===================================================" << endl;

	delete[] Buffer;

	return 0;
}
