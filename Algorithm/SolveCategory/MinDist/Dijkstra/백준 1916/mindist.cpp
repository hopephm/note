#include<iostream>
#include<vector>
#include<queue>

using namespace std;

#define MAX 1001
#define INF 1234567890

struct cmp{
	bool operator()(pair<int,int> a, pair<int, int> b){
		return a.second > b.second;
	}
};

int dijkstra(int N, int S,int E, vector<pair<int,int>> graph[MAX]){
	// first : posNum, second : dist
	priority_queue<pair<int, int> , vector<pair<int,int>>, cmp> pq;
	int dist[MAX]; for(int i = 0; i < N; i++) dist[i] = INF;
	dist[S] = 0;

	pq.push({S, 0});

	while(!pq.empty()){
		int cur = pq.top().first;
		int cost = pq.top().second;
		pq.pop();

		if(dist[cur] < cost) continue;

		for(int i = 0; i < graph[cur].size(); i++){
			int next = graph[cur][i].first;
			int nextDist = cost + graph[cur][i].second;

			if(dist[next] > nextDist){
				dist[next] = nextDist;
				pq.push({next, nextDist});
			}
		}
	}

	return dist[E];
}


// Single Source Min Dist
int main(){
	ios_base::sync_with_stdio(false);
	cout.tie(NULL);
	cin.tie(NULL);

	// first : destination Pos, second : cost
	// vector row : start Pos
	vector<pair<int, int>> graph[MAX];
	int N, M, S, E; cin >> N >> M;
	
	for(int i = 0; i < M; i++){
		int s, e, d; cin >> s >> e >> d;
		graph[s-1].push_back({e-1, d});
	}

	cin >> S >> E;
	S--; E--;

	int minDist = dijkstra(N, S, E, graph);

	cout << minDist << endl;
}
