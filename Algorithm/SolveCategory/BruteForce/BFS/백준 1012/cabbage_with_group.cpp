#include<iostream>
#include<vector>
#include<queue>

using namespace std;

#define MAX_MN 50

bool cabbageMap[MAX_MN][MAX_MN];
int groupMap[MAX_MN][MAX_MN];

int d[4][2] = {
	{0,1}, {0,-1}, {1, 0}, {-1, 0}
};


void init(int M, int N){
	for(int i = 0; i < N; i++){		
		for(int j = 0; j < M; j++){
			cabbageMap[i][j] = false;
			groupMap[i][j] = 0;
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
	groupMap[y][x] = groupCount;

	while(!q.empty()){
		int curX = q.front().first;
		int curY = q.front().second;
		q.pop();

		for(int i = 0; i < 4; i++){
			int nextX = curX + d[i][0];
			int nextY = curY + d[i][1];

			if(isIn(M, N, nextX, nextY)){
				if(groupMap[nextY][nextX] == 0 && cabbageMap[nextY][nextX] == true){
					q.push({nextX, nextY});
					groupMap[nextY][nextX] = groupCount;
				}
			}
		}
	}
}

int getGroupNo(int M, int N, vector<pair<int,int>> cabbagePos){
	int groupCount = 0;

	for(int i = 0; i < cabbagePos.size(); i++){
		int x = cabbagePos[i].first;
		int y = cabbagePos[i].second;

		if(groupMap[y][x] == 0){
			checkSameGroup(M, N, x, y, ++groupCount);
		}
	}

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
			cout << groupMap[i][j];
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
		vector<pair<int, int>> cabbagePos;

		cin >> M >> N >> K;

		init(M, N);

		for(int k = 0; k < K; k++){
			int x, y; cin >> x >> y;
			cabbagePos.push_back({x,y});

			cabbageMap[y][x] = true;
		}

		groupNo = getGroupNo(M, N, cabbagePos);

		cout << groupNo << endl;
	}
}
