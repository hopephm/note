#define _CRT_SECURE_NO_WARNINGS
#define MAX 21

#include<iostream>

using namespace std;

// tip!! ����Լ��� ����Ҷ��� �ߺ��� �Ͼ�� �ʵ��� �˻��Ѵ�.
// �� ������ ���ü� �ִ� 4���� ��翡 ���Ͽ� ���ʷ� ���� ������ ä�������� ����
// �� ����� Oo   O   O    Oo  �� ���� ä��������.
//             o   oo   oo    o 
// �̷��� �˻��ϸ� �̹� �˻��� �������� �ٽ� �˻��� ������ �������Ƿ�   << �� ���������� ���̻� ������ �ִ°��� ã�� ������ �Ͽ��⶧���� ���� �˻縦 �� �ʿ䰡 ������. (��������)
// �ߺ��� �Ͼ�� �ʴ´�.

//                                    o  o
// ó���� Ʋ������ : �������  oO  oO  Oo   Oo �� �����Ͽ�,
//                                o           o

// ��� ������ ���� á���� �˻��Ͽ���, �˻翡 ���� �ð��� ������ ũ�⸸ŭ �߰��Ǿ� �ð��� �� �����ɷ�����,
// �� ������ �ִ� ��쿡�� ��� �˻縦 �̾���� ������ �׿� ���� �ð��� �߰��Ǿ���.
// �ߺ��� ���� ó���� �ϱⰡ �ָ��ߴ�.


int c, H, W;
int count_ = 0;
char graph[MAX][MAX];

int block[4][2][2] = {
	{{1,0},{0,1}},
	{{0,1},{-1,1}},
	{{1,0},{1,1}},
	{{0,1},{1,1}}
};

bool Cover(int X, int Y, int shape) { // ���� �� �ִٸ� ���� true return ���� �� ���ٸ� �ȵ��� false return
	/*
	cout << "X : " << X << ", Y : " << Y << endl;
	cout << "Y + block[shape][0][1] : " << Y + block[shape][0][1] << ", X + block[shape][0][0] : " << X + block[shape][0][0] << endl;
	cout << "Y + block[shape][1][1] : " << Y + block[shape][1][1] << ", X + block[shape][1][0] : " << X + block[shape][1][0] << endl;
	*/

	if (Y + block[shape][0][1] < H &&  Y + block[shape][1][1] < H && X + block[shape][0][0] >= 0 && X + block[shape][0][0] < W && X + block[shape][1][0] >=0 && X + block[shape][1][0] < W) {
		//cout << "�ܰ� ���! " << endl;
		if (graph[Y][X] == '.' && graph[Y + block[shape][0][1]][X + block[shape][0][0]] == '.' && graph[Y + block[shape][1][1]][X + block[shape][1][0]] == '.') {
			graph[Y][X] = graph[Y + block[shape][0][1]][X + block[shape][0][0]] = graph[Y + block[shape][1][1]][X + block[shape][1][0]] = 'B';
			return true;
		}
	}
	return false;
}

void remove_Cover(int X, int Y, int shape) {
	graph[Y][X] = graph[Y + block[shape][0][1]][X + block[shape][0][0]] = graph[Y + block[shape][1][1]][X + block[shape][1][0]] = '.';
}

void solve() {

	/*for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			printf("%c", graph[i][j]);
		}
		printf("\n");
	}*/

	int st_X = -1;
	int st_Y = -1;

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (graph[i][j] == '.') {
				st_X = j; st_Y = i; break;
			}
		}
		if (st_X != -1) break;
	}

	if (st_X == -1) { // . �� ã�� �� ���ٴ� ���� ��� ���� �����ٴ� ���̹Ƿ� 
		count_++;
		return;
	}

	// �ش� ���� �������ε� ���� �� ���ٸ� �̺��� �Ʒ��ʿ����� ���� �� �����Ƿ� ����Ǿ�� ��.
	for (int shape = 0; shape < 4; shape++) {
		if (Cover(st_X, st_Y, shape)) {
			solve();
			remove_Cover(st_X, st_Y, shape);
		}
	}
	
}

int main() {
	scanf("%d", &c);
	
	for (int k = 0; k < c; k++) {
		count_ = 0;
		scanf("%d %d", &H, &W);

		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				scanf(" %c", &graph[i][j]);
			}
		}

		bool flag = false;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				if (graph[i][j] == '.') {
					flag = true; break;
				}
			}
			if (flag) break;
		}

		if (flag) {
			solve();
		}
		printf("%d\n", count_);
	}
	
}