#include<iostream>
#include<queue>
#include<vector>

using namespace std;

#define INF 987654321
#define V_MAX 1000

vector<pair<int, int >> Graph[V_MAX];
priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
int dist[V_MAX];

void Init(int ver) {
	for (int i = 0; i < ver; i++) {
		dist[i] = INF;
	}
}



//시작점에서 끝점까지의 최단거리를 구하는 다익스트라
int dijkstra(int s, int e, int ver) {
	int d, v, t_d, t_v;

	Init(ver);

	dist[s-1] = 0;

	Q.push({ dist[s-1], s-1 });

	while (!Q.empty()) {
		d = Q.top().first;
		v = Q.top().second;
		Q.pop();

		for (int i = 0; i < Graph[v].size(); i++) {
			t_d = d + Graph[v][i].first; // 현재까지 최단거리 + 다음거리
			t_v = Graph[v][i].second; // 연결된 정점

			if (t_d < dist[t_v]) {
				dist[t_v] = t_d;
				Q.push({ dist[t_v] , t_v });
			}
		}
	}

	/*cout << "-----------------------" << endl;
	for (int i = 0; i < ver; i++) {
		cout << "dist[" << i << "] = " << dist[i] << endl;
	}
	cout << "-----------------------" << endl;*/

	return dist[e-1];
}


int main() {
	int v, e;
	int a,b,c;
	int v1, v2;

	cin >> v >> e;

	for (int i = 0; i < e; i++) {
		cin >> a >> b >> c;
		Graph[a - 1].push_back({ c, b - 1 });
		Graph[b - 1].push_back({ c, a - 1 });
	}

	cin >> v1 >> v2;

	int _v1, _v2, v1_v2, vN_e, f_dist;

	_v1 = dijkstra(1, v1, v);
	//cout << "_v1 = " << _v1 << endl;
	_v2 = dijkstra(1, v2, v);
	//cout << "_v2 = " << _v2 << endl;
	v1_v2 = dijkstra(v1, v2, v);
	//cout << "v1_v2 = " << v1_v2 << endl;

	// 언제 -1을 출력해야하징

	if (_v1 > _v2) { // v2하고 더 가깝다는 뜻
		vN_e = dijkstra(v1, v, v);

		f_dist = _v2 + v1_v2 + vN_e;
		//cout << "vN_e = " << vN_e << endl;
		if (f_dist < INF) {
			printf("%d\n", f_dist);
		}
		else {
			printf("%d\n", -1);
		}
	}
	else {
		vN_e = dijkstra(v2, v, v);

		f_dist = _v1 + v1_v2 + vN_e;
		//cout << "vN_e = " << vN_e << endl;
		if (f_dist < INF) {
			printf("%d\n", f_dist);
		}
		else {
			printf("%d\n", -1);
		}
	}
}