#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 1000

int RGB_val[MAX][3];
int RGB_sum[MAX][3]; // 0 ���� i��° ������ 0 >> �������� ��, 1 >> �� ���� ���� ��

int main() {
	int N, R, G, B;
	
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> RGB_val[i][0] >> RGB_val[i][1] >> RGB_val[i][2];
	}

	// ���� ������ �߻��� �� ���� ���� ���� ���� ������ ���� ���� ���� ��.

	for (int i = 0; i < 3; i++) RGB_sum[0][i] = RGB_val[0][i];

	for (int i = 1; i < N; i++) {
		RGB_sum[i][0] = min(RGB_sum[i - 1][1], RGB_sum[i - 1][2]) + RGB_val[i][0];
		RGB_sum[i][1] = min(RGB_sum[i - 1][0], RGB_sum[i - 1][2]) + RGB_val[i][1];
		RGB_sum[i][2] = min(RGB_sum[i - 1][1], RGB_sum[i - 1][0]) + RGB_val[i][2];
	}

	int Min_val = min(RGB_sum[N - 1][0], RGB_sum[N - 1][1]);
	Min_val = min(Min_val, RGB_sum[N - 1][2]);

	cout << Min_val << endl;

}

