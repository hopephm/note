#include<iostream>
#include<string>
#include<stack>

using namespace std;

int main() {
	string str1, str2;

	cin >> str1 >> str2;
	int **DP = new int*[str1.length() + 1];
	for (int i = 0; i < str1.length() + 1; i++) {
		DP[i] = new int[str2.length() + 1];
	}

	for (int i = 0; i < str1.length(); i++)
		DP[i][0] = 0;
	for (int j = 0; j < str2.length(); j++)
		DP[0][j] = 0;


	int temp_val = 0;
	for (int i = 1; i <= str1.length(); i++) {
		for (int j = 1; j <= str2.length(); j++) {
			if (str1[i - 1] == str2[j - 1]) {
				DP[i][j] = DP[i - 1][j - 1] + 1;
			}
			else {
				DP[i][j] = 0;
			}
			if (DP[i][j] > temp_val) {
				temp_val = DP[i][j];
			}
		}
	}

	cout << temp_val << endl;
}