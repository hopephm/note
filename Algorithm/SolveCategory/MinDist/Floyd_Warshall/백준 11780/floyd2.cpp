#include<iostream>

using namespace std;

#define MAX 100
#define INF 1234567890

int minDist[MAX][MAX];

void init(int N){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if (i == j) minDist[i][j] = 0;
			else minDist[i][j] = INF;
		}
	}
}

void floyd(int N){
	for(int k = 0; k < N; k++)
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				if(minDist[i][k] != INF && minDist[k][j] != INF)
					if(minDist[i][j] > minDist[i][k] + minDist[k][j])
						minDist[i][j] = minDist[i][k] + minDist[k][j];
					
	// 경로 저장 로직만 추가하자
}

void printMinDist(int N){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(minDist[i][j] == INF) cout <<  0 << " ";
			else cout << minDist[i][j] << " ";
		}
		cout << endl;
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, M;
	cin >> N >> M;

	init(N);

	for(int i = 0; i < M; i++){
		int st, ed, cost;
		cin >> st >> ed >> cost;

		if (cost < minDist[st-1][ed-1])
			minDist[st-1][ed-1] = cost;
	}

	floyd(N);

	printMinDist(N);
	
}