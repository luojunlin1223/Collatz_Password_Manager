#include "PasswordManager.h"

PasswordManager::PasswordManager(){
}
PasswordManager::~PasswordManager() {}
int PasswordManager::collatz(int value) {
	int temp = value;
	int step = 0;
	while (temp != 1) {
		if (temp % 2 == 0)
			temp = temp / 2;
		else
			temp = 3 * temp + 1;
		step++;
	}
	return step;
}
string PasswordManager::encrypt(wstring password) {
	int offset = 0;
	string encrypted;
	for (auto temp = password.begin(); temp != password.end(); temp++) {
		offset = collatz(((int)((wchar_t)(*temp)) + offset));
		encrypted+= to_string(offset);
	}
	return encrypted;
}
wstring PasswordManager::decrypt(string password) { 

	return  L""; 
}
string PasswordManager::generate_password() {
	string password;
	for (int i = 1; i <10000 ; i++)
	{
		password += encrypt(mode1((i - 1) / 100 + 1)) + '\n';
	}
	for (int i = 1; i < 10000; i++)
	{

		password += encrypt(mode2((i - 1) / 100 + 1)) + '\n';
	}
	
	return password;
}
wstring PasswordManager::mode1(int length) {
	wstring password;
	int count = 10;
	for (size_t i = 0; i < length; i++)
	{
		int ascii = rand() % 256;
		if (iswprint(ascii)) {
			if ('a' <= ascii && ascii <= 'z') {
				if (count > 0) {
					count--;
					password.push_back(wchar_t(ascii));
				}
				else
					i--;
			}
			else {
				password.push_back(wchar_t(ascii));
			}
		}
		else
			i--;
	}
	return password;
}
wstring PasswordManager::mode2(int length) {
	wstring temp;
	wstring password;
	for (size_t i = 0; i < length; i++)
	{
		int ascii = rand() % 256;
		wchar_t ch = ascii;
		if (iswprint(ascii)) {
			string::size_type pos;
			pos = temp.find(ch);
			if (pos != temp.npos)
				i--;
			else {
				temp.push_back(ch);
				password.push_back(ch);
			}
		}
		else
			i--;
	}
	return password;
}