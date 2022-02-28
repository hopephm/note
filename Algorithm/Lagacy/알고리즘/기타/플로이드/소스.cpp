#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int noc, nob;

int cost[100][100];
int dist[100][100];
bool visited[100][100];

void BFS() {
	queue<int> Q;
	Q.push(0);

	int temp;
	while (!Q.empty()) {
		temp = Q.front(); Q.pop();
		for (int i = 0; i < noc; i++) {
			if (cost[temp][i] != 0 && visited[temp][i] == false) {
				//현재가지고 dist의 비용값 보다 이전까지의 비용값 + 방금 간선의 비용이 더 작다면 교체해줌 그리고 push
			}
		}
	}
}


void init() {
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			visited[i][j] = false;
		}
	}
}

int main() {
	int c1, c2, cost_;

	cin >> noc;
	cin >> nob;

	for (int i = 0; i < noc; i++) {
		for (int j = 0; j < noc; j++) {
			cost[i][j] = 0;
			dist[i][j] = 0;
		}
	}

	for (int i = 0; i < nob; i++) {
		cin >> c1 >> c2 >> cost_;
		cost[c1][c2] = cost_;
	}

	cost[0][0] = 0;

	BFS();
}