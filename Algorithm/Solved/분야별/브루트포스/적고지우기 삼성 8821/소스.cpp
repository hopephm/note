#include<iostream>
#include<string>

using namespace std;

int main() {
	int testcase;
	cin >> testcase;

	for (int i = 0; i < testcase; i++) {
		string nums;
		cin >> nums;

		int counts[10];
		memset(counts, 0, sizeof(counts));

		for (int j = 0; j < nums.length(); j++) {
			counts[int(nums[j])-48]++;
		}

		int result = 0;
		for (int j = 0; j < 10; j++) {
			if (counts[j] % 2 == 1) result++;
		}

		cout << "#" << i+1 << " " << result << endl;

	}

}