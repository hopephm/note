#include<iostream>
#include<algorithm>

using namespace std;

#define MAX 300

int N;
int Stair[MAX];
int acc_Stair[MAX];
bool is_Continued[MAX];

void Init() {
	for (int i = 0; i < N; i++) {
		acc_Stair[i] = 0;
		is_Continued[i] = false;
	}
}


int main() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> Stair[i];
	}

	int val = 0;

	// 현재의 누적값 = 이전 누적값 혹은 전전 누적값 중 큰 값
	//  * 단 이전 값이 FLAG(연속) 이라면 전전 누적값을 선택
	// 처음에 1계단을 뛸지, 두계단을 뛸지 선택해놓아야 함.

	for (int k = 0; k < 2; k++) {

		// 초기화
		Init();

		if (k == 0) { // 처음에 1계단을 선택한 경우
			acc_Stair[0] = Stair[0];
			is_Continued[0] = false;

			acc_Stair[1] = Stair[1] + Stair[0];
			is_Continued[1] = true;
		}
		else {		  // 처음에 2계단을 선택한 경우
			acc_Stair[0] = 0;
			is_Continued[0] = false;

			acc_Stair[1] = Stair[1];
			is_Continued[1] = false;
		}
		
		// 최대 누적값을 저장하는 알고리즘
		for (int i = 2; i < N; i++) {
			if (acc_Stair[i - 1] > acc_Stair[i - 2]) {
				if (is_Continued[i - 1]) {
					acc_Stair[i] = acc_Stair[i - 2] + Stair[i];
					is_Continued[i] = false;
				}
				else {
					acc_Stair[i] = acc_Stair[i - 1] + Stair[i];
					is_Continued[i] = true;
				}
			}
			else {
				acc_Stair[i] = acc_Stair[i - 2] + Stair[i];
				is_Continued[i] = false;
			}
		}

		/*for (int i = 0; i < N; i++) {
			cout << i + 1 << "번째 : " << acc_Stair[i] << " ";
			if ((i + 1) % 10 == 0) cout << endl;
		}
		cout << endl;*/
		val = max(val,acc_Stair[N - 1]);
	}

	//cout << endl;
	cout << val << endl;
}