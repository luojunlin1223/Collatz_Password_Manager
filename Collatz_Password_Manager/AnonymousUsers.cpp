#include "AnonymousUsers.h"
AnonymousUsers::AnonymousUsers(string password){
	this->password = password;
}
AnonymousUsers::~AnonymousUsers() {}
void AnonymousUsers::save(const string file_name) {
	ofstream write;
	write.open(file_name, ios::app);
	write <<this->password << endl;
	write.close();
}
