#include<iostream>
using namespace std;

long long count_ = 0;
void Solve(long long size, long long f_y, long long f_x) {
	long long t = size / 2;

	if (f_x >= t) {
		count_ += t * t;
		f_x -= t;
	}
	if (f_y >= t) {
		count_ += t * t * 2;
		f_y -= t;
	}

	if (size > 2) Solve(t, f_y, f_x);
}

int main() {
	long long N, y, x;
	cin >> N >> y >> x;

	long long Size_ = 1;
	for (int i = 0; i < N; i++) {
		Size_ *= 2;
	}

	Solve(Size_, y, x);

	cout << count_ << endl;
}