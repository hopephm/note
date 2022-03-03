#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int N, M;
int map[101][101];
int dist[101][101];
int dx[4] = { 1, 0, -1, 0 }, dy[4] = { 0, 1, 0, -1 };

typedef struct pt {		//큐에 넣을 간선 구조체
	int dst;		//거리
	int y;
	int x;
}pt;

struct cmp {		//우선 순위 큐에 넣기 위해서 비교 연산 오버라이딩
	bool operator()(pt t, pt u) {
		return t.dst > u.dst;
	}
};

void BFS() {
	priority_queue<pt, vector<pt>, cmp> q;
	q.push({ 0,1,1 });

	while (!q.empty()) {
		pt currPt = q.top();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int mx = currPt.x + dx[i], my = currPt.y + dy[i];
			if (0 < mx && mx <= M && 0 < my && my <= N) {
				if (dist[my][mx] > currPt.dst + map[currPt.y][currPt.x]) {
					dist[my][mx] = currPt.dst + map[currPt.y][currPt.x];
					q.push({ dist[my][mx], my, mx });
				}
			}
		}
	}


}

int main(void) {

	scanf("%d %d", &M, &N);

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++) {
			scanf("%1d", &map[i][j]);
			dist[i][j] = 200;
		}

	dist[1][1] = 0;

	BFS();
	for (int i = 0; i < N; i++) {
		for(int j = 0; j<M; j++)
			printf("%d", dist[N][M]);
		printf("\n");
	}
	

	return 0;
}