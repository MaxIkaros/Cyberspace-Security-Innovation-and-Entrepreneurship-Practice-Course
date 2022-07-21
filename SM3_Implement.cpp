#include <iostream>
#include <string>
#include <cmath>
using namespace std;

string BinaryHex(string bin) {//������������ת��Ϊʮ������
	string hex = "";
	int temp = 0;
	while (bin.size() % 4 != 0)
	{
		bin = "0" + bin;//ÿ��λ�����������ܹ���Ϊһ��ʮ������������������ص㽫������������ת��Ϊ4�ı�������������λ��0ֱ������Ϊ4�ı�������
	}
	for (int i = 0; i < bin.size(); i += 4) 
	{
		temp = (bin[i] - '0') * 8 + (bin[i + 1] - '0') * 4 + (bin[i + 2] - '0') * 2 + (bin[i + 3] - '0') * 1;//�ж�ÿ4λ����������ʮ���ƴ�С
		if (temp < 10) {
			hex += to_string(temp);//���õ���ֵС��10ʱ��ֱ����0��9������
		}
		else {
			hex += 'A' + (temp - 10);//���õ���ֵ����10ʱ������A��F��ת��
		}
	}
	return hex;
}

string HexBinary(string hex) {//������ʮ������ת��Ϊ������
	string bin = "";
	string table[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	//ʮ������ÿһλ���ܶ�Ӧ�����ж��������
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

int BinaryDec(string bin) {//������������ת��Ϊʮ����
	int dec = 0;
	for (int i = 0; i < bin.size(); i++) 
	{
		dec += (bin[i] - '0') * pow(2, bin.size() - i - 1);
	}
	return dec;
}

string DecBinary(int dec) {//������ʮ����ת��Ϊ������
	string bin = "";
	while (dec >= 1) 
	{
		bin = to_string(dec % 2) + bin;
		dec = dec / 2;
	}
	return bin;
}

int HexDec(string hex) {//������ʮ������ת��Ϊʮ����
	int dec = 0;
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

string DecHex(int dec) {//������ʮ����ת��Ϊʮ������
	string hex = "";
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

string pad(string str) {//�����ݽ������ 
	string a = "";
	for (int i = 0; i < str.size(); i++) //���Ƚ�����ֵת��Ϊ16�����ַ���
	{
		a += DecHex((int)str[i]);
	}
	cout << "�����ַ���ת��ΪASCII��Ľ��Ϊ��" << endl;
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
	int a_length = a.size() * 4;//��¼�ĳ���Ϊ2�����µĳ���
	a += "8";//�ڻ�õ����ݺ�����1���൱������ʮ�������¼�8
	while (a.size() % 128 != 112) 
	{
		a += "0";//���С�0���������
	}
	string a_len = DecHex(a_length);//���ڼ�¼���ݳ��ȵ��ַ���
	while (a_len.size() != 16) 
	{
		a_len = "0" + a_len;
	}
	a += a_len;
	return a;
}

string LeftShift(string str, int n) {//ʵ��ѭ������nλ�Ĺ���
	string a = HexBinary(str);
	a = a.substr(n) + a.substr(0, n);
	return BinaryHex(a);
}

string XOR(string a1, string a2) {//ʵ��������
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

string AND(string a1, string a2) {//ʵ�������
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

string OR(string a1, string a2) {//ʵ�ֻ����
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

string NOT(string a) {//ʵ�ַǲ���
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

char bitXor(char a1, char a2) {//ʵ�ֵ�����λ��������
	return a1 == a2 ? '0' : '1';
}

char bitAnd(char a1, char a2) {//ʵ�ֵ����ص������
	return (a1 == '1' && a2 == '1') ? '1' : '0';
}

string modAdd(string a1, string a2) {//ʵ��ģ������
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

string P1(string a) {//ʵ���û�����P1��X��
	return XOR(XOR(a, LeftShift(a, 15)), LeftShift(a, 23));
}

string P0(string a) {//ʵ���û�����P0��X��
	return XOR(XOR(a, LeftShift(a, 9)), LeftShift(a, 17));
}

string T(int i) {//������ʼ��T
	if (0 <= i && i <= 15) {
		return "79CC4519";
	}
	else {
		return "7A879D8A";
	}
}

string FF(string a1, string a2, string a3, int i) {//ʵ�ֲ�������FF����
	if (0 <= i && i <= 15) {
		return XOR(XOR(a1, a2), a3);
	}
	else {
		return OR(OR(AND(a1, a2), AND(a1, a3)), AND(a2, a3));
	}
}

string GG(string a1, string a2, string a3, int i) {//ʵ�ֲ�������GG����
	if (0 <= i && i <= 15) {
		return XOR(XOR(a1, a2), a3);
	}
	else {
		return OR(AND(a1, a2), AND(NOT(a1), a3));
	}
}
string ext(string a) {//��Ϣ��չ����
	string b = a;//�ַ������ʹ洢ǰ68λ�洢��չ��Wֵ
	for (int i = 16; i < 68; i++) {//���ݹ�ʽ���ɵ�17λ����68λ��Wֵ
		b += XOR(XOR(P1(XOR(XOR(b.substr((i - 16) * 8, 8), b.substr((i - 9) * 8, 8)), LeftShift(b.substr((i - 3) * 8, 8), 15))), LeftShift(b.substr((i - 13) * 8, 8), 7)), b.substr((i - 6) * 8, 8));
	}
	cout << "��չ�����Ϣ���£�" << endl;
	cout << "����W0,W1,����,W67����ϢΪ��" << endl;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cout << b.substr(i * 64 + j * 8, 8) << "  ";
		}
		cout << endl;
	}
	cout << b.substr(512, 8) << "  " << b.substr(520, 8) << "  " << b.substr(528, 8) << "  " << b.substr(536, 8) << endl;
	cout << endl;
	for (int i = 0; i < 64; i++) {//���ݹ�ʽ����64λW'ֵ
		b += XOR(b.substr(i * 8, 8), b.substr((i + 4) * 8, 8));
	}
	cout << "W0',W1',����,W63'����ϢΪ��" << endl;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cout << b.substr(544 + i * 64 + j * 8, 8) << "  ";
		}
		cout << endl;
	}
	cout << endl;
	return b;
}

string cmp(string str1, string str2) {//��Ϣѹ������
	string IV = str2;
	string A = IV.substr(0, 8), B = IV.substr(8, 8), C = IV.substr(16, 8), D = IV.substr(24, 8), E = IV.substr(32, 8), F = IV.substr(40, 8), G = IV.substr(48, 8), H = IV.substr(56, 8);
	string SS1 = "", SS2 = "", TT1 = "", TT2 = "";
	cout << "����ѹ���м�ֵΪ: " << endl;
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

string ite(string a) {//����ѹ������ʵ��
	int num = a.size() / 128;
	cout << "��Ϣ�������֮���� " + to_string(num) + " ����Ϣ���顣" << endl;
	cout << endl;
	string V = "7380166F4914B2B9172442D7DA8A0600A96F30BC163138AAE38DEE4DB0FB0E4E";
	string B = "", extensionB = "", compressB = "";
	for (int i = 0; i < num; i++) {
		cout << "�� " << to_string(i + 1) << " ����Ϣ���飺" << endl;
		cout << endl;
		B = a.substr(i * 128, 128);
		extensionB = ext(B);
		compressB = cmp(extensionB, V);
		V = XOR(V, compressB);
	}
	return V;
}

int main() {//������
	string str[2];
	str[0] = "abcdefghikjlmnopqrstuvwxyz";//�ɸ�����Ҫ�����޸�
	str[1] = "abcdabcdabcdabcdabcdabcd";//�ɸ�����Ҫ�����޸�
	for (int num = 0; num < 2; num++) {
		cout << "ʾ�� " + to_string(num + 1) + " ���ɸ�����Ҫ�����������޸ģ���������ϢΪ�ַ���: " + str[num] << endl;
		cout << endl;
		string paddingValue = pad(str[num]);
		cout << "�������ϢΪ��" << endl;
		for (int i = 0; i < paddingValue.size() / 64; i++) {
			for (int j = 0; j < 8; j++) {
				cout << paddingValue.substr(i * 64 + j * 8, 8) << "  ";
			}
			cout << endl;
		}
		cout << endl;
		string result = ite(paddingValue);
		cout << "�Ӵ�ֵΪ��" << endl;
		for (int i = 0; i < 8; i++) {
			cout << result.substr(i * 8, 8) << "  ";
		}
		cout << endl;
		cout << endl;
	}
}