#include<iostream>

using namespace std;

#define MAX 100
int values[MAX];

/*
	문제 : 매순간 필요한 돈 이하의 액면을 가진 동전 중 가장 액면이 높은 동전 추가

	>> 필요한 돈 이하의 액면을 가진 동전 중 가장 액면이 높은 동전말고 다른 동전 추가
	
	동전의 액면 이 a > b > c > d라고 할 때,

	다른 동전을 추가하는 방법 중 최소 횟수를 만드는

	kb > a 인 k (a를 선택할 수 있는 상황에서 a를 선택하지 않고 만드는 최소의 수 k)

	이때, b를 선택하고도 a를 선택할 수 있으면 여전이 greedy 선택한 것과 동일하므로, 
	kb - b <= a 인 최소의 kb를 찾아야 함 ( kb - b = (k - 1)b 임, b >= 1 이므로 kb > a >= (k-1)b인 k는 반드시 존재, a가 무엇이던)

	이때의 최소 횟수인 k 보다 a를 포함해서 매순간 가장 작은 액면을 선택한 것의 합이 작으면
	Yes 만약 최소 횟수 k보다 커지면 No.
*/


int main() {
	int coins;
	cin >> coins;

	for (int i = 0; i < coins; i++) {
		cin >> values[i];
	}

	bool isGreedy = true;

	// 액면 개수만큼 실행
	for (int i = 1; i < coins; i++) {
		int count_ = 0;

		// 다음 액면보다 커지게 하는 첫 count를 구함
		while (count_ * values[i - 1] < values[i]) {
			count_++;
		}

		int val = count_ * values[i - 1];

		// val의 동전 개수를 Greedy로 구함
		int sum = 0;
		for (int k = i; k >= 0; k--) {
			if (val >= values[k]) {
				sum += val / values[k];
				val = val % values[k];
			}
		}

		// 선택하지 않았을 때 가능한 최소 수와 Greedy를 통한 최소 수의 비교
		if (sum > count_) {
			isGreedy = false;
			break;
		}

	}

	if (isGreedy) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}

}