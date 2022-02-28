#include<iostream>
#include<string>
#include<algorithm>
#include<stack>

using namespace std;

int DP[1001][1001];
stack<char> st;

int main(){
	string str1, str2;
	cin >> str1 >> str2;

	for (int i = 0; i < str1.length(); i++) {
		DP[0][i] = 0;
	}
	for (int j = 0; j < str2.length(); j++) {
		DP[j][0] = 0;
	}


	for (int i = 1; i <= str1.length(); i++) {
		for (int j = 1; j <= str2.length(); j++) {
			if (str1[i-1] == str2[j-1]) {
				DP[i][j] = DP[i - 1][j - 1] + 1;
			}
			else {
				DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
			}
		}
	}

	for (int i = 0; i <= str1.length(); i++) {
		if(i != 0) cout << str1[i-1] << " ";
		if (i == 0) {
			cout << "    ";
			for (int j = 0; j < str2.length(); j++) {
				cout << str2[j] << " ";
			}
			cout << endl;
			cout << "  ";
		}
		for (int j = 0; j <= str2.length(); j++) {
			cout << DP[i][j] << " ";
		}
		cout << endl;
	}

	cout << DP[str1.length()][str2.length()] << endl;

	int p_str1 = str1.length();
	int p_str2 = str2.length();

	while (p_str1 >= 0 && p_str2 >= 0) {
		if (DP[p_str1][p_str2 - 1] == DP[p_str1][p_str2]) {
			p_str2--;
		}
		else if (DP[p_str1 - 1][p_str2] == DP[p_str1][p_str2]) {
			p_str1--;
		}
		else {
			st.push(str1[p_str1-1]);
			p_str1--; p_str2--;
		}
	}

	while (!st.empty()) {
		cout << st.top(); st.pop();
	}
	cout << endl;
}