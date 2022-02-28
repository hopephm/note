/*#include<iostream>

using namespace std;

#define cur 0
#define next 1

int DP[2][10];

int main() {
	int N;
	cin >> N;

	for (int i = 1; i < 10; i++) {
		DP[0][i] = 1;
	}
	DP[0][0] = 0;

	if (N == 1) {
		cout << 9 << endl;
		return 0;
	}

	int temp = 2;

	while (temp <= N) {
		DP[next][0] = DP[cur][1];
		for (int i = 1; i < 9; i++) {
			DP[next][i] = (DP[cur][i - 1] + DP[cur][i + 1]) % 1000000000;
		}
		DP[next][9] = DP[cur][8];

		for (int i = 0; i < 10; i++) {
			DP[cur][i] = DP[next][i];
		}

		temp++;
	}

	int result = 0;
	for (int i = 0; i < 10; i++) {
		result = (result + DP[cur][i]) % 1000000000;
	}

	cout << result << endl;
}*/

#include<iostream>

using namespace std;

#define MAX 101

int current[MAX][10];

int main() {
	int N;
	cin >> N;

	for (int i = 1; i < 10; i++) {
		current[1][i] = 1;
	}
	current[1][0] = 0;

	if (N == 1) {
		cout << 9 << endl;
		return 0;
	}

	int temp = 2;

	while (temp <= N) {
		current[temp][0] = current[temp - 1][1];
		for (int i = 1; i < 9; i++) {
			current[temp][i] = (current[temp - 1][i - 1] + current[temp - 1][i + 1]) % 1000000000;
		}
		current[temp][9] = current[temp - 1][8];
		temp++;
	}

	int result = 0;
	for (int i = 0; i < 10; i++) {
		result = (result + current[N][i]) % 1000000000;
	}

	cout << result << endl;
}