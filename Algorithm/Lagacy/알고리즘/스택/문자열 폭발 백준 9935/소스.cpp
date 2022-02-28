#include<iostream>
#include<string>

using namespace std;

#define MAX 1000000

char result[MAX];

bool solve(string& str, string& bomb) {
	bool isdone = true;
	int bl = bomb.length();

	int top = 0;
	for (int i = 0; i < str.size(); i++) {
		result[top++] = str[i];

		int samelength = 0;
		for (int j = 0; j < bl; j++) {
			if (result[top - 1] == bomb[bl - 1 - j]) {
				top--;
				samelength++;
			}
			else {
				break;
			}
		}

		if (samelength < bl) {
			top += samelength;
		}
		else if(samelength == bl){
			isdone = false;
		}
		
	}

	result[top] = NULL;

	str = result;

	return isdone;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string str, bomb;

	cin >> str >> bomb;

	bool isdone = solve(str, bomb);

	while (!isdone) {
		isdone = solve(str, bomb);
	}

	if (str.size() == 0) {
		cout << "FRULA" << endl;
	}
	else {
		cout << result << endl;
	}
	
	
}