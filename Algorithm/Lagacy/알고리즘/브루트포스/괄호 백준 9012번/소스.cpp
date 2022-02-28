#include<iostream>
#include<string>
#include<stack>

using namespace std;

int main() {
	int testCase;

	cin >> testCase;

	for (int k = 0; k < testCase; k++) {
		string PS;
		cin >> PS;

		bool flag = true;
		stack<char> st;
		int count = 0;
		for (int i = 0; i < PS.length(); i++) {
			if (PS[i] == '(') st.push(count++);
			else if (PS[i] == ')') {
				if (st.empty()) {
					flag = false;
					break;
				}
				st.pop();
			}
		}

		if (!st.empty()) flag = false;

		if (flag) cout << "YES" << endl;
		else cout << "NO" << endl;

	}

}