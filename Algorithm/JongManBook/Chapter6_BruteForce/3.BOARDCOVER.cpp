#include<iostream>
#include<string>

using namespace std;

// 1. 입력처리
// 2. 4가지 모양 처리
typedef struct pos{
	int x;
	int y;
}pos;

pos shape[4][2] = {
	//   □            □            □□           □□
	// □□            □□            □           □
	{{0, 1},{-1,1}}, {{0,1}, {1, 1}}, {{1,0}, {1,1}}, {{0,1}, {1,0}}
};

void printMap(char **map, int H, int W){
	for(int i = 0; i < H; i++){
		for(int j = 0; j < W; j++) cout << map[i][j];
		cout << endl;
	}
}

bool putBlock(char **map, pos cur, int shapeNum, int H, int W){
	pos p[3];

	p[0] = cur;
	for(int i = 0; i < 2; i++){
		p[i+1].x = cur.x + shape[shapeNum][i].x;
		p[i+1].y = cur.y + shape[shapeNum][i].y;
	}

	for(int i = 0; i < 3; i++){
		int X = p[i].x, Y = p[i].y;

		if(X < 0 || X >= W || Y < 0 || Y >= H) return false;
		else if(map[Y][X] != '.') return false;
	}

	for(int i = 0; i < 3; i++){
		int X = p[i].x, Y = p[i].y;
		map[Y][X] = 'B';
	}

	return true;
}

void removeBlock(char **map, pos cur, int shapeNum){
	pos p[3];

	p[0] = cur;
	for(int i = 0; i < 2; i++){
		p[i+1].x = cur.x + shape[shapeNum][i].x;
		p[i+1].y = cur.y + shape[shapeNum][i].y;
	}

	for(int i = 0; i < 3; i++){
		int X = p[i].x, Y = p[i].y;
		map[Y][X] = '.';
	}
}

pos findTopLeft(char **map, int H, int W){
	for(int i = 0 ; i < H; i++)
		for(int j = 0; j < W; j++)
			if(map[i][j] == '.') return {j, i};

	return {-1,-1};
}

int simulation(char **map, pos cur, int H, int W){
	int result = 0;

	for(int k = 0; k < 4; k++){
		if(putBlock(map, cur, k, H, W)){
			pos topLeftPos = findTopLeft(map, H, W);

			if(topLeftPos.x == -1) result++;
			else result += simulation(map, topLeftPos, H, W);

			removeBlock(map, cur, k);
		}
	}

	return result;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int testCase; cin >> testCase;

	for(int tc = 0; tc < testCase; tc++){
		int H, W; cin >> H >> W;
		int space = 0;
		char **map = new char*[H];
		for(int i = 0; i < H; i++)
			map[i] = new char[W];

		for(int i = 0; i <H; i++){
			string tmp; cin >> tmp;
			for(int j = 0; j < W; j++){
				map[i][j] = tmp[j];
				if(map[i][j] == '.') space++;
			}
		}


		if(space%3 != 0) cout << 0 << endl;
		else {
			pos stPos = findTopLeft(map, H, W);
			cout << simulation(map, stPos, H, W) << endl;
		}

		delete[] map;
	}
}
