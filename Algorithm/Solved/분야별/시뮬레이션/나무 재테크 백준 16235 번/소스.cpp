#include<iostream>
#include<list>

using namespace std;

#define MAX_N 10

struct tree {
	int age;
	bool is_alive;
};

list<tree> TREE[MAX_N][MAX_N]; // ������ ���� ����Ʈ
list<int>::iterator T_it;
int Nutrient[MAX_N][MAX_N];   // ��п� ���� �迭
int add_Nutrient[MAX_N][MAX_N];   // ��п� ���� �迭

int N, M, K; // N : ���� ũ��, M : �ɴ� ���� ��, K : �󸶳� ���� ��?



void Init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			Nutrient[i][j] = 5;
		}
	}
}

void Plant(int x, int y, int age) {
	TREE[x][y].push_front({ age, true });
}

void Spring(){
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!TREE[i][j].empty()) {
				for (list<tree>::iterator it = TREE[i][j].begin(); it != TREE[i][j].end(); it++) {
					if (Nutrient[i][j] - (*it).age >= 0) {
						Nutrient[i][j] -= (*it).age;
						(*it).age++;
					}
					else {
						(*it).is_alive = false;
					}
				}
			}
		}
	}
}

void Summer() {
	list<tree>::iterator T_it; // �ױ� �����ϴ� ����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			bool flag = false;
			if (!TREE[i][j].empty()) {
				T_it = TREE[i][j].end();
				for (list<tree>::iterator it = TREE[i][j].begin(); it != TREE[i][j].end(); it++) {
					if (!(*it).is_alive) {
						if (!flag) {
							flag = true; T_it = it;
						}
						Nutrient[i][j] += (*it).age / 2;
					}
				}
				TREE[i][j].erase(T_it, TREE[i][j].end());
			}
		}
	}
	/*cout << "���� ���� �� ���� ���" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << Nutrient[i][j] << "\t";
		}
		cout << endl;
	}*/

}

int dx[8] = { -1,-1,-1,0,0,1,1,1 };
int dy[8] = { 1,0,-1,1,-1,1,0,-1 };

void Fall() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!TREE[i][j].empty()) {
				for (list<tree>::iterator it = TREE[i][j].begin(); it != TREE[i][j].end(); it++) {
					if ((*it).age % 5 == 0) {
						for (int k = 0; k < 8; k++) {
							if (i + dy[k] >= 0 && i + dy[k] < N && j + dx[k] >= 0 && j + dx[k] < N) {
								Plant(i + dy[k], j + dx[k], 1);
							}
						}
					}
				}
			}
		}
	}
}

void Winter() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			Nutrient[i][j] += add_Nutrient[i][j];
		}
	}
}

void Print() {
	cout << "���� ���� ��" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << TREE[i][j].size() << "\t";
		}
		cout << endl;
	}

	cout << endl;

	cout << "��� �Ѹ� �� ���� ���" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << Nutrient[i][j] << "\t";
		}
		cout << endl;
	}
}

int main() {
	cin >> N >> M >> K;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> add_Nutrient[i][j];
		}
	}

	int x, y, a;
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> a;
		Plant(x - 1, y - 1, a);
	}

	Init();

	//Print();

	for (int i = 0; i < K; i++) {
		Spring();
		Summer();
		Fall();
		Winter();
		//Print();
	}

	int count_ = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			count_ += TREE[i][j].size();
		}
	}

	cout << count_ << endl;

}