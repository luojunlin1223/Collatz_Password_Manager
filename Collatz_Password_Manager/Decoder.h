#pragma once
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;
class Decoder
{public:
	Decoder();
	~Decoder();
	unordered_map<int, vector<int>> map;
	unordered_map<int, vector<int>> pretreatment;
	vector<vector<int>> result;
	vector<vector<int>> result2;
	vector<int> path;
	vector<int> path2;
	bool check(vector<int> _list, vector<int> path);
	void backtracking(int startindex, string password);
	void backtracking2(int startindex, vector<int> result);
	vector<wstring> decrypt(string password);
	void train();
};

