#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

#define MAX_ptcp 1024


int recursive(int K, int* A) {
	// �������� (�������)
	if (K <= 0) return 0;

	// ��������
	int sum = 0;
	for (int i = 0; i < pow(2, K-1); i++) {
		sum += abs(A[2 * i] - A[2 * i + 1]);
		A[i] = max(A[2 * i], A[2 * i + 1]);
	}

	return sum + recursive(K - 1, A);

}


int main() {
	int testcase;
	cin >> testcase;

	for (int i = 0; i < testcase; i++) {
		int K;
		cin >> K;

		int A[MAX_ptcp];

		for (int j = 0; j < pow(2, K); j++) { // �Ǽ��ڷ��� �̿��� �������
			cin >> A[j];
		}

		int sum = recursive(K, A);

		cout << "#1 " << sum << endl;

	}
}