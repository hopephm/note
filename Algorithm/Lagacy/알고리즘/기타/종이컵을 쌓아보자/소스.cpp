#include<iostream>

using namespace std;

int main() {
	int Head, Body, NUM;
	cin >> Head >> Body >> NUM;
	for (int i = 1; i <= NUM; i++) {
		cout << NUM * Head + Body * i << " ";
	}
	cout << endl;
}