#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define MAX_V 10001
#define MAX_E 100001
#define INF 2147483647

struct MST {
	int dist;
	int s_v;
	int e_v;
};

vector<MST> EDGE;
vector<int> S;
int parent[MAX_V];

int min_ = INF;
int vertex = 0;

int v, e;

bool operator <(const struct MST &a, const struct MST &b) {
	return a.dist < b.dist;
}

long kruskal() {
	long cost = EDGE[0].dist;

	for (int i = 0; i < v; i++) {
		parent[i] = i;
	}

	if (EDGE[0].s_v < EDGE[0].e_v) {
		parent[EDGE[0].e_v] = parent[EDGE[0].s_v];
	}else {
		parent[EDGE[0].s_v] = parent[EDGE[0].e_v];
	}
	

	for (int i = 0; i < EDGE.size(); i++) {

		int t1 = parent[EDGE[i].s_v];
		int t2 = parent[EDGE[i].e_v];



		if (!(parent[EDGE[i].e_v] == parent[EDGE[i].s_v])) {
			
			if (parent[EDGE[i].s_v] < parent[EDGE[i].e_v]) {
				for (int k = 0; k < v; k++) {
					if (parent[k] == t2) {
						parent[k] = parent[EDGE[i].s_v];
					}
				}
			}
			else {
				for (int k = 0; k < v; k++) {
					if (parent[k] == t1) {
						parent[k] = parent[EDGE[i].e_v];
					}
				}
			}

			cost += EDGE[i].dist;

		}
	}

	return cost;
	
}


int main() {
	int v1, v2, dist;

	cin >> v >> e;

	for (int i = 0; i < e; i++) {
		cin >> v1 >> v2 >> dist;

		EDGE.push_back({ dist, v1-1, v2-1 });
	}

	sort(EDGE.begin(), EDGE.end());

	cout << kruskal() << endl;

}
