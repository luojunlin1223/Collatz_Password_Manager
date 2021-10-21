#include "User.h"
User::User(string username,wstring password) {
	this->username = username;
	this->password= PasswordManager::encrypt(password,0);
}
User::~User() {}
void User::set_username(string new_username) {
	this->username = new_username;
}
void User::set_password(wstring new_password){
	this->password = PasswordManager::encrypt(new_password,0);
}
string User::get_username() {
	return this->username;
}
string User::get_password() {
	return this->password;
}
void User::save(const string file_name) {
	ofstream write;
	write.open(file_name, ios::app);
	write << this->username << " " << this->password << endl;
	write.close();
}
bool User::authenticate(const string file_name) {
	ifstream in(file_name);
	if (!in) {
		in.close();
		throw exception("Can not find the file!");
	}
	else {
		string username, password;
		while(in>>username>>password){
			if (this->username == username && this->password == password)
				return true;
		}
		in.close();
	}
	return false; 
}


