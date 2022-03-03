#include<iostream>
#include<vector>
#include<queue>

using namespace std;

#define MAX 1000

vector<int> Graph[MAX];
int V, E, Start;

int d_Visited[MAX];
int b_Visited[MAX];

void Init() {
	for (int i = 0; i < V; i++) {
		d_Visited[V] = false;
		b_Visited[V] = false;
	}
	d_Visited[Start - 1] = true;
	b_Visited[Start - 1] = true;
}


void DFS(int V) {
	cout << V+1 << " ";
	for (int i = 0; i < Graph[V].size(); i++) {
		if (!d_Visited[Graph[V][i]]) {
			d_Visited[Graph[V][i]] = true;
			DFS(Graph[V][i]);
		}
	}
}

void BFS(int V) {
	queue<int> Q;
	int current;

	Q.push(V);

	while (!Q.empty()) {
		current = Q.front(); Q.pop();
		cout << current + 1 << " ";
		for (int i = 0; i < Graph[current].size(); i++) {
			if (!b_Visited[Graph[current][i]]) {
				Q.push(Graph[current][i]);
				b_Visited[Graph[current][i]] = true;
			}
		}
	}
}

int main() {

	int V1, V2;

	cin >> V >> E >> Start;

	for (int i = 0; i < E; i++) {
		cin >> V1 >> V2 ;
		Graph[V1 - 1].push_back(V2 - 1);
		Graph[V2 - 1].push_back(V1 - 1);
	}

	Init(); 

	DFS(Start - 1);
	cout << endl;
	BFS(Start - 1);
}