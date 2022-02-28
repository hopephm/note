#include<iostream>
#include<cmath>
using namespace std;
int N;

bool is_hannum (int N) {
	int count_ = 0;
	int cur_sub, sub = (N / 10) % 10 - N % 10; // 10의 자리 - 1의자리 
	int temp = N;

	while (temp >= 10) {
		temp = temp / 10; count_++;
	}

	for (int i = count_-1; i >= 0; i--) {
		cur_sub = (int)(N / pow(10, i + 1)) % 10 - (int)(N / pow(10, i)) % 10;
		if (cur_sub != sub) {
			return false;
		}
	}
	return true;
}


int main() {
	cin >> N;
	int count__ = 0;

	for (int i = 1; i <= N; i++) {
		if (i < 100 || is_hannum(i)) {
			count__++;
		}
	} cout << count__;
}

