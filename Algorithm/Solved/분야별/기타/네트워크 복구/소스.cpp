
/////////////////////////////////////////////////////////////////////////////////////////      크루스칼

/*#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define MAX_V 1001

typedef struct com {
	int d;
	int s_com;
	int e_com;
}com;

bool operator<(com c1, com c2) {
	return c1.d < c2.d;
}

vector<com> EDGE;
vector<com> RESULT;
vector<com> OUT;
vector<int> parent;

int main() {
	int V, E;
	int v1, v2, d;

	cin >> V >> E;

	for (int i = 0; i < E; i++) {
		cin >> v1 >> v2 >> d;
		EDGE.push_back({ d, v1 - 1, v2 - 1 });
	}

	sort(EDGE.begin(), EDGE.end());

	for (int i = 0; i < E; i++) {
		parent.push_back(i);
	}

	int t_s, t_e;

	for (int i = 0; i < E; i++) {
		t_s = parent[EDGE[i].s_com];
		t_e = parent[EDGE[i].e_com];

		if (t_s != t_e) {
			RESULT.push_back(EDGE[i]);

			if (t_s < t_e) {
				for (int j = 0; j < E; j++) {
					if (parent[j] == t_e) {
						parent[j] = t_s;
					}
				}
			}
			else {
				for (int j = 0; j < E; j++) {
					if (parent[j] == t_s) {
						parent[j] = t_e;
					}
				}
			}
		}

	}

	for (int i = 0; i < RESULT.size(); i++) {
		if (parent[0] == parent[RESULT[i].s_com] && parent[0] == parent[RESULT[i].e_com]) { // 0과 연결 되어있다는 뜻
			OUT.push_back(RESULT[i]);
		}
	}

	printf("%d\n", OUT.size());

	for (int i = 0; i < OUT.size(); i++) {
		printf("%d %d\n", OUT[i].s_com + 1, OUT[i].e_com + 1);
	}

}*/

/*

/////////////////////////////////////////////////////////////////////////////////////////      프림

#include<iostream>
#include<queue>
#include<vector>

using namespace std;

#define MAX_V 1000
#define INF 2000000000



vector<pair<int, int>> Graph[MAX_V];
int Dist[MAX_V];

pair<int, int> RESULT[MAX_V];

int V, E;

void prim() {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;

	for (int i = 0; i < V; i++) {
		Dist[i] = INF;
	}

	Dist[0] = 0;
	Q.push({ Dist[0], 0 });

	int d, v;
	while (!Q.empty()) {
		d = Q.top().first;
		v = Q.top().second;
		Q.pop();

		for (int i = 0; i < Graph[v].size(); i++) {
			if (Graph[v][i].first < Dist[Graph[v][i].second]) {
				Dist[Graph[v][i].second] = Graph[v][i].first;
				Q.push({ Dist[i], Graph[v][i].second });

				RESULT[Graph[v][i].second].first = v;
				RESULT[Graph[v][i].second].second = Graph[v][i].second;
			}
		}
	}
}


int main() {
	cin >> V >> E;

	int v1, v2, d;
	for (int i = 0; i < E; i++) {
		cin >> v1 >> v2 >> d;

		Graph[v1 - 1].push_back({ d, v2 - 1 });
		Graph[v2 - 1].push_back({ d, v1 - 1 });
	}

	prim();

	int ct = 0;

	for (int i = 1; i < V; i++) {
		printf("%d %d\n", RESULT[i].first+1, RESULT[i].second+1);
	}
}*/

// 다익스트라
/*
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

#define MAX 1000
#define INF 987654321

vector<pair<int, int>> Graph[MAX];
vector<pair<int, int>> RESULT;
int CONNECTED[MAX];
int Dist[MAX];

int V, E;

void dijkstra() {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > Q;

	for (int i = 0; i < V; i++) {
		Dist[i] = INF;
	}

	Dist[0] = 0;
	Q.push({ Dist[0],0 });

	int v, d;
	int t_v, t_d;
	while (!Q.empty()) {
		d = Q.top().first;
		v = Q.top().second;
		Q.pop();
		//cout << v << "정점" << endl;
		for (int i = 0; i < Graph[v].size(); i++) {
			t_d = Graph[v][i].first+d;
			t_v = Graph[v][i].second;

			if (t_d < Dist[t_v]) {
				Dist[t_v] = t_d;
				Q.push({ Dist[t_v], t_v});
				CONNECTED[t_v] = v;
				//cout << "CONNECTED " << v << " : " << t_v << endl;
			}
		}
	}


}

int main() {
	cin >> V >> E;

	int v1, v2, d;

	for (int i = 0; i < E; i++) {
		cin >> v1 >> v2 >> d;

		Graph[v1 - 1].push_back({ d,v2 - 1 });
		Graph[v2 - 1].push_back({ d, v1 - 1 });
	}

	dijkstra();

	for (int i = 1; i < V; i++) {
		if (Dist[i] < INF) {
			RESULT.push_back({ i, CONNECTED[i]});
		}
	}
	printf("%d\n", RESULT.size());


	for (int i = 0; i < RESULT.size(); i++) {
		printf("%d %d\n", RESULT[i].first+1, RESULT[i].second+1);
	}
}
*/