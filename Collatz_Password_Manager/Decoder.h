#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;
class Decoder
{public:
	Decoder();
	~Decoder();
	unordered_map<int, vector<int>> map;
	vector<vector<tuple<int, int, wstring>>> pre_pretable;
	vector<vector<int>> result_combination;
	vector<vector<int>> result;
	vector<int> path_combination;
	vector<int> path;
	bool check(vector<int> _list, vector<int> path);
	void backtracking_combination(int startindex, string password);
	void backtracking(int startindex, vector<int> result, vector<tuple<int, int, wstring>> temp_pretable);
	void backtracking(int startindex, vector<int> result_combination);
	vector<string> decrypt(string password, bool _train);
	void train();
	vector<tuple<string, wstring>> find_dir(int start,string dir_file);
};

