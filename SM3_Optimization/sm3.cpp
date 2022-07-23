#include<iostream>
#include <string.h>
#include <stdio.h>
#include"sm3_SIMD.h"//change header file name to use different optimization

int main()
{
	std::string input_str = "sdusdusdusdu";
	int dlen = input_str.size();
	unsigned char* message = (unsigned char*)input_str.c_str();
	unsigned char res[32];
	sm3(message, dlen, res);
	for (int i = 0; i < 32; i++)
		printf("%02x", res[i]);
	return 0;
}

