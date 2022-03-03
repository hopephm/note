#include<iostream>

using namespace std;

#define MAX 41

// 첫번째에 0의 횟수, 두번째에 1의 횟수 리턴.
pair<int, int> Cache[MAX]; //Cache 0, 1은 공백상태
int N;

// 재귀로 풀어보자.
// 배열 40개로 one과 zero의 호출 횟수를 기억하자.
// 만약 기록되어 있다면 아래를 호출하지 않고 바로 리턴

void Init() {
	for (int i = 0; i < N; i++) {
		Cache[i] = { 0, 0 };
	}
}

pair<int, int> fibot(int num) {
	// 기저 조건
	if (num == 0) {
		return { 1,0 };
	}
	else if (num == 1) {
		return { 0,1 };
	}
	// 탐색조건
	if (Cache[num].first != 0 || Cache[num].second != 0) {
		return Cache[num];
	}
	else {
		pair<int, int> temp1, temp2;
		temp1 = fibot(num - 1);
		temp2 = fibot(num - 2);
		Cache[num] = { temp1.first + temp2.first, temp1.second + temp2.second };
	}
	return Cache[num];
}

int main() {
	int testcase;
	cin >> testcase;

	for (int i = 0; i < testcase; i++) {
		cin >> N;
		Init();
		if (N == 0) cout << 1 << " " << 0 << endl;
		else if (N == 1) cout << 0 << " " << 1 << endl;
		else {
			fibot(N);
			cout << Cache[N].first << " " << Cache[N].second << endl;
		}
	}
}