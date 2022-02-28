#include<iostream>

using namespace std;

#define MAX 41

// ù��°�� 0�� Ƚ��, �ι�°�� 1�� Ƚ�� ����.
pair<int, int> Cache[MAX]; //Cache 0, 1�� �������
int N;

// ��ͷ� Ǯ���.
// �迭 40���� one�� zero�� ȣ�� Ƚ���� �������.
// ���� ��ϵǾ� �ִٸ� �Ʒ��� ȣ������ �ʰ� �ٷ� ����

void Init() {
	for (int i = 0; i < N; i++) {
		Cache[i] = { 0, 0 };
	}
}

pair<int, int> fibot(int num) {
	// ���� ����
	if (num == 0) {
		return { 1,0 };
	}
	else if (num == 1) {
		return { 0,1 };
	}
	// Ž������
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