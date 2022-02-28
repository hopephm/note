/*#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<stack>

#define MAX 12

using namespace std;

int Size;
int Sum = 0;
int result = 99999999;

int MAP[MAX][MAX];

pair<int, int> core[MAX];

void Solve(int num) {
	int Data[4] = {
		core[num].first,
		Size - core[num].first - 1,
		core[num].second,
		Size - core[num].second - 1
	};


	for (int i = 0; i < 4; i++) {
		Sum += Data[i]; // �����Ҷ��� �����ְ� ���°����� ��������.

		if (Sum < result) { // �׸��� �ش� �������� �̵��� �����Ҷ�

			if (num < Size - 1) {
				Solve(num + 1);
			}
			else { // �׸��� 4���� ��� �̵��� �Ұ����Ҷ�
				result = Sum; 
			}
		}

		Sum -= Data[i];
	}
}

int main() {
	int Testcase;
	int a, b, c;

	cin >> Testcase;

	for (int k = 0; k < Testcase; k++) {

		cin >> Size;
		int count = 0;

		for (int i = 0; i < Size; i++) {
			for (int j = 0; j < Size; j++) {
				scanf("%1d", &MAP[i][j]);
				if (MAP[i][j] == 1) {
					core[count++] = { i, j };
				}
			}
		}

		Solve(0);

		cout << "#" << k+1 << " " << result << endl;
		
	}
}*/
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>

#define MAX 12

using namespace std;

int Size;
int Sum = 0;
int result = 99999999;

int MAP[MAX][MAX];

pair<int, int> core[MAX];

bool is_possible(int direction, int value) {
	switch (direction) {
	case 1:
		for (int i = 0; i < value; i++) {
			if (MAP[value][i] != 0) {
				return false;
			}
		}
		return true;
	case 2:
		for (int i = Size-1; i > value; i--) {
			if (MAP[value][i] != 0) {
				return false;
			}
		}
		return true;
	case 3:
		for (int i = 0; i < value; i++) {
			if (MAP[i][value] != 0) {
				return false;
			}
		}
		return true;
	case 4:
		for (int i = Size - 1; i > value; i--) {
			if (MAP[i][value] != 0) {
				return false;
			}
		}
		return true;
	}
}

void Solve(int num) {
	int Data[4] = {
		core[num].first,
		Size - core[num].first - 1,
		core[num].second,
		Size - core[num].second - 1
	};

	for (int i = 0; i < 4; i++) {
		if (is_possible(i, Data[i])) {
			
		}
	}


}

int main() {
	int Testcase;
	int a, b, c;

	cin >> Testcase;

	for (int k = 0; k < Testcase; k++) {

		cin >> Size;
		int count = 0;

		for (int i = 0; i < Size; i++) {
			for (int j = 0; j < Size; j++) {
				scanf("%1d", &MAP[i][j]);
				if (MAP[i][j] == 1) {
					core[count++] = { i, j };
				}
			}
		}

		Solve(0);



	}
}