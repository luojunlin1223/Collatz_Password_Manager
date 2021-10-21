#include "AnonymousUsers.h"
AnonymousUsers::AnonymousUsers(string password){
	this->password = password;
}
AnonymousUsers::AnonymousUsers(wstring password) {
	this->wpassword = password;
}
AnonymousUsers::~AnonymousUsers() {}
void AnonymousUsers::save(const string file_name,string password) {
	ofstream write;
	write.open(file_name, ios::app);
	write <<password << endl;
	write.close();
}
void AnonymousUsers::save(const string file_name, wstring password) {
	wofstream write;
	write.open(file_name, ios::app);
	write << password << endl;
	write.close();
}
