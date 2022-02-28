#define _CRT_SECURE_NO_WARNINGS
#define MAX 21

#include<iostream>

using namespace std;

// tip!! 재귀함수를 사용할때는 중복이 일어나지 않도록 검사한다.
// 이 문제는 나올수 있는 4가지 모양에 대하여 차례로 왼쪽 위부터 채워나가기 위해
// 블럭 모양을 Oo   O   O    Oo  와 같이 채워나갔다.
//             o   oo   oo    o 
// 이렇게 검사하면 이미 검사한 왼쪽위를 다시 검사할 이유가 없어지므로   << 또 마지막까지 더이상 놓을수 있는곳을 찾는 식으로 하였기때문에 따로 검사를 할 필요가 없었다. (기저조건)
// 중복이 일어나지 않는다.

//                                    o  o
// 처음에 틀린이유 : 블럭모양을  oO  oO  Oo   Oo 와 같이하여,
//                                o           o

// 모든 공간이 가득 찼는지 검사하였고, 검사에 대한 시간이 보드판 크기만큼 추가되어 시간이 더 오래걸렸으며,
// 또 공백이 있는 경우에도 계속 검사를 이어나갔기 때문에 그에 대한 시간도 추가되었다.
// 중복에 대한 처리를 하기가 애매했다.


int c, H, W;
int count_ = 0;
char graph[MAX][MAX];

int block[4][2][2] = {
	{{1,0},{0,1}},
	{{0,1},{-1,1}},
	{{1,0},{1,1}},
	{{0,1},{1,1}}
};

bool Cover(int X, int Y, int shape) { // 덮을 수 있다면 덮고 true return 덮을 수 없다면 안덮고 false return
	/*
	cout << "X : " << X << ", Y : " << Y << endl;
	cout << "Y + block[shape][0][1] : " << Y + block[shape][0][1] << ", X + block[shape][0][0] : " << X + block[shape][0][0] << endl;
	cout << "Y + block[shape][1][1] : " << Y + block[shape][1][1] << ", X + block[shape][1][0] : " << X + block[shape][1][0] << endl;
	*/

	if (Y + block[shape][0][1] < H &&  Y + block[shape][1][1] < H && X + block[shape][0][0] >= 0 && X + block[shape][0][0] < W && X + block[shape][1][0] >=0 && X + block[shape][1][0] < W) {
		//cout << "외곽 통과! " << endl;
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

	if (st_X == -1) { // . 을 찾을 수 없다는 것은 모든 점을 덮었다는 뜻이므로 
		count_++;
		return;
	}

	// 해당 점을 어떤모양으로도 덮을 수 없다면 이보다 아래쪽에서는 덮을 수 없으므로 종료되어야 함.
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