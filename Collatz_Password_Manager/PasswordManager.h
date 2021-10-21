#pragma once
#include<vector>
#include<string>

using namespace std;
class PasswordManager
{
public:
	PasswordManager();
	~PasswordManager();
	vector<int> path;
	vector<int> result;
	static int collatz(int value);
	static string encrypt(wstring password,int _offset);
	static string generate_password();
	static wstring mode1(int length);
	static wstring mode2(int length);
	static void backtracking(int n,int k,int startindex);
};