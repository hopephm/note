// Visited를 언제 사용하느냐에 따라 메모리 할당이 달라질 수 있다.

#include<iostream>
#include<queue>

using namespace std;

#define MAX_MN 50

bool cabbageMap[MAX_MN][MAX_MN];
bool groupMap[MAX_MN][MAX_MN];

int d[4][2] = {
	{0,1}, {0,-1}, {1, 0}, {-1, 0}
};


void init(int M, int N){
	for(int i = 0; i < N; i++){		
		for(int j = 0; j < M; j++){
			cabbageMap[i][j] = false;
			groupMap[i][j] = false;
		}
	}
}

bool isIn(int M, int N, int x, int y){
	if(x >= 0 && x < M && y >= 0 && y < N)
		return true;
	else 
		return false;
}

void checkSameGroup(int M, int N, int x, int y, int groupCount){
	queue<pair<int, int>> q;

	q.push({x, y});
	groupMap[y][xZ] = true;

	while(!q.empty()){
		int curX = q.front().first;
		int curY = q.front().second;
		q.pop();

		for(int i = 0; i < 4; i++){
			int nextX = curX + d[i][0];
			int nextY = curY + d[i][1];

			if(isIn(M, N, nextX, nextY)){
				if(groupMap[nextY][nextX] == false && cabbageMap[nextY][nextX] == true){
					q.push({nextX, nextY});
					groupMap[nextY][nextX] = true;
				}
			}
		}
	}
}

int getGroupNo(int M, int N){
	int groupCount = 0;

	for(int y = 0; y < N; y++)
		for(int x = 0; x < M; x++)
			if(groupMap[y][x] == false && cabbageMap[y][x] == true)
				checkSameGroup(M, N, x, y, ++groupCount);

	return groupCount;
}

void printCabbageMap(int M, int N){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			if (cabbageMap[i][j] == false) cout << 0;
			if (cabbageMap[i][j] == true) cout << 1;
		}
		cout << endl;
	}
}

void printGroupMap(int M, int N){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			if (groupMap[i][j] == false) cout << 0;
			if (groupMap[i][j] == true) cout << 1;
		}
		cout << endl;
	}
}


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int testcase;
	cin >> testcase;

	for(int t = 0; t< testcase; t++){
		int M, N, K;
		int groupNo = 0;
		cin >> M >> N >> K;

		init(M, N);

		for(int k = 0; k < K; k++){
			int x, y; cin >> x >> y;
			cabbageMap[y][x] = true;
		}

		groupNo = getGroupNo(M, N);

		cout << groupNo << endl;
	}
}