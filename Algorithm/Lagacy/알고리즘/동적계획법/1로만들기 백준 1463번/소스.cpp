/*#include<iostream>
using namespace std;

#define MAX 1000001
int N;

int cache[MAX];
int N_count = 0;

void Init() {
	for (int i = 0; i <= N; i++) {
		cache[i] = -1;
	}
}

int Solve(int Num) {
	
	// 기저사례
	if (Num == 1) {
		cache[Num] = 0;
		return 0;
	}

	// 호출사례 + 메모이제이션
	int temp, min = MAX;

	if (Num % 3 == 0) {
		if (cache[Num / 3] != -1) min = cache[Num / 3];
		else min = Solve(Num / 3);
	}
	if (Num % 2 == 0) {
		if (cache[Num / 2] != -1) temp = cache[Num / 2];
		else temp = Solve(Num / 2);
		if (temp < min) min = temp;
	}
	if (cache[Num - 1] != -1) temp = cache[Num - 1];
	else {
		N_count++;
		temp = Solve(Num - 1);
	}
	if (temp < min) min = temp;
	
	cache[Num] = min + 1;

	return (min + 1);
	// 종료조건
}

int main() {
	cin >> N;
	Init();

	cout << Solve(N) << endl;
}*/



#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 1000001
int cache[MAX];

int main() {
	int N;
	cin >> N;

	cache[0] = 0;  cache[1] = 0;
	for (int Num = 2; Num <= N; Num++) {

		cache[Num] = cache[Num-1] + 1;

		if (Num % 3 == 0) cache[Num]= min(cache[Num], cache[Num / 3] + 1);
		if (Num % 2 == 0) cache[Num]= min(cache[Num], cache[Num / 2] + 1);
	}
	cout << cache[N] << endl;
}