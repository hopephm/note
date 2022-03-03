#include<iostream>

using namespace std;

#define MAX 1000000

int examinant[MAX];

int main() {
	int N;
	int B, C;

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> examinant[i];
	}

	cin >> B >> C;

	unsigned long long result = 0;
	for (int i = 0; i < N; i++) {
		result++;

		int to_check = examinant[i] - B;

		if (to_check > 0) {
			int quotient = to_check / C;
			int remainder = to_check % C;

			result += quotient + 1;
			if (remainder == 0) {
				result--;
			}

		}
	}

	cout << result << endl;
}