// https://github.com/cmuratori/meow_hash
// https://peter.website/meow-hash-cryptanalysis

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
//#include <bitset>

#include "meow_hash_x64_aesni.h"

using namespace std;

//const char* MESSAGE = "abcdefghabcdefghaijklmnhaijklmnh";
//const char* MESSAGE = "abcdefghabcdefghabcdefghabcdefgh";
//const char* MESSAGE = "Ab Cdefghi 202000461234";
const char* MESSAGE = "abcdefghabcdefgh" \
"abcdefghabcdefgh" \
"abcdefghabcdefgh" \
"abcdefghabcdefgh";
const int MSG_LEN = strlen(MESSAGE);

//http://tools.bugscaner.com/text/hex2bytes.html
	//symmetrize32 = hex_to_bytes(
	//    "aa694fb61039bf2c7e2d743dc1bb2e19a97070a970f2a9c1a9700172f20195a9"
	//    "2000000000000000000000000000000000000000000000000000000000000000"
	//    "63e4e370970793d3ac543500ba51dc9d09636363636363d06363b76363b76363"
	//    "0000000000000000000000000000000000000000000000000000000000000000"
	//)
//meow_u8 Key[128] = { // Key for 32-bit message
//	0xaa, 0x69, 0x4f, 0xb6, 0x10, 0x39, 0xbf, 0x2c,
//	0x7e, 0x2d, 0x74, 0x3d, 0xc1, 0xbb, 0x2e, 0x19,
//	0xa9, 0x70, 0x70, 0xa9, 0x70, 0xf2, 0xa9, 0xc1,
//	0xa9, 0x70, 0x01, 0x72, 0xf2, 0x01, 0x95, 0xa9, // "aa694fb61039bf2c7e2d743dc1bb2e19a97070a970f2a9c1a9700172f20195a9"
//	
//	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // "2000000000000000000000000000000000000000000000000000000000000000"
//	
//	0x63, 0xe4, 0xe3, 0x70, 0x97, 0x07, 0x93, 0xd3,
//	0xac, 0x54, 0x35, 0x00, 0xba, 0x51, 0xdc, 0x9d,
//	0x09, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0xd0,
//	0x63, 0x63, 0xb7, 0x63, 0x63, 0xb7, 0x63, 0x63, // "63e4e370970793d3ac543500ba51dc9d09636363636363d06363b76363b76363"
//	
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // "0000000000000000000000000000000000000000000000000000000000000000"
//};

	//Invertibility(BufSize, Buffer);
	//	3B1FDE040CB93145F03E96E80A030CB9010114EE0114EE018FB5C1C10DA9A95F
	//	0000000000000000000000000000004000000000000000000000000000000000
	//	86CE8D974BAE8E4D69CA7B2330DC568B636363636363636363636363DD0909B7
	//	0000000000000000000000000000000000000000000000000000000000000000
//meow_u8 Key[128] = { // Key for 64-bit message
//	// 3B1FDE040CB93145F03E96E80A030CB9010114EE0114EE018FB5C1C10DA9A95F
//	0x45, 0x31, 0xB9, 0x0C, 0x04, 0xDE, 0x1F, 0x3B,
//	0xB9, 0x0C, 0x03, 0x0A, 0xE8, 0x96, 0x3E, 0xF0, 
//	0x01, 0xEE, 0x14, 0x01, 0xEE, 0x14, 0x01, 0x01, 
//	0x5F, 0xA9, 0xA9, 0x0D, 0xC1, 0xC1, 0xB5, 0x8F, 
//	
//	// 0000000000000000000000000000004000000000000000000000000000000000
//	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
//	
//	// 86CE8D974BAE8E4D69CA7B2330DC568B636363636363636363636363DD0909B7
//	0x4D, 0x8E, 0xAE, 0x4B, 0x97, 0x8D, 0xCE, 0x86,
//	0x8B, 0x56, 0xDC, 0x30, 0x23, 0x7B, 0xCA, 0x69, 
//	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 
//	0xB7, 0x09, 0x09, 0xDD, 0x63, 0x63, 0x63, 0x63,
//
//	// 0000000000000000000000000000000000000000000000000000000000000000
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
//};

	//AD01BAE19EE69957B5FF3EAD674081D3DF21C21356A561AC54A6CEFCABAEEEF5
	//0083C9DE8B7F67783FE6B28A2B84CFBB92CE4306005D5C86F0796CFE55FC57AE
	//AEA3950D44F77F4D22F9F7C3329AC3BC3C9887219F13C208FFED9734645767B9
	//4BFEA61FFF587CB260E9E00CDBFADD2991FBD32B500C4B203E73C66FA89A2F8C
//meow_u8 Key[128] = { // Key for 64-bit message
//	0xAD, 0x01, 0xBA, 0xE1, 0x9E, 0xE6, 0x99, 0x57, 
//	0xB5, 0xFF, 0x3E, 0xAD, 0x67, 0x40, 0x81, 0xD3, 
//	0xDF, 0x21, 0xC2, 0x13, 0x56, 0xA5, 0x61, 0xAC, 
//	0x54, 0xA6, 0xCE, 0xFC, 0xAB, 0xAE, 0xEE, 0xF5, // AD01BAE19EE69957B5FF3EAD674081D3DF21C21356A561AC54A6CEFCABAEEEF5
//
//	0x00, 0x83, 0xC9, 0xDE, 0x8B, 0x7F, 0x67, 0x78, 
//	0x3F, 0xE6, 0xB2, 0x8A, 0x2B, 0x84, 0xCF, 0xBB, 
//	0x92, 0xCE, 0x43, 0x06, 0x00, 0x5D, 0x5C, 0x86, 
//	0xF0, 0x79, 0x6C, 0xFE, 0x55, 0xFC, 0x57, 0xAE, // 0083C9DE8B7F67783FE6B28A2B84CFBB92CE4306005D5C86F0796CFE55FC57AE
//
//	0xAE, 0xA3, 0x95, 0x0D, 0x44, 0xF7, 0x7F, 0x4D, 
//	0x22, 0xF9, 0xF7, 0xC3, 0x32, 0x9A, 0xC3, 0xBC, 
//	0x3C, 0x98, 0x87, 0x21, 0x9F, 0x13, 0xC2, 0x08, 
//	0xFF, 0xED, 0x97, 0x34, 0x64, 0x57, 0x67, 0xB9, // AEA3950D44F77F4D22F9F7C3329AC3BC3C9887219F13C208FFED9734645767B9
//
//	0x4B, 0xFE, 0xA6, 0x1F, 0xFF, 0x58, 0x7C, 0xB2, 
//	0x60, 0xE9, 0xE0, 0x0C, 0xDB, 0xFA, 0xDD, 0x29, 
//	0x91, 0xFB, 0xD3, 0x2B, 0x50, 0x0C, 0x4B, 0x20, 
//	0x3E, 0x73, 0xC6, 0x6F, 0xA8, 0x9A, 0x2F, 0x8C // 4BFEA61FFF587CB260E9E00CDBFADD2991FBD32B500C4B203E73C66FA89A2F8C
//};

	// 1 Xor's (latter)
	//D1112B1D-E6DBD735-EDD65B24-C01EE2A6
    //6262778D-62778D62-ECD6A2A2-88616131
    //00000000-00000000-00000000-00000040
    //00000000-00000000-00000000-00000000
    //D3C24441-1AA43208-C6A9035F-5A887CB5
    //63636363-63636363-63636363-DD0909F7
    //00000000-00000000-00000000-00000000
    //00000000-00000000-00000000-00000000
meow_u8 Key[128] = { // Key for 64-bit message
	//D1112B1D-E6DBD735-EDD65B24-C01EE2A6
	0xA6, 0xE2, 0x1E, 0xC0, 0x24, 0x5B, 0xD6, 0xED,
	0x35, 0xD7, 0xDB, 0xE6, 0x1D, 0x2B, 0x11, 0xD1,	

	//6262778D-62778D62-ECD6A2A2-88616131
	0x31, 0x61, 0x61, 0x88, 0xA2, 0xA2, 0xD6, 0xEC,
	0x62, 0x8D, 0x77, 0x62, 0x8D, 0x77, 0x62, 0x62,

	//00000000-00000000-00000000-00000040
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	//00000000-00000000-00000000-00000000
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	//D3C24441-1AA43208-C6A9035F-5A887CB5
	0xB5, 0x7C, 0x88, 0x5A, 0x5F, 0x03, 0xA9, 0xC6,
	0x08, 0x32, 0xA4, 0x1A, 0x41, 0x44, 0xC2, 0xD3,

	//63636363-63636363-63636363-DD0909F7
	0xF7, 0x09, 0x09, 0xDD, 0x63, 0x63, 0x63, 0x63, 
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
	
	//00000000-00000000-00000000-00000000
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	//00000000-00000000-00000000-00000000
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
	
	//2 Xor's
	//3B1FDE04-0CB93145-F03E96E8-0A030CB9
	//010114EE-0114EE01-8FB5C1C1-0DA9A95F
	//00000000-00000000-00000000-00000040
	//00000000-00000000-00000000-00000000
	//86CE8D97-4BAE8E4D-69CA7B23-30DC568B
	//63636363-63636363-63636363-DD0909B7
	//00000000-00000000-00000000-00000000
	//00000000-00000000-00000000-00000000
//meow_u8 Key[128] = { // Key for 64-bit message
//	//3B1FDE04-0CB93145-F03E96E8-0A030CB9
//	0xB9, 0x0C, 0x03, 0x0A, 0xE8, 0x96, 0x3E, 0xF0, 
//	0x45, 0x31, 0xB9, 0x0C, 0x04, 0xDE, 0x1F, 0x3B,
//
//	//010114EE-0114EE01-8FB5C1C1-0DA9A95F
//	0x5F, 0xA9, 0xA9, 0x0D, 0xC1, 0xC1, 0xB5, 0x8F, 
//	0x01, 0xEE, 0x14, 0x01, 0xEE, 0x14, 0x01, 0x01,
//
//	//00000000-00000000-00000000-00000040
//	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	
//	//00000000-00000000-00000000-00000000
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//
//	//86CE8D97-4BAE8E4D-69CA7B23-30DC568B
//	0x8B, 0x56, 0xDC, 0x30, 0x23, 0x7B, 0xCA, 0x69,
//	0x4D, 0x8E, 0xAE, 0x4B, 0x97, 0x8D, 0xCE, 0x86, 
//	
//	//63636363-63636363-63636363-DD0909B7
//	0xB7, 0x09, 0x09, 0xDD, 0x63, 0x63, 0x63, 0x63, 
//	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
//
//	//00000000-00000000-00000000-00000000
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	
//	//00000000-00000000-00000000-00000000
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//};

//meow_u8 Key[128] = { // Key for 32-bit message
//	// 0000000000000000000000000000002000000000000000000000000000000020
//	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
//
//	// 0000000000000000000000000000002000000000000000000000000000000000
//	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
//
//	// 6363636363636363636363636363634363636363636363636363636363636343
//	0x43, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 
//	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 
//	0x43, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 
//	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 
//
//	// 0000000000000000000000000000000000000000000000000000000000000000
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
//};


// Original print style
void PrintHash(meow_u128 Hash) {
	printf("    %08X-%08X-%08X-%08X\n",
		MeowU32From(Hash, 3),
		MeowU32From(Hash, 2),
		MeowU32From(Hash, 1),
		MeowU32From(Hash, 0));
}

// The same print style as http://tools.bugscaner.com/text/hex2bytes.html
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


int main() {

	// Get message
	int BufSize = MSG_LEN;
	char* Buffer = new char[BufSize + 1]; // +1 for null terminator
	memset(Buffer, 0, BufSize + 1); // +1 for null terminator
	memcpy(Buffer, MESSAGE, BufSize);

	cout << "Message: " << Buffer << endl;
	cout << "Message size: " << BufSize << endl;

	// Get Key
	Invertibility(BufSize, Buffer);

	// NOTE(casey): Ask Meow for the hash
	meow_u128 Hash = MeowHash(Key, BufSize, Buffer);
	//cout << endl;
	//for (int i = 0; i < 256; i++) {
	//	// 80 ~ 95: 80.87.90.93
	//	Key[84] = i;
	//	printf("%02X", i);
	//	meow_u128 Hash = MeowHash(Key, BufSize, Buffer);
	//}

	// NOTE(casey): Print the hash
	cout << "==========================================================" << endl;
	cout << "Hash of the message above: " << endl;
	PrintHash(Hash);
	cout << "==========================================================" << endl;

	delete[] Buffer;

	return 0;
}
