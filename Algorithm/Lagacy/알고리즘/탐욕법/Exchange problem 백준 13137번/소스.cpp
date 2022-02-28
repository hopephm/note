#include<iostream>

using namespace std;

#define MAX 100
int values[MAX];

/*
	���� : �ż��� �ʿ��� �� ������ �׸��� ���� ���� �� ���� �׸��� ���� ���� �߰�

	>> �ʿ��� �� ������ �׸��� ���� ���� �� ���� �׸��� ���� �������� �ٸ� ���� �߰�
	
	������ �׸� �� a > b > c > d��� �� ��,

	�ٸ� ������ �߰��ϴ� ��� �� �ּ� Ƚ���� �����

	kb > a �� k (a�� ������ �� �ִ� ��Ȳ���� a�� �������� �ʰ� ����� �ּ��� �� k)

	�̶�, b�� �����ϰ� a�� ������ �� ������ ������ greedy ������ �Ͱ� �����ϹǷ�, 
	kb - b <= a �� �ּ��� kb�� ã�ƾ� �� ( kb - b = (k - 1)b ��, b >= 1 �̹Ƿ� kb > a >= (k-1)b�� k�� �ݵ�� ����, a�� �����̴�)

	�̶��� �ּ� Ƚ���� k ���� a�� �����ؼ� �ż��� ���� ���� �׸��� ������ ���� ���� ������
	Yes ���� �ּ� Ƚ�� k���� Ŀ���� No.
*/


int main() {
	int coins;
	cin >> coins;

	for (int i = 0; i < coins; i++) {
		cin >> values[i];
	}

	bool isGreedy = true;

	// �׸� ������ŭ ����
	for (int i = 1; i < coins; i++) {
		int count_ = 0;

		// ���� �׸麸�� Ŀ���� �ϴ� ù count�� ����
		while (count_ * values[i - 1] < values[i]) {
			count_++;
		}

		int val = count_ * values[i - 1];

		// val�� ���� ������ Greedy�� ����
		int sum = 0;
		for (int k = i; k >= 0; k--) {
			if (val >= values[k]) {
				sum += val / values[k];
				val = val % values[k];
			}
		}

		// �������� �ʾ��� �� ������ �ּ� ���� Greedy�� ���� �ּ� ���� ��
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