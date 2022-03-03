#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 1000

int RGB_val[MAX][3];
int RGB_sum[MAX][3]; // 0 현재 i번째 값에서 0 >> 가장작은 값, 1 >> 그 다음 작은 값

int main() {
	int N, R, G, B;
	
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> RGB_val[i][0] >> RGB_val[i][1] >> RGB_val[i][2];
	}

	// 현재 값에서 발생할 수 없는 이전 누적 값을 제외한 것중 작은 것을 고름.

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

