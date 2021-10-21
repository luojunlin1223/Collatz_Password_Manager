#include <iostream>
#include "AnonymousUsers.h"
#include "Decoder.h"
#define password_file "password.txt"
#define password_test_file "passwordtest.txt"
#define password_origin_file "passwordtest_origin.txt"
using namespace std;
int main() {
	setlocale(LC_ALL, "en_US.UTF-8");
	while (true) {
		int choice;
		cout << "1. Create a new account." << endl;
		cout << "2. Authenticate the password." << endl;
		cout << "3. Generate password." << endl;
		cout << "4. Analyze password." << endl;
		cout << "5. Quit." << endl;
		cout << "Your choice:" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: {
			string username;
			wstring password;
			string temp;
			cout << "Your username:" << endl;
			cin >> username;
			cin.ignore();
			cout << "Your password:" << endl;
			getline(wcin, password);
			User user(username, password);
			user.save(password_file);
			break;
		}
		case 2: {
			string username;
			wstring password;
			int count = 3;
			cout << "Your username:" << endl;
			cin >> username;
			cin.ignore();
			while (count != 0) {
				cout << "Your password:" << endl;
				getline(wcin, password);
				User user(username, password);
				try {
					if (user.authenticate(password_file)) {
						cout << "success!" << endl;
						break;
					}
					else {
						cout << "failure!" << endl;
						cout << "number of retries: " << count-1 << endl;
						count--;
					}
				}
				catch (exception& except) {
					cout << except.what() << endl;
				}
			}
			break;
		}
		case 3: {
			PasswordManager pm;
			pm.generate_password();
			AnonymousUsers anon_password(pm.password);
			AnonymousUsers anon_origin(pm.origin);
			anon_password.save(password_test_file,pm.password);
			anon_origin.save(password_origin_file, pm.origin);
			break;
		}
		case 4: {
			Decoder decoder;
			string password;
			cout << "Password: " << endl;
			cin >> password;
			vector<string> result=decoder.decrypt(password,false);
			break;
		}
		case 5: {
			exit(1);
			break;
		}
		default: {
			cout << "wrong!" << endl;
			break;
		}
		}
	}
}