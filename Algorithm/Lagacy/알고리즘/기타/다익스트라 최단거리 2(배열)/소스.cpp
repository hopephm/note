#include<iostream>
#include<queue>

using namespace std;

#define MAX 20000
#define INF 100

pair<int,int> Graph[MAX][MAX];
int Dist[MAX];
int Size[MAX];

priority_queue< pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;

void Init(int ver) {
	for (int i = 0; i < ver; i++) {
		Dist[i] = INF;
		Size[i] = 0;
	}
}

void dijkstra(int s) {
	int v, d, t_d, t_v;

	Dist[s] = 0;

	Q.push({ Dist[s], s });

	while (!Q.empty()) {
		d = Q.top().first;
		v = Q.top().second;
		Q.pop();

		for (int i = 0; i < Size[v]; i++) {
			t_d = d + Graph[v][i].first;
			t_v = Graph[v][i].second;
			if (t_d < Dist[t_v]) {
				Dist[t_v] = t_d;
				Q.push({ Dist[t_v], t_v});
			}

		}

	}

}


int main() {
	int v, e, s;
	int v1, v2, d;

	cin >> v >> e >> s;

	Init(v);

	for (int i = 0; i < e; i++) {
		cin >> v1 >> v2 >> d;
		Graph[v1 - 1][Size[v1 - 1]] = { d, v2 - 1  };
		Size[v1 - 1]++;
	}

	dijkstra(s);
}