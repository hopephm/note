#include<iostream>
#include<vector>
#include<math.h>
#include<algorithm>

using namespace std;

#define MAX 100

typedef struct EDGE {
	double dist;
	int s;
	int e;
}EDGE;

bool operator<(EDGE e1, EDGE e2) {
	return e1.dist < e2.dist;
}

double GetDist(pair<double,double> P1, pair<double,double> P2) {
	return sqrt((P1.first - P2.first)*(P1.first - P2.first) + (P1.second - P2.second)*(P1.second - P2.second));
}

vector<EDGE> Edges_;
pair<double, double> VER[MAX];
int parent[MAX];

int main() {
	int V;
	
	cin >> V;

	for (int i = 0; i < V; i++) {
		cin >> VER[i].first >> VER[i].second;
	}

	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			Edges_.push_back({GetDist(VER[i], VER[j]), i, j });
		}
	}

	sort(Edges_.begin(), Edges_.end());

	for (int i = 0; i < V; i++) {
		parent[i] = i;
	}

	double D = 0;
	int t_s, t_e;
	for (int i = 0; i < Edges_.size(); i++) {
		t_s = parent[Edges_[i].s];
		t_e = parent[Edges_[i].e];

		if (t_s != t_e) {
			D += Edges_[i].dist;
			if (t_s < t_e) {
				for (int i = 0; i < V; i++) {
					if (parent[i] == t_e) {
						parent[i] = t_s;
					}
				}
			}
			else {
				for (int i = 0; i < V; i++) {
					if (parent[i] == t_s) {
						parent[i] = t_e;
					}
				}
			}
		}
	}

	printf("%.2f\n", D);

}