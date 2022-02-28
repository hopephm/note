#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
#include<stdio.h>

using namespace std;

/*
`	
	1. M가지 치킨집 조합				>> 재귀로 해결
	2. 각 조합의 도시의 치킨거리 구함.	>> BFS로 해결
	3. 최솟값 출력						>> 전역값 t로 해결
	4. 최적화							>> BFS 대신 DFS로 탐색할 거리가 발견한 치킨거리 이상이면 호출 X!

*/

#define N_MAX 50
#define M_MAX 13
#define val_MAX 987654321

typedef struct pos {
	int x; int y;
}pos;

int N, M;
int Graph[N_MAX][N_MAX];
vector<pos> C_House;

pos D[4] = {
	{0,1},{0,-1},{1,0},{-1,0 }
};

int BFS(vector<pos> cur_House) {
	queue<pos> Q;
	int distance[N_MAX][N_MAX];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			distance[i][j] = val_MAX;
		}
	}
	int sum = 0;

	for(int i = 0; i < cur_House.size(); i++) {
		Q.push(cur_House[i]);
		distance[cur_House[i].x][cur_House[i].y] = 0;

		while (!Q.empty()) {
			pos cur = Q.front(); Q.pop();
			for (int j = 0; j < 4; j++) {
				int temp_x = cur.x + D[j].x;
				int temp_y = cur.y + D[j].y;
				if (temp_x >= 0 && temp_x < N && temp_y >= 0 && temp_y < N) {
					if (distance[temp_x][temp_y] > abs(cur_House[i].x - temp_x) + abs(cur_House[i].y - temp_y)) {
						distance[temp_x][temp_y] = abs(cur_House[i].x - temp_x) + abs(cur_House[i].y - temp_y);
						Q.push({ temp_x , temp_y });
					}
				}
			}
		}
	}
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (Graph[i][j] == 1) {
				sum += distance[i][j];
			}
		}
	}

	return sum;
}

int t = val_MAX;
bool checked[M_MAX];

void Solve(int depth, int st_num, vector<pos> to_check) {
	depth++;
	if (depth == M) {
		int value = BFS(to_check);
		if (value < t) {
			t = value;
		}
		return;
	}

	for (int i = st_num+1; i < C_House.size(); i++) {
		if (!checked[i]) {
			checked[i] = true;
			to_check.push_back(C_House[i]);
			Solve(depth, i, to_check);
			to_check.pop_back();
			checked[i] = false;
		}
	}
}


int main() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%1d", &Graph[i][j]);
			if (Graph[i][j] == 2) {
				C_House.push_back({ i, j });
			}
		}
	}

	for (int j = 0; j < C_House.size(); j++) {
		for (int i = 0; i < C_House.size(); i++) {
			checked[i] = false;
		}checked[j] = true;
		vector<pos> to_check;
		to_check.push_back(C_House[j]);
		Solve(0, j, to_check);
	}

	cout << t << endl;
}