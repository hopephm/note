#include<iostream>
#include<vector>
#include<queue>

using namespace std;

#define INF 200000000

#define MAX_V 1001
#define MAX_E 10001
#define MAX_Interval 1001
#define MAX_K_E 1001

struct k {
	int Vertex;
	int out_time;
};


vector<pair<int, int>> Graph[MAX_V];
int TIME[MAX_V];

int V, E;
int start_, end_, interval, K_E;
struct k K_route[MAX_K_E]; // 첫번째 인자에 교차로명, 두번째 인자에 교차로에 진입하는 시간, 세번째 인자에 교차로에서 나가는 시간

//int K_route[MAX_K_E];
//int K_TIME[MAX_K_E];

int is_K_E(int n) {
	for (int i = 0; i < K_E; i++) {
		if (n == K_route[i].Vertex) {
			return i;
		}
	}
	return -1;
}

void dijkstra(bool is_end) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;

	int t_V, t_T;
	int c_V, c_T;
	int TTT;

	for (int i = 0; i < V; i++) {
		TIME[i] = INF;
	}
	TIME[start_-1] = 0;

	Q.push({ TIME[start_-1],start_-1 });

	while (!Q.empty()) {
		t_T = Q.top().first;
		t_V = Q.top().second;
		Q.pop();

		for (int i = 0; i < Graph[t_V].size(); i++) {
			c_T = t_T + Graph[t_V][i].first;
			c_V = Graph[t_V][i].second;

			if (is_end) {
				if (TTT = is_K_E(c_V)) {
					if (TIME[K_route[TTT - 1].out_time] < c_T) {
						TIME[c_V] = K_route[TTT].out_time;
						Q.push({ TIME[c_V],c_V });

						cout << "in_time(" << K_route[TTT].Vertex << ") : " << K_route[TTT - 1].out_time << endl;
						cout << "out_time(" << K_route[TTT].Vertex << ") : " << K_route[TTT].out_time << endl;
						cout << "Q.push : " << TIME[c_V] << ", " << c_V << endl;
					}
					else if (c_T < TIME[c_V]) {
						TIME[c_V] = c_T;
						Q.push({ TIME[c_V],c_V });
						cout << "Q.push : " << TIME[c_V] << ", " << c_V << endl;
					}
				}
			}
			else {
				if (c_T < TIME[c_V]) {
					TIME[c_V] = c_T;
					Q.push({ TIME[c_V],c_V });
				}
			}
		}
	}
}

int main() {

	int v1, v2, t;

	cin >> V >> E;
	cin >> start_ >> end_ >> interval >> K_E;

	for (int i = 0; i < K_E; i++) {
		cin >> K_route[i].Vertex; 
		K_route[i].Vertex--;
	}

	for (int i = 0; i < E; i++) {
		cin >> v1 >> v2 >> t;

		Graph[v1-1].push_back({ t, v2-1 });
		Graph[v2-1].push_back({ t, v1-1 });
	}

	dijkstra(false);

	for (int i = 0; i < V; i++) {
		cout << TIME[i] << endl;
	}

	for (int i = 0; i < K_E; i++) {
		K_route[i].out_time = TIME[K_route[i].Vertex] + interval;
		cout << K_route[i].Vertex << "도달시간 : " << K_route[i].out_time << endl;
	}

	dijkstra(true);

	cout << TIME[end_-1];



}