#include "Decoder.h"
#include "PasswordManager.h"
#include <fstream>
#include <iostream>
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
void Decoder::backtracking_combination(int startindex, string password) {
	string temp;
	for (vector<int>::iterator it = path_combination.begin(); it != path_combination.end(); it++) {
		temp += to_string(*it);
	}
	if (temp == password) {
		result_combination.push_back(path_combination);
		return;
	}
		unordered_map<int, vector<int>>::iterator it;
		if((password[startindex] - '0'==0))
			return;
		if (startindex < password.size() - 1) {
			it = map.find((password[startindex] - '0') * 10 + (password[static_cast<__int64>(startindex) + 1] - '0'));
			if (it != map.end() && check(it->second, path_combination)) {
				path_combination.push_back((password[startindex] - '0') * 10 + (password[static_cast<__int64>(startindex) + 1] - '0'));
				backtracking_combination(startindex + 2, password);
				path_combination.pop_back();
			}
		}
		if (startindex < password.size() - 2) {
			it = map.find((password[startindex] - '0') * 100 + (password[static_cast<__int64>(startindex) + 1] - '0') * 10
				+ (password[static_cast<__int64>(startindex) + 2] - '0'));
			if (it != map.end() && check(it->second, path_combination)) {
				path_combination.push_back((password[startindex] - '0') * 100 + (password[static_cast<__int64>(startindex) + 1] - '0') * 10
					+ (password[static_cast<__int64>(startindex) + 2] - '0'));
				backtracking_combination(startindex + 3, password);
				path_combination.pop_back();
			}

		}
		it = map.find(password[startindex] - '0');
		if (it != map.end() && check(it->second, path_combination)) {
			path_combination.push_back(password[startindex] - '0');
			backtracking_combination(startindex + 1, password);
			path_combination.pop_back();
		}
	
}
void Decoder::backtracking(int startindex, vector<int> result_combination, vector<tuple<int, int, wstring>> temp_pretable) {
	if (path.size() == result_combination.size()) {
		result.push_back(path);
		return;
	}
	for (vector<tuple<int, int, wstring>>::iterator tuple_it = temp_pretable.begin(); tuple_it != temp_pretable.end(); tuple_it++) {
			if (get<0>(*tuple_it) == startindex) {
				wstring temp = get<2>(*tuple_it);
				int count = 0;
				for (wstring::iterator temp_it = temp.begin(); temp_it != temp.end(); temp_it++) {
					path.push_back(*temp_it);
					count++;
				}
				if ((size_t)startindex + count <= result_combination.size()) {
					if ((size_t)startindex + count + 1 <= result_combination.size()) {
						path.push_back(32);
						backtracking(startindex + count+1, result_combination, temp_pretable);
						for (int i = 0; i < count+1; i++) {
							path.pop_back();
						}
					}
					else {
						backtracking(startindex + count, result_combination, temp_pretable);
						for (int i = 0; i < count; i++) {
							path.pop_back();
						}
					}
				}
				else {
					for (int i = 0; i < count; i++) {
						path.pop_back();
					}
				}
			}	
		}
	unordered_map<int, vector<int>>::iterator it;
	it = map.find(result_combination.at(startindex));
	for (int i = 0; i < it->second.size(); i++) {
		if (path.size() == 0) {
			if (isprint(it->second.at(i))) {
				path.push_back(it->second.at(i));
				backtracking(startindex + 1, result_combination, temp_pretable);
				path.pop_back();
			}
		}
		else {
			if (it->second.at(i) >= result_combination.at(path.size() - 1)) {
				if (isprint(it->second.at(i) - result_combination.at(path.size() - 1))) {
					path.push_back(it->second.at(i) - result_combination.at(path.size() - 1));
					backtracking(startindex + 1, result_combination, temp_pretable);
					path.pop_back();
				}
			}
		}
	}
}
void Decoder::backtracking(int startindex, vector<int> result_combination) {
	if (path.size() == result_combination.size()) {
		result.push_back(path);
		return;
	}
	unordered_map<int, vector<int>>::iterator it;
	it = map.find(result_combination.at(startindex));
	for (int i = 0; i < it->second.size(); i++) {
		if (path.size() == 0) {
			if (isprint(it->second.at(i))) {
				path.push_back(it->second.at(i));
				backtracking(startindex + 1, result_combination);
				path.pop_back();
			}
		}
		else {
			if (it->second.at(i) >= result_combination.at(path.size() - 1)) {
				if (isprint(it->second.at(i) - result_combination.at(path.size() - 1))) {
					path.push_back(it->second.at(i) - result_combination.at(path.size() - 1));
					backtracking(startindex + 1, result_combination);
					path.pop_back();
				}
			}
		}
	}
}
vector<string> Decoder::decrypt(string password,bool _train) {
	vector<string> _result;
	backtracking_combination(0, password);
	if (_train) {
		train();
		for (int i = 0; i < result_combination.size(); i++) {
			backtracking(0, result_combination[i], pre_pretable[i]);
		}
	}
	else {
		for (int i = 0; i < result_combination.size(); i++) {
			backtracking(0, result_combination[i]);
		}
	}
	for (vector<vector<int>>::iterator result_it = result.begin(); result_it != result.end(); result_it++) {
		string temp;
		for (vector<int>::iterator it = result_it->begin(); it != result_it->end(); it++) {
			temp.push_back(*it);
		}
		_result.push_back(temp);
	}
	return _result;
}
void Decoder::train() {
	for (int l = 0; l < result_combination.size(); l++) {
		vector<tuple<int, int, wstring>> temp_pretable;
		vector<vector<tuple<string, wstring>>> result2;
		for (int i = 0; i < result_combination[l].size(); i++) {
			result2.push_back(find_dir(result_combination[l][i], "train.txt"));
		}

		for (int i = 0; i < result_combination[l].size(); i++) {
			string temp;
			temp = to_string(result_combination[l][i]);
			for (int j = i + 1; j < result_combination[l].size(); j++) {
				temp += to_string(result_combination[l][j]);
				for (int k = 0; k < result2[i].size(); k++) {
					if (i == 0)
					{
						if (temp == get<0>(result2[i][k]))
							temp_pretable.push_back(make_tuple(i, j, get<1>(result2[i][k])));
					}
					else
					{
						if (temp == get<0>(result2[static_cast<__int64>(i) - 1][k]))
						{
							temp_pretable.push_back(make_tuple(i, j, get<1>(result2[static_cast<__int64>(i) - 1][k])));
						}
					}
				}
			}
		}
		sort(temp_pretable.begin(), temp_pretable.end());
		temp_pretable.erase(unique(temp_pretable.begin(), temp_pretable.end()), temp_pretable.end());
		pre_pretable.push_back(temp_pretable);
	}
}
vector<tuple<string,wstring>> Decoder::find_dir(int start,string dir_file) {
	wifstream in(dir_file);
	string temp;
	vector<tuple<string, wstring>> result;
	if (!in) {
		in.close();
		throw exception("Can not find the file!");
	}
	else {
		wstring word;
		while (in >> word) {
			temp = PasswordManager::encrypt(word,start);
			result.push_back(make_tuple(temp,word));
		}
		in.close();
	}
	return result;
}