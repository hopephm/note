#include<iostream>
#include<stack>
#include<string>

using namespace std;

#define MAX 1000

void solve(string& str) {
	stack<char> oper;

	char result[MAX];
	int top = 0;

	


	result[top] = NULL;

	str = result;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);


	string str;

	cin >> str;

	solve(str);

	cout << str << endl;
}