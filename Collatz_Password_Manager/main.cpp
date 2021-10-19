#include<iostream>
#include "PasswordManager.h"
#include "User.h"
#include "AnonymousUsers.h"
#include <locale.h>
#include <unordered_map>
#define password_file "password.txt"
#define password_test_file "passwordtest.txt"
unordered_map<int, list<int>> map;
vector<vector<int>> result;
vector<int> path;
string test = "2541103";
using namespace std;
void backtracking(int startindex, string password) {
	string temp;
	for (vector<int>::iterator it = path.begin(); it != path.end(); it++) {
		temp += to_string(*it);
	}
	if (temp==password) {
		result.push_back(path);
		return;
	}
	for (int i = startindex; i < password.size(); i++) {
		unordered_map<int, list<int>>::iterator it;
		if (i < password.size() - 1) {
			it = map.find((password[i] - '0') * 10 + (password[i+1] - '0'));
			if (it != map.end()) {
				path.push_back((password[i] - '0') * 10 + (password[i+1] - '0'));
				backtracking(i + 2, password);
				path.pop_back();
			}
		}
		if (i < password.size() - 2) {
			it = map.find((password[i] - '0') * 100 + (password[i+1] - '0') * 10 + (password[i+2] - '0'));
			if (it != map.end()) {
				path.push_back((password[i] - '0') * 10 + (password[i+1] - '0') * 10 + (password[i+2] - '0'));
				backtracking(i + 3, password);
				path.pop_back();
			}
			
		}
		it = map.find(password[i] - '0');
		if (it != map.end()) {
			path.push_back(password[i] - '0');
			backtracking(i + 1, password);
			path.pop_back();
		}
	}
}
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
			backtracking(0, test);
			cout << 254/1%10; 
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