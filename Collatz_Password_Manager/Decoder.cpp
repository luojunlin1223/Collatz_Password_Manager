#include "Decoder.h"
#include "PasswordManager.h"
Decoder::Decoder() {
	for (int i = 1; i < 256; i++)
	{
		int step = PasswordManager::collatz(i);
		unordered_map<int, vector<int>>::iterator it;
		it = map.find(step);
		if (it != map.end()) {
			it->second.push_back(i);
		}
		else {
			vector<int> lt;
			lt.push_back(i);
			map.insert(make_pair(step, lt));
		}
	}
	this->pretreatment = map;
}
Decoder::~Decoder() {}
bool Decoder::check(vector<int> _list, vector<int> path) {
	for (vector<int>::iterator it = _list.begin(); it != _list.end(); it++) {
		if (path.size() == 0) {
			if (iswprint(*it))
				return true;
		}
		else {
			if (*it >= path.back()) {
				if (iswprint(*it - path.back()))
					return true;
			}
		}
	}
	return false;
}
void Decoder::backtracking(int startindex, string password) {
	string temp;
	for (vector<int>::iterator it = path.begin(); it != path.end(); it++) {
		temp += to_string(*it);
	}
	if (temp == password) {
		result.push_back(path);
		return;
	}
		unordered_map<int, vector<int>>::iterator it;
		if((password[startindex] - '0'==0))
			return;
		if (startindex < password.size() - 1) {
			it = map.find((password[startindex] - '0') * 10 + (password[static_cast<__int64>(startindex) + 1] - '0'));
			if (it != map.end() && check(it->second, path)) {
				path.push_back((password[startindex] - '0') * 10 + (password[static_cast<__int64>(startindex) + 1] - '0'));
				backtracking(startindex + 2, password);
				path.pop_back();
			}
		}
		if (startindex < password.size() - 2) {
			it = map.find((password[startindex] - '0') * 100 + (password[static_cast<__int64>(startindex) + 1] - '0') * 10
				+ (password[static_cast<__int64>(startindex) + 2] - '0'));
			if (it != map.end() && check(it->second, path)) {
				path.push_back((password[startindex] - '0') * 100 + (password[static_cast<__int64>(startindex) + 1] - '0') * 10
					+ (password[static_cast<__int64>(startindex) + 2] - '0'));
				backtracking(startindex + 3, password);
				path.pop_back();
			}

		}
		it = map.find(password[startindex] - '0');
		if (it != map.end() && check(it->second, path)) {
			path.push_back(password[startindex] - '0');
			backtracking(startindex + 1, password);
			path.pop_back();
		}
	
}
void Decoder::backtracking2(int startindex, vector<int> result) {
	if (path2.size() == result.size()) {
		result2.push_back(path2);
		return;
	}
	unordered_map<int, vector<int>>::iterator it;
	it = map.find(result.at(startindex));
	for (int i = 0; i < it->second.size(); i++) {
		if (path2.size() == 0) {
			if (iswprint(it->second.at(i))) {
				path2.push_back(it->second.at(i));
				backtracking2(startindex + 1, result);
				path2.pop_back();
			}
		}
		else {
			if (it->second.at(i) >= result.at(path2.size() - 1)) {
				if (iswprint(it->second.at(i) - result.at(path2.size() - 1))) {
					path2.push_back(it->second.at(i) - result.at(path2.size() - 1));
					backtracking2(startindex + 1, result);
					path2.pop_back();
				}
			}
		}
	}
}
vector<wstring> Decoder::decrypt(string password) {
	vector<wstring> _result;
	backtracking(0, password);

	/*for (vector<vector<int>>::iterator it = result.begin(); it != result.end(); it++) {
		backtracking2(0, *it);
	}
	for (vector<vector<int>>::iterator it = result2.begin(); it != result2.end(); it++) {
		wstring decrypted;
		for (vector<int>::iterator _it = it->begin(); _it != it->end(); _it++) {
			decrypted.push_back(wchar_t(*_it));
		}
		_result.push_back(decrypted);
	}*/

	return _result;
}
void Decoder::train() {

}