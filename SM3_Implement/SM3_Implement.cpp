#include <iostream>
#include <string>
#include <cmath>
using namespace std;

string BinaryHex(string bin) {//用来将二进制转化为十六进制
	string hex = "";//用来存储生成的十六进制数
	int temp = 0;//每四位二进制数的十进制值
	while (bin.size() % 4 != 0)
	{
		bin = "0" + bin;//每四位二进制数就能够成为一个十六进制数，根据这个特点将二进制数长度转换为4的倍数，我们往高位添0直到长度为4的倍数即可
	}
	for (int i = 0; i < bin.size(); i += 4) 
	{
		temp = (bin[i] - '0') * 8 + (bin[i + 1] - '0') * 4 + (bin[i + 2] - '0') * 2 + (bin[i + 3] - '0') * 1;//判断每4位二进制数的十进制大小
		if (temp < 10) {
			hex += to_string(temp);//当得到的值小于10时，直接用0到9来代替
		}
		else {
			hex += 'A' + (temp - 10);//当得到的值大于10时，进行A到F的转换
		}
	}
	return hex;
}

string HexBinary(string hex) {//用来将十六进制转化为二进制
	string bin = "";//用来存储生成的二进制数
	string table[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	//十六进制每一位可能对应的所有二进制情况
	for (int i = 0; i < hex.size(); i++) 
	{
		if (hex[i] >= 'A' && hex[i] <= 'F') {
			bin += table[hex[i] - 'A' + 10];
		}
		else {
			bin += table[hex[i] - '0'];
		}
	}
	return bin;
}

int BinaryDec(string bin) {//用来将二进制转化为十进制
	int dec = 0;//用来存储生成的十进制数
	for (int i = 0; i < bin.size(); i++) 
	{
		dec += (bin[i] - '0') * pow(2, bin.size() - i - 1);
	}
	return dec;
}

string DecBinary(int dec) {//用来将十进制转化为二进制
	string bin = "";//用来存储生成的二进制数
	while (dec >= 1) 
	{
		bin = to_string(dec % 2) + bin;
		dec = dec / 2;
	}
	return bin;
}

int HexDec(string hex) {//用来将十六进制转化为十进制
	int dec = 0;//用来存储生成的十进制数
	for (int i = 0; i < hex.size(); i++) 
	{
		if (hex[i] >= 'A' && hex[i] <= 'F') {
			dec += (hex[i] - 'A' + 10) * pow(16, hex.size() - i - 1);
		}
		else {
			dec += (hex[i] - '0') * pow(16, hex.size() - i - 1);
		}
	}
	return dec;
}

string DecHex(int dec) {//用来将十进制转化为十六进制
	string hex = "";//用来存储生成的十六进制数
	int temp = 0;
	while (dec >= 1) 
	{
		temp = dec % 16;
		if (temp < 10 && temp >= 0) {
			hex = to_string(temp) + hex;
		}
		else {
			hex += ('A' + (temp - 10));
		}
		dec = dec / 16;
	}
	return hex;
}

string pad(string str) {//对数据进行填充 
	string a = "";
	for (int i = 0; i < str.size(); i++) //首先将输入值转换为16进制字符串
	{
		a += DecHex((int)str[i]);
	}
	cout << "输入字符串转换为ASCII码的结果为：" << endl;
	for (int i = 0; i < a.size(); i++) 
	{
		cout << a[i];
		if ((i + 1) % 8 == 0) {
			cout << "  ";
		}
		if ((i + 1) % 64 == 0 || (i + 1) == a.size()) {
			cout << endl;
		}
	}
	cout << endl;
	int a_length = a.size() * 4;//记录的长度为2进制下的长度
	a += "8";//在获得的数据后面添1，相当于是在十六进制下加8
	while (a.size() % 128 != 112) 
	{
		a += "0";//进行“0”数据填充
	}
	string a_len = DecHex(a_length);//用于记录数据长度的字符串
	while (a_len.size() != 16) 
	{
		a_len = "0" + a_len;
	}
	a += a_len;
	return a;
}

string LeftShift(string str, int n) {//实现循环左移n位的功能
	string a = HexBinary(str);
	a = a.substr(n) + a.substr(0, n);
	return BinaryHex(a);
}

string XOR(string a1, string a2) {//实现异或操作
	string b1 = HexBinary(a1);
	string b2 = HexBinary(a2);
	string b = "";
	for (int i = 0; i < b1.size(); i++) 
	{
		if (b1[i] == b2[i]) {
			b += "0";
		}
		else {
			b += "1";
		}
	}
	return BinaryHex(b);
}

string AND(string a1, string a2) {//实现与操作
	string b1 = HexBinary(a1);
	string b2 = HexBinary(a2);
	string b = "";
	for (int i = 0; i < b1.size(); i++) {
		if (b1[i] == '1' && b2[i] == '1') {
			b += "1";
		}
		else {
			b += "0";
		}
	}
	return BinaryHex(b);
}

string OR(string a1, string a2) {//实现或操作
	string b1 = HexBinary(a1);
	string b2 = HexBinary(a2);
	string b = "";
	for (int i = 0; i < b1.size(); i++) 
	{
		if (b1[i] == '0' && b2[i] == '0') {
			b += "0";
		}
		else {
			b += "1";
		}
	}
	return BinaryHex(b);
}

string NOT(string a) {//实现非操作
	string b1 = HexBinary(a);
	string b = "";
	for (int i = 0; i < b1.size(); i++) 
	{
		if (b1[i] == '0') {
			b += "1";
		}
		else {
			b += "0";
		}
	}
	return BinaryHex(b);
}

char bitXor(char a1, char a2) {//实现单比特位的异或操作
	return a1 == a2 ? '0' : '1';
}

char bitAnd(char a1, char a2) {//实现单比特的与操作
	return (a1 == '1' && a2 == '1') ? '1' : '0';
}

string modAdd(string a1, string a2) {//实现模加运算
	string b1 = HexBinary(a1);
	string b2 = HexBinary(a2);
	char temp = '0';
	string b = "";
	for (int i = b1.size() - 1; i >= 0; i--) 
	{
		b = bitXor(bitXor(b1[i], b2[i]), temp) + b;
		if (bitAnd(b1[i], b2[i]) == '1') {
			temp = '1';
		}
		else {
			if (bitXor(b1[i], b2[i]) == '1') {
				temp = bitAnd('1', temp);
			}
			else {
				temp = '0';
			}
		}
	}
	return BinaryHex(b);
}

string P1(string a) {//实现置换功能P1（X）
	return XOR(XOR(a, LeftShift(a, 15)), LeftShift(a, 23));
}

string P0(string a) {//实现置换功能P0（X）
	return XOR(XOR(a, LeftShift(a, 9)), LeftShift(a, 17));
}

string T(int i) {//常量初始化T
	if (0 <= i && i <= 15) {
		return "79CC4519";
	}
	else {
		return "7A879D8A";
	}
}

string FF(string a1, string a2, string a3, int i) {//实现布尔函数FF功能
	if (0 <= i && i <= 15) {
		return XOR(XOR(a1, a2), a3);
	}
	else {
		return OR(OR(AND(a1, a2), AND(a1, a3)), AND(a2, a3));
	}
}

string GG(string a1, string a2, string a3, int i) {//实现布尔函数GG功能
	if (0 <= i && i <= 15) {
		return XOR(XOR(a1, a2), a3);
	}
	else {
		return OR(AND(a1, a2), AND(NOT(a1), a3));
	}
}
string ext(string a) {//消息扩展函数
	string b = a;//字符串类型存储前68位存储扩展字W值
	for (int i = 16; i < 68; i++) {//根据公式生成第17位到第68位的W值
		b += XOR(XOR(P1(XOR(XOR(b.substr((i - 16) * 8, 8), b.substr((i - 9) * 8, 8)), LeftShift(b.substr((i - 3) * 8, 8), 15))), LeftShift(b.substr((i - 13) * 8, 8), 7)), b.substr((i - 6) * 8, 8));
	}
	cout << "扩展后的消息如下：" << endl;
	cout << "其中W0,W1,……,W67的消息为：" << endl;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cout << b.substr(i * 64 + j * 8, 8) << "  ";
		}
		cout << endl;
	}
	cout << b.substr(512, 8) << "  " << b.substr(520, 8) << "  " << b.substr(528, 8) << "  " << b.substr(536, 8) << endl;
	cout << endl;
	for (int i = 0; i < 64; i++) {//根据公式生成64位W'值
		b += XOR(b.substr(i * 8, 8), b.substr((i + 4) * 8, 8));
	}
	cout << "W0',W1',……,W63'的消息为：" << endl;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cout << b.substr(544 + i * 64 + j * 8, 8) << "  ";
		}
		cout << endl;
	}
	cout << endl;
	return b;
}

string cmp(string str1, string str2) {//消息压缩函数
	string IV = str2;
	string A = IV.substr(0, 8), B = IV.substr(8, 8), C = IV.substr(16, 8), D = IV.substr(24, 8), E = IV.substr(32, 8), F = IV.substr(40, 8), G = IV.substr(48, 8), H = IV.substr(56, 8);
	string SS1 = "", SS2 = "", TT1 = "", TT2 = "";
	cout << "迭代压缩中间值为: " << endl;
	cout << "    A         B         C         D         E         F        G         H " << endl;
	cout << A << "  " << B << "  " << C << "  " << D << "  " << E << "  " << F << "  " << G << "  " << H << endl;
	for (int j = 0; j < 64; j++) {
		SS1 = LeftShift(modAdd(modAdd(LeftShift(A, 12), E), LeftShift(T(j), (j % 32))), 7);
		SS2 = XOR(SS1, LeftShift(A, 12));
		TT1 = modAdd(modAdd(modAdd(FF(A, B, C, j), D), SS2), str1.substr((j + 68) * 8, 8));
		TT2 = modAdd(modAdd(modAdd(GG(E, F, G, j), H), SS1), str1.substr(j * 8, 8));
		D = C;
		C = LeftShift(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = LeftShift(F, 19);
		F = E;
		E = P0(TT2);
		cout << A << "  " << B << "  " << C << "  " << D << "  " << E << "  " << F << "  " << G << "  " << H << endl;
	}
	string res = (A + B + C + D + E + F + G + H);
	cout << endl;
	return res;
}

string ite(string a) {//迭代压缩函数实现
	int num = a.size() / 128;
	cout << "消息经过填充之后共有 " + to_string(num) + " 个消息分组。" << endl;
	cout << endl;
	string V = "7380166F4914B2B9172442D7DA8A0600A96F30BC163138AAE38DEE4DB0FB0E4E";
	string B = "", extensionB = "", compressB = "";
	for (int i = 0; i < num; i++) {
		cout << "第 " << to_string(i + 1) << " 个消息分组：" << endl;
		cout << endl;
		B = a.substr(i * 128, 128);
		extensionB = ext(B);
		compressB = cmp(extensionB, V);
		V = XOR(V, compressB);
	}
	return V;
}

int main() {//主函数
	string str[2];
	str[0] = "abcdefghikjlmnopqrstuvwxyz";//可根据需要进行修改
	str[1] = "abcdabcdabcdabcdabcdabcd";//可根据需要进行修改
	for (int num = 0; num < 2; num++) {
		cout << "示例 " + to_string(num + 1) + " （可根据需要在主函数中修改）：输入消息为字符串: " + str[num] << endl;
		cout << endl;
		string paddingValue = pad(str[num]);
		cout << "填充后的消息为：" << endl;
		for (int i = 0; i < paddingValue.size() / 64; i++) {
			for (int j = 0; j < 8; j++) {
				cout << paddingValue.substr(i * 64 + j * 8, 8) << "  ";
			}
			cout << endl;
		}
		cout << endl;
		string result = ite(paddingValue);
		cout << "杂凑值为：" << endl;
		for (int i = 0; i < 8; i++) {
			cout << result.substr(i * 8, 8) << "  ";
		}
		cout << endl;
		cout << endl;
	}
}