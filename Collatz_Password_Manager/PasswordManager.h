#pragma once
#include<vector>
#include<string>

using namespace std;
class PasswordManager
{
public:
	PasswordManager();
	~PasswordManager();
	static int collatz(int value);
	static string encrypt(wstring password);
	static wstring decrypt(string password);
	static string generate_password();
	static wstring mode1(int length);
	static wstring mode2(int length);

};