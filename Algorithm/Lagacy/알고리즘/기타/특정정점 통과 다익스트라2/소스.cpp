#include<iostream>
#include<queue>
#include<vector>

using namespace std;

#define INF 200000000
#define v_Max 801

int v;

vector<pair<int, int>> graph[v_Max];

int dijkstra(int start, int end) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
	int dist[v_Max];
	for (int i = 1; i <= v; i++) {
		dist[i] = INF;
	}

	int v, d, distance_, t_v;

	dist[start] = 0;

	Q.push({ dist[start], start });

	while (!Q.empty()) {
		v = Q.top().second;
		d = Q.top().first;
		Q.pop();
		
		for (int i = 0; i < graph[v].size();i++) {
			distance_ = d + graph[v][i].first;
			t_v = graph[v][i].second;

			if (distance_ < dist[t_v]) {
				dist[t_v] = distance_;
				Q.push({ dist[t_v], t_v });
			}
		}
	}


	return dist[end];
}


int main() {
	int e;
	int v1, v2, dis;
	int s_v1, s_v2;
	int d_v1, d_v2, d_v1_v2, d_v1_e, d_v2_e;
	int f_dist1, f_dist2, f_dist;

	cin >> v >> e;
	for (int i = 0; i < e; i++) {
		cin >> v1 >> v2 >> dis;
		graph[v1].push_back({ dis, v2});
		graph[v2].push_back({ dis, v1});
	}

	cin >> s_v1 >> s_v2;

	d_v1 = dijkstra(1, s_v1);
	d_v2 = dijkstra(1, s_v2);
	d_v1_v2 = dijkstra(s_v1, s_v2);
	d_v1_e = dijkstra(s_v1, v);
	d_v2_e = dijkstra(s_v2, v);

	f_dist1 = d_v2 + d_v1_v2 + d_v1_e;
	f_dist2 = d_v1 + d_v1_v2 + d_v2_e;

	if (f_dist1 < f_dist2) {
		f_dist = f_dist1;
	}
	else {
		f_dist = f_dist2;
	}


	if (f_dist < INF) {
		printf("%d\n", f_dist);
	}
	else {
		printf("%d\n", -1);
	}

}