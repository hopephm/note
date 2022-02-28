#include<iostream>
#include<cmath>

using namespace std;

#define MAX 16

int pow10k_coins[MAX] = { 0 };
int pow100k_25_coins_sum = 0;

void solve1(long long val, int size) {
	if (size == 0) {
		pow10k_coins[size] = val;
	}
	else {
		long long coin = (long long)pow(10, size);
		pow10k_coins[size] = val / coin;
		val = val - coin * pow10k_coins[size];
		solve1(val, size - 1);
	}
}

void solve2(int size) {
	if (size <= 0) {
		return;
	}
	else if (size % 2 != 0) {
		if (pow10k_coins[size] >= 2 && pow10k_coins[size - 1] >= 5) {
			pow10k_coins[size] -= 2;
			pow10k_coins[size-1] -= 5;
			pow100k_25_coins_sum++;
		}
		if (pow10k_coins[size] >= 5) {
			pow10k_coins[size] -= 5;
			pow100k_25_coins_sum += 2;
		}
		solve2(size - 2);
	}
	else {
		solve2(size - 1);
	}
}

int main() {
	long long val;
	int testcase;

	cin >> testcase;

	for (int i = 0; i < testcase; i++) {
		cin >> val;
		int size = 0;
		pow100k_25_coins_sum = 0;

		while (val / (long long)pow(10, size) > 0) {
			size++;
		}
		solve1(val, size - 1);
		solve2(size - 1);

		int sum = 0;
		for (int i = 0; i < size; i++) {
			sum += pow10k_coins[i];
		}
		sum += pow100k_25_coins_sum;

		cout << sum << endl;
	}
}