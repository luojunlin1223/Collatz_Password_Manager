#include<iostream>
#include <algorithm>
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
			while (count != 0) {
				cout << "Your username:" << endl;
				cin >> username;
				cin.ignore();
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
			AnonymousUsers anon(PasswordManager::generate_password());
			anon.save(password_test_file);
			break;
		}
		case 4: {
			Decoder decoder;
			string test;
			vector<tuple<int, int,wstring>> pre;
			string password = "27322810313331033910211452912207344136146925461033281533271031012815108114101";
			decoder.decrypt(password);
			for (int l = 0; l < decoder.result.size(); l++) {
				vector<vector<tuple<string, wstring>>> result2;
				for (int i = 0; i < decoder.result[l].size(); i++) {
					result2.push_back(decoder.find_dir(decoder.result[l][i], "train.txt"));
				}

				for (int i = 0; i < decoder.result[l].size(); i++) {
					string temp;
					temp = to_string(decoder.result[l][i]);
					for (int j = i + 1; j < decoder.result[l].size(); j++) {
						temp += to_string(decoder.result[l][j]);
						for (int k = 0; k < result2[i].size(); k++) {
							if (i == 0)
							{
								if (temp == get<0>(result2[i][k]))
									pre.push_back(make_tuple(i,j,get<1>(result2[i][k])));
							}
							else
							{
								if (temp == get<0>(result2[i - 1][k]))
								{
									pre.push_back(make_tuple(i, j, get<1>(result2[i-1][k])));
								}
							}
						}
					}
				}
				cout << "--------" << endl;
			}
			sort(pre.begin(), pre.end());
			pre.erase(unique(pre.begin(), pre.end()), pre.end());

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