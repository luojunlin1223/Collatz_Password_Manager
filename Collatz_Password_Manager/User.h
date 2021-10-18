#pragma once
#include <string>
#include "PasswordManager.h"
#include <fstream>
using namespace std;
class User
{
public:
	User() {};
	User(string username,wstring password);
	virtual ~User();
	void set_username(string new_username);
	void set_password(wstring new_password);
	string get_username();
	string get_password();
	virtual void save(const string file_name);
	virtual bool authenticate(const string file_name);
private:
	string username;
	string password;
};


