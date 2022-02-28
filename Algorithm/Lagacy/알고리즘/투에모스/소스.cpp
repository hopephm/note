#include<iostream>
#include<stdio.h>
#include<string>

using namespace std;

int main() {
	string val = "0";
	int N, x, y;

	cin >> N >> x >> y;

	for(int j = 0; j < N -1; j++){
		int s = val.size();

		for (int i = 0; i < s; i++) {
			if (val[i] == '0') {
				val = val + "1";
			}
			else {
				val = val + "0";
			}
		}
	}

	for (int i = x - 1; i < y; i++) {
		printf("%c", val[i]);
	}
	cout << endl;
}