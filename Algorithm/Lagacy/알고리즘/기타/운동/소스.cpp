#include<iostream>

using namespace std;

#define MAX 400
#define INF 2000000000

int V, E;

int Graph[MAX][MAX];

int main() {
	cin >> V >> E;

	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (i == j) {
				Graph[i][j] = 0;
			}
			else {
				Graph[i][j] = INF;
			}
		}
	}

	int v1, v2, d;
	for (int i = 0; i < E; i++) {
		cin >> v1 >> v2 >> d;
		Graph[v1 - 1][v2 - 1] = d;
	}

	for (int k = 0; k < V; k++) {
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {

				if (Graph[i][j] > Graph[i][k] + Graph[k][j] && Graph[i][k] < INF && Graph[k][j]) {
					Graph[i][j] = Graph[i][k] + Graph[k][j];
				}
			}
		}
	}

	int d2 = INF;
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (Graph[i][j] + Graph[j][i] < d2 && Graph[i][j] < INF && Graph[j][i] < INF && i != j ) {
				d2 = Graph[i][j] + Graph[j][i];
			}
		}
	}

	if (d2 >= INF) {
		printf("%d\n", -1);
	}
	else {
		printf("%d\n", d2);
	}

}