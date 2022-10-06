#include <iostream>
#include <string>
#include "BigNum.h"

using namespace std;

int main()
{
	string str = "1";
	string str1 = "0";
	string str2 = "1";
	
	short a = -10000;
	int b = -20000;
	int64_t c = -30000;


	BigNum num(str);

	cout << "str == str1" << endl;
	if (str == str1)
		cout << true << endl;
	else
		cout << endl;
	cout << "str != str1" << endl;
	if (str != str1)
		cout << false << endl;
	else
		cout << endl;
	cout << "str == str2" << endl;
	if (str == str2)
		cout << true << endl;
	else
		cout << endl;
	cout << "str != str2" << endl;
	if (str != str2)
		cout << false << endl;
	else
		cout << endl;
	cout << "³¡" << endl;

	cout << "string + short" << endl;
	cout << num + a << endl;
	cout << "string + int" << endl;
	cout << num + b << endl;
	cout << "string + int64_t" << endl;
	cout << num + c << endl << endl;

	cout << "string * short" << endl;
	cout << num * a << endl;
	cout << "string * int" << endl;
	cout << num * b << endl;
	cout << "string * int64_t" << endl;
	cout << num * c << endl << endl;
}