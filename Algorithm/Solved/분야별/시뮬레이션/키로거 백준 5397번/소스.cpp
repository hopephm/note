#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string>
#include<stack>

using namespace std;

stack<char> Out_Buffer;
stack<char> Store_Buffer;

int main() {
	int testcase;
	char c;
	string c_;

	cin >> testcase;
	
	for (int i = 0; i < testcase; i++) {
		cin >> c_;
		for(int k = 0; k<c_.length(); k++){
			c = c_[k];
			if (c == '<') {
				if (!Out_Buffer.empty()) {
					Store_Buffer.push(Out_Buffer.top());
					Out_Buffer.pop();
				}
			}
			else if (c == '>') {
				if (!Store_Buffer.empty()) {
					Out_Buffer.push(Store_Buffer.top());
					Store_Buffer.pop();
				}
			}
			else if (c == '-') {
				if (!Out_Buffer.empty()) Out_Buffer.pop();
			}
			else {
				Out_Buffer.push(c);
			}
		}

		while (!Store_Buffer.empty()) {
			Out_Buffer.push(Store_Buffer.top());
			Store_Buffer.pop();
		}
		while (!Out_Buffer.empty()) {
			Store_Buffer.push(Out_Buffer.top());
			Out_Buffer.pop();
		}
		while (!Store_Buffer.empty()) {
			printf("%c", Store_Buffer.top());
			Store_Buffer.pop();
		}
		cout << endl;
	}
}