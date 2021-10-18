#include "PasswordManager.h"
#include <unordered_map>
#include <iostream>
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
	unordered_map<int, list<int>> map;
	wstring fin_password;
	for (int i = 1; i < 256; i++)
	{
		int step = PasswordManager::collatz(i);
		unordered_map<int, list<int>>::iterator it;
		it = map.find(step);
		if (it != map.end()) {
			it->second.push_back(i);
		}
		else {
			list<int> lt;
			lt.push_back(i);
			map.insert(make_pair(step, lt));
		}

	}
	unordered_map<int, list<int>>::iterator map_it;
	vector<int> openlist, closelist;
	string temp;
	if (password.size() == 1) {
		map_it=map.find(password[0]-'0');
		for (list<int>::iterator list_it = map_it->second.begin(); list_it != map_it->second.end();list_it++) {
			std::cout << *list_it << endl;
		}
	}
	else {
		while (password != temp) {
			if (password.size() == 2) {
			}
		}

	}
	return  fin_password; 
}
string PasswordManager::generate_password() {
	string password;
	for (int i = 1; i <10001 ; i++)
	{
		if (i % 100 == 0)
			password += encrypt(mode1(i / 100)) + '\n';
		else
			password += encrypt(mode1((i - 1) / 100 + 1)) + '\n';
	}
	for (int i = 1; i < 10001; i++)
	{
		if (i % 100 == 0)
			password += encrypt(mode2(i / 100)) + '\n';
		else
			password += encrypt(mode2((i - 1) / 100 + 1)) + '\n';
	}
	
	return password;
}
wstring PasswordManager::mode1(int length) {
	wstring password;
	vector<int> temp;
	vector<int>::iterator it;
	while (temp.size() < 10) {
		int ascii = rand() % ('z' - 'a'+1) + 'a';
		it = find(temp.begin(), temp.end(), ascii);
		if (it == temp.end())
			temp.push_back(ascii);
	}
	for (int i = 0; i < length; i++)
	{
		password.push_back(wchar_t(temp.at(rand() % (9 - 0 + 1) + 0)));
		
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