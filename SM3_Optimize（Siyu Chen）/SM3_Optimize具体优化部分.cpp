#include <iostream>
#include <string>
#include <cmath>
#include<windows.h>
using namespace std;

string cmp(string str1, string str2) {//消息压缩函数
	string IV = str2;
	string A = IV.substr(0, 8), B = IV.substr(8, 8), C = IV.substr(16, 8), D = IV.substr(24, 8), E = IV.substr(32, 8), F = IV.substr(40, 8), G = IV.substr(48, 8), H = IV.substr(56, 8);
	string Res = "",SS1 = "", SS2 = "", TT1 = "", TT2 = "";
	cout << "迭代压缩中间值为: " << endl;
	cout << "    A         B         C         D         E         F        G         H " << endl;
	cout << A << "  " << B << "  " << C << "  " << D << "  " << E << "  " << F << "  " << G << "  " << H << endl;
	for (int j = 0; j < 64; j++) {
		Res = LeftShift(A, 12);//创建临时变量Res，用来存储LeftShift(A, 12)，即A左移12位的值，并用于后续带入，进行程序加速
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

int main() {//主函数
	string str[2];
	str[0] = "abcdefghikjlmnopqrstuvwxyz";//可根据需要进行修改
	str[1] = "abcdabcdabcdabcdabcdabcd";//可根据需要进行修改
	DWORD starttime = GetTickCount();
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
		DWORD endtime = GetTickCount();
		cout << endl;
		cout << "这个程序运行时间为：" << (endtime - starttime) << "ms" << endl;
		system("pause");
		cout << endl;
	}
}
