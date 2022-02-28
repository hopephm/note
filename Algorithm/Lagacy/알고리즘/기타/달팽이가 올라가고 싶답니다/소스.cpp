#include<iostream>
using namespace std;

int main(void) {
	int A, B, V;
	cin >> A >> B >> V;

	int temp = V - A;
	int val;
	if (temp % (A - B) == 0)
		val = temp / (A - B);
	else
		val = temp / (A - B) + 1;
	cout << val + 1;
}