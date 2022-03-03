#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

int main() {
	int Testcase;
	//int* Result;

	string T;

	cin >> Testcase;

	//Result = new int[Testcase];

	for (int k = 0; k < Testcase; k++) {
		int N;
		cin >> N;

		vector<string> Title;

		for (int i = 0; i < N; i++) {
			cin >> T;
			Title.push_back(T);
		}

		sort(Title.begin(), Title.end());

		int count = 0;
		char temp = 'A';

		for (int i = 0; i < N; i++) {
			if (Title[i][0] == temp) {
				count++;
				temp++;
			}
		}

		cout << "#" << k+1 << " " << count;
	}
}