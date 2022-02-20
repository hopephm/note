#include<iostream>
#include<vector>

using namespace std;

#define INF 1234567890

typedef struct Edge{
	int st;
	int ed;
	int cost;
}Edge;

// 벨만포드는 음의 오버플로우가 발생할 수 있다!!!
// 벨만포드는 N-1번 수행, N 번째도 갱신된다면 사이클이 있다는 뜻이다!
long long *bellmanFord(int N, vector<Edge> busInfo){
	long long* dist = new long long[N];
	for(int i = 0; i < N; i++)
		dist[i] = INF;
	dist[0] = 0;

	// N-1 회 반복
	for(int i = 0; i < N; i++){
		for(int j = 0; j < busInfo.size(); j++){
			int st = busInfo[j].st;
			int ed = busInfo[j].ed;
			int cost = busInfo[j].cost;

			if(dist[st] != INF && dist[ed] > dist[st] + cost){
				if(i == N-1) {
					dist[0] = -1;
					break;
				}
				dist[ed] = dist[st] + cost;
			}
		}
	}

	return dist;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, M;
	vector<Edge> busInfo;
	cin >> N >> M;

	for(int i = 0; i < M; i++){
		int st, ed, cost;
		cin >> st >> ed >> cost;
		busInfo.push_back({st-1,ed-1,cost});
	}

	long long* dist = bellmanFord(N, busInfo);

	if(dist[0] == -1)
		cout << -1 << endl;
	else{
		for(int i = 1; i < N; i++){
			if(dist[i] == INF) 
				cout << -1 << endl;
			else
				cout << dist[i] << endl;	
		}
	}

	delete dist;
}