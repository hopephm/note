#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> persons_running_time;

int main() {
	int testcase;

	cin >> testcase;

	int time;
	for (int i = 0; i < testcase; i++) {
		cin >> time;
		persons_running_time.push_back(time);
	}

	sort(persons_running_time.begin(), persons_running_time.end());

	int sum = 0;

	for (int i = 0; i < persons_running_time.size(); i++) {
		sum += persons_running_time[i] * (persons_running_time.size() - i);
	}

	cout << sum << endl;
}