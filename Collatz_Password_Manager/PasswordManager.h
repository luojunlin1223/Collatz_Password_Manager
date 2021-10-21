#pragma once
#include<vector>
#include<string>

using namespace std;
class PasswordManager
{
public:
	PasswordManager();
	~PasswordManager();
	string password;
	wstring origin;
	static int collatz(int value);
	static string encrypt(wstring password,int _offset);
	void generate_password();
	static wstring mode1(int length);
	static wstring mode2(int length);
};