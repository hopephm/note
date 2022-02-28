#include<iostream>
#include<queue>
#include<vector>

using namespace std;

#define INF 100000000
#define V_MAX 20000

vector<pair<int, int>> Graph[V_MAX];
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> Q;
int dist[V_MAX];

void Init(int num) {
	for (int i = 0; i < num; i++) {
		dist[i] = INF;
	}
}

void dijkstra(int val) {
	int v, d, distance;
	int t_d, t_v;

	dist[val] = 0;
	Q.push({ dist[val], val});

	while (!Q.empty()) {
		d = Q.top().first;
		v = Q.top().second;
		Q.pop();

		for (int i = 0; i < Graph[v].size(); i++) {
			t_d = Graph[v][i].first;
			t_v = Graph[v][i].second;

			distance = d + t_d;

			if (distance < dist[t_v]) {
				dist[t_v] = distance;
				Q.push({dist[t_v], t_v });
			}
		}

	}
}

int main() {
	int v, e, start;
	int v1, v2, dis;

	cin >> v >> e;
	cin >> start;

	for (int i = 0; i < e; i++) {
		cin >> v1 >> v2 >> dis;
		Graph[v1 - 1].push_back({dis,v2 - 1 });
	}

	Init(v);

	dijkstra(start-1);

	for (int i = 0; i < v; i++) {
		if (dist[i] != INF) printf("%d\n", dist[i]);
		else printf("INF\n");
	}
}