#include<iostream>
#include<string>

using namespace std;

#define MAX 10

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

#define RED -1
#define BLUE -2

#define SUCCESS 10
#define FAIL 11
#define CONTINUE 12

int X, Y;
int mintry = 987654321;

struct ball {
	int x;
	int y;
	char color;
	bool isfalled;
};

void showmap(char map[MAX][MAX]) {
	cout << endl;
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
}

int simulator(char curmap[MAX][MAX], ball &R, ball &B, int direction) {
	ball order[2];
	bool isfirstred;

	ball m[4] = {
		{-1,0}, {1, 0}, {0, -1}, {0, 1}
	};

	// 4방향 우선순위 처리
	if ((direction == LEFT && R.x < B.x) ||
		(direction == RIGHT && B.x < R.x) ||
		(direction == UP && R.y < B.y) ||
		(direction == DOWN && B.y < R.y)) {
		order[0] = R;
		order[1] = B;
		isfirstred = true;
	}
	else {
		order[0] = B;
		order[1] = R;
		isfirstred = false;
	}

	// 각 방향 이동
	for (int i = 0; i < 2; i++) {
		ball& cur = order[i];
		curmap[order[i].y][order[i].x] = '.';

		while (true) {
			char mapval = curmap[cur.y + m[direction].y][cur.x + m[direction].x];

			if (mapval == '.') {
				cur.y += m[direction].y;
				cur.x += m[direction].x;
			}
			else if (mapval == 'O') {
				cur.isfalled = true;
				break;
			}
			else if (mapval == '#' || mapval == 'R' || mapval == 'B') {
				curmap[cur.y][cur.x] = cur.color;
				break;
			}
		}
	}

	// 결과반환
	if (isfirstred) {
		R = order[0];
		B = order[1];

		if (order[1].isfalled) {
			return FAIL;
		}
		else if (order[0].isfalled) {
			return SUCCESS;
		}
		else {
			return CONTINUE;
		}
	}
	else {
		R = order[1];
		B = order[0];

		if (order[0].isfalled) {
			return FAIL;
		}
		else if (order[1].isfalled) {
			return SUCCESS;
		}
		else {
			return CONTINUE;
		}
	}
}

void dfs(char cmap[MAX][MAX], ball R, ball B, int depth) {
	if (depth > 10) {
		return;
	}

	for (int direction = 0; direction < 4; direction++) {
		int result;
		ball tR = R;
		ball tB = B;

		char tmap[MAX][MAX];

		for (int i = 0; i < Y; i++) {
			for (int j = 0; j < X; j++) {
				tmap[i][j] = cmap[i][j];
			}
		}

		result = simulator(tmap, tR, tB, direction);

		if (result == CONTINUE) {
			dfs(tmap, tR, tB, depth + 1);
		}
		else if (result == SUCCESS) {
			if (depth < mintry) {
				mintry = depth;
			}
		}
		// else if(result == FAIL) {} : do nothing and try next direction
	}
}

int main() {
	char map[MAX][MAX];

	cin >> Y >> X;

	ball R, B;

	for (int i = 0; i < Y; i++) {
		string cols;
		cin >> cols;

		for (int j = 0; j < X; j++) {
			if (cols[j] == 'R') {
				R.x = j;
				R.y = i;
				R.color = 'R';
				R.isfalled = false;
			}
			else if (cols[j] == 'B') {
				B.x = j;
				B.y = i;
				B.color = 'B';
				B.isfalled = false;
			}

			map[i][j] = cols[j];
		}
	}

	dfs(map, R, B, 1);
	
	if (mintry == 987654321) {
		cout << -1 << endl;
	}
	else {
		cout << mintry << endl;
	}
	
}