#include<iostream>
#include<queue>

using namespace std;

struct pt {
	int x;
	int y;
	int val;
	int dst;
	bool visited;
};

void init(pt **map,int M,int N) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j].visited = false;
			map[i][j].dst = 9999;
		}
	}
	map[0][0].dst = 0;
}

struct cmp {
	bool operator() (pt a, pt b) {
		return a.dst > b.dst;
	}
};

void solve(pt** map, int M, int N) {
	priority_queue<pt,vector<pt>,cmp> Q;
	pt temp;
	Q.push(map[0][0]);
	int dx[4] = { 1,-1,0,0 };
	int dy[4] = { 0,0,1,-1 };

	while (!Q.empty()) {
		temp = Q.top(); Q.pop();

		for (int i = 0; i < 4; i++) {
			if (temp.x + dx[i] >= 0 && temp.x + dx[i] < N && temp.y + dy[i] >= 0 && temp.y + dy[i] < M) {
				if (map[temp.y + dy[i]][temp.x + dx[i]].dst > temp.dst) {
					map[temp.y + dy[i]][temp.x + dx[i]].dst = temp.dst + map[temp.y + dy[i]][temp.x + dx[i]].val;
					map[temp.y + dy[i]][temp.x + dx[i]].visited = false;
				}
				else {
					map[temp.y + dy[i]][temp.x + dx[i]].visited = true;
				}
				if (map[temp.y + dy[i]][temp.x + dx[i]].visited == false) {
					Q.push(map[temp.y + dy[i]][temp.x + dx[i]]);
				}
			}
		}
	}
}


int main() {
	int M, N;
	cin >> M >> N;

	char* line = new char[N];

	pt** map = new pt*[M];
	for (int i = 0; i < M; i++) {
		map[i] = new pt[N];
		cin >> line;
		for (int j = 0; j < N; j++) {
			map[i][j].val = (int)line[j] - 48;
			map[i][j].x = j;
			map[i][j].y = i;
		}
	}

	init(map,M,N);

	solve(map, M, N);

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j].dst;
		}
		cout << endl;
	}


}