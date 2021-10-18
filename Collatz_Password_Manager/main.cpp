#include<iostream>
#include "PasswordManager.h"
#include "User.h"
#include "AnonymousUsers.h"
#include <locale.h>
#include <unordered_map>
#define password_file "password.txt"
#define password_test_file "passwordtest.txt"
using namespace std;
unordered_map<int, list<int>> map;
int main() {
	setlocale(LC_ALL, "en_US.UTF-8");
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
			/*int j = 0;
			int jj = 0;
			int jjj = 0;
			for (int i = 1; i < 256; i++)
			{
				
				int step = PasswordManager::collatz(i);
				if (0 <= step && step <= 10)
					j++;
				else if (11 <= step && step <= 99)
					jj++;
				else
					jjj++;
			}
			cout << j << endl;
			cout << jj << endl;
			cout << jjj << endl;*/
			
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
		/*User user("luojunlin", L"dnf528571@");
		user.save(password_file);

		try {
			cout<<user.authenticate(password_file);
		}
		catch (exception& excep) {
			cout << excep.what();
		}

		AnonymousUsers user2(PasswordManager::generate_password());
		user2.save(password_test_file);*/
	}
}