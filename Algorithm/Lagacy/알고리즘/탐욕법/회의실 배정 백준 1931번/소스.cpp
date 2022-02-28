#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<pair<int, int>> conf;

int solve() {

	int count = 0;
	long long cur_end = 0;
	for (int i = 0; i < conf.size(); i++) {
		if (conf[i].second >= cur_end) {
			count++;
			cur_end = conf[i].first;
		}
	}
	return count;
}

int main() {
	int testcase;

	cin >> testcase;

	long long st_time, ed_time;
	for (int i = 0; i < testcase; i++) {
		cin >> st_time >> ed_time;
		conf.push_back({ ed_time, st_time });
	}
	
	sort(conf.begin(), conf.end());

	cout << solve() << endl;
}