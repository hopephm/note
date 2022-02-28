#include<iostream>
#include<cmath>

using namespace std;

int value[10] = { 0 };

void Solve(int n, int count) {
	int temp = pow(10, count);
	int quotient = n / (temp * 10);
	int key = (n / temp) % 10;
	int remainder = n % temp;

	if (count == 0) remainder = 0;

	for (int i = 0; i < 10; i++) {
		value[i] += quotient * temp;
		if (i < key) {
			value[i] += temp;
		}
		else if (i == key) {
			value[i] += remainder + 1;
		}
	}
	value[0] -= temp;

	if (count > 0) Solve(n, count - 1);
}


int main() {
	int n, temp, count;
	cin >> n;

	temp = n;
	count = 0;

	// 경계값 등호 부등호 주의하자!
	while (temp >= 10) { // 이부분에 등호를 안붙여서 틀림.... >   를  >= 로 바꾸니 동작
		temp = temp / 10;
		count++;
	}

	Solve(n, count);

	for (int i = 0; i < 10; i++) {
		cout << value[i] << " ";
	}
}