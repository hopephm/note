#include<iostream>
#include<vector>
#include<queue>
using namespace std;

#define MAX 100

class Pos{
	public:

	int x, y, h;
	Pos(int _x, int _y, int _h){
		x = _x; y = _y; h = _h;
	}
};

int tomatoBox[MAX][MAX][MAX];
Pos d[6] = {
	Pos(1,0,0),
	Pos(-1,0,0),
	Pos(0,1,0),
	Pos(0,-1,0),
	Pos(0,0,1),
	Pos(0,0,-1)
};

void printBox(int H, int Y, int X){
	for(int h = 0; h < H; h++){
		for(int y = 0; y < Y; y++){
			for(int x = 0; x < X; x++){
				cout.width(3);
				cout.fill(' ');
				cout << tomatoBox[h][y][x];
			}
			cout << endl;
		}
		cout << endl;
	}
}

bool isIn(int H, int Y, int X, Pos p){
	if(p.x >= 0 && p.x < X && p.y >= 0 && p.y < Y && p.h >= 0 && p.h < H) return true;
	else return false;
}

bool isAllRipened(int H, int Y, int X){
	for(int h = 0; h < H; h++)
		for(int y = 0; y < Y; y++)
			for(int x = 0; x < X; x++)
				if (tomatoBox[h][y][x] == 0) return false;

	return true;
}

int getDay(int H, int Y, int X, vector<Pos> tomato){
	queue<pair<Pos, int>> q; // int는 Day를 의미

	int day = 0;

	for(int i = 0; i < tomato.size(); i++)
		q.push({tomato[i], 0});

	while(!q.empty()){
		Pos curPos = q.front().first;
		int curDay = q.front().second;
		q.pop();

		for(int i = 0; i < 6; i++){
			Pos nextPos = Pos(curPos.x + d[i].x, curPos.y + d[i].y, curPos.h + d[i].h);
			int nextDay = curDay + 1;

			if(isIn(H,Y,X, nextPos)){
				if(tomatoBox[nextPos.h][nextPos.y][nextPos.x] == 0){
					q.push({nextPos, nextDay});
					tomatoBox[nextPos.h][nextPos.y][nextPos.x] = 1;

					if (nextDay > day) day = nextDay;
				}
			}
		}
	}

	if(!isAllRipened(H,Y,X)) day = -1;

	return day;
}


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int X, Y, H;
	vector<Pos> tomato;
	cin >> X >> Y >> H;

	for(int h = 0; h < H; h++){
		for(int y = 0; y < Y; y++){
			for(int x = 0; x < X; x++){
				int val; cin >> val;
				tomatoBox[h][y][x] = val;
				if(val == 1) tomato.push_back(Pos(x,y,h));
			}
		}
	}

	int day = getDay(H,Y,X,tomato);

	cout << day << endl;
}