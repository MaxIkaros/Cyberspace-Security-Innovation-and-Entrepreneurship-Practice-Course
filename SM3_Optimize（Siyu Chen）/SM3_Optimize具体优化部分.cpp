#include <iostream>
#include <string>
#include <cmath>
#include<windows.h>
using namespace std;

string cmp(string str1, string str2) {//��Ϣѹ������
	string IV = str2;
	string A = IV.substr(0, 8), B = IV.substr(8, 8), C = IV.substr(16, 8), D = IV.substr(24, 8), E = IV.substr(32, 8), F = IV.substr(40, 8), G = IV.substr(48, 8), H = IV.substr(56, 8);
	string Res = "",SS1 = "", SS2 = "", TT1 = "", TT2 = "";
	cout << "����ѹ���м�ֵΪ: " << endl;
	cout << "    A         B         C         D         E         F        G         H " << endl;
	cout << A << "  " << B << "  " << C << "  " << D << "  " << E << "  " << F << "  " << G << "  " << H << endl;
	for (int j = 0; j < 64; j++) {
		Res = LeftShift(A, 12);//������ʱ����Res�������洢LeftShift(A, 12)����A����12λ��ֵ�������ں������룬���г������
		SS1 = LeftShift(modAdd(modAdd(Res, E), LeftShift(T(j), (j % 32))), 7);
		SS2 = XOR(SS1, Res);
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

int main() {//������
	string str[2];
	str[0] = "abcdefghikjlmnopqrstuvwxyz";//�ɸ�����Ҫ�����޸�
	str[1] = "abcdabcdabcdabcdabcdabcd";//�ɸ�����Ҫ�����޸�
	DWORD starttime = GetTickCount();
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
		DWORD endtime = GetTickCount();
		cout << endl;
		cout << "�����������ʱ��Ϊ��" << (endtime - starttime) << "ms" << endl;
		system("pause");
		cout << endl;
	}
}
