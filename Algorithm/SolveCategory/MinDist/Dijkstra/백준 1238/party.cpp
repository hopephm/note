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

int* dijkstra(int N, int S, vector<pair<int,int>> graph[MAX]){
	// first : posNum, second : dist
	priority_queue<pair<int, int> , vector<pair<int,int>>, cmp> pq;
	int* dist = new int[N]; for(int i = 0; i < N; i++) dist[i] = INF;
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

	return dist;
}


// Single Source Min Dist, Single Dest Min Dist
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	vector<pair<int,int>> graph[MAX];
	vector<pair<int,int>> rvsGraph[MAX];
	int N, M, X; cin >> N >> M >> X;

	for(int i = 0; i < M; i++){
		int s, e, c; cin >> s >> e >> c;
		graph[s-1].push_back({e-1, c});
		rvsGraph[e-1].push_back({s-1, c});
	}

	int* goDist = dijkstra(N, X-1, graph);
	int* backDist = dijkstra(N, X-1, rvsGraph);

	int maxCost = -1;
	for(int i = 0; i < N; i++){
		int totalCost = goDist[i] + backDist[i];
		if(maxCost < totalCost) maxCost = totalCost;
	}

	cout << maxCost << endl;

	delete goDist;
	delete backDist;
}