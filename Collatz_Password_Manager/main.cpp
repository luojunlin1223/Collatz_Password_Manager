#include<iostream>
#include "AnonymousUsers.h"
#include "Decoder.h"
#define password_file "password.txt"
#define password_test_file "passwordtest.txt"
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
			cout << "Your username:" << endl;
			cin >> username;
			cout << "Your password:" << endl;
			wcin >> password;
			User user(username, password);
			user.save(password_file);
			break;
		}
		case 2: {
			string username;
			wstring password;
			int count = 3;
			while (count != 0) {
				cout << "Your username:" << endl;
				cin >> username;
				cout << "Your password:" << endl;
				wcin >> password;
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
			AnonymousUsers anon(PasswordManager::generate_password());
			anon.save(password_test_file);
			break;
		}
		case 4: {
			Decoder decoder;
			string test;
			unordered_map<string, wstring> map;
			wifstream in("train.txt");
			if (!in) {
				in.close();
				throw exception("Can not find the file!");
			}
			else {
				wstring word;
				while (in >> word) {
					test = PasswordManager::encrypt(word);
					map.insert(make_pair(test, word));
				}
				in.close();
			}
			//decoder.decrypt("27322810313331033910211452912207344136146925461033281533271031012815108114101");
			string password = "27322810313331033910211452912207344136146925461033281533271031012815108114101";
			decoder.decrypt(password);
			for (int i = 0; i < password.size(); i++) {
				for (int j = 1; j < password.size(); j++) {
					string sub = password.substr(i, j);
					for (unordered_map<string, wstring>::iterator it = map.begin(); it != map.end(); it++) {
						if (sub == it->first) {
							wcout << it->second << endl;
						}
					}
				}
			}	
			int i = 0;
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