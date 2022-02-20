#include<iostream>

using namespace std;

#define MAX_SYNC 5
#define SWITCH_SIZE 10
#define CLOCK_COUNT 16

#define INF 1234567890

typedef struct SwitchButton{
	int syncedClock[MAX_SYNC];
	int syncedSize;
}SwitchButton;

SwitchButton switchButton[SWITCH_SIZE] ={
	{{0, 1, 2}, 3},
	{{3,7,9,11}, 4},
	{{4,10,14,15}, 4},
	{{0,4,5,6,7}, 5},
	{{6,7,8,10,12},5},
	{{0,2,14,15},4},
	{{3,14,15},3},
	{{4,5,7,14,15},5},
	{{1,2,3,4,5},5},
	{{3,4,5,9,13},5}
};

void clickSwitch(int *clocks, int switchNum, int clickNum, bool isGetBack){
	SwitchButton tmpSwitch = switchButton[switchNum];
	int turnHour = 3;
	if(isGetBack) turnHour *= -1;


	for(int i = 0; i < tmpSwitch.syncedSize; i++)
		for(int j = 0; j < clickNum; j++)
			clocks[tmpSwitch.syncedClock[i]] = (clocks[tmpSwitch.syncedClock[i]] + turnHour) % 12;
}

bool isAll_12(int *clocks){
	for(int i = 0 ; i < CLOCK_COUNT; i++)
		if(clocks[i] != 0) return false;
	return true;
}

int simulation(int *clocks, int switchNum, int curClicked){
	if(switchNum >= SWITCH_SIZE){
		if(isAll_12(clocks)) return curClicked;
		else return INF;
	}

	int minClick = INF;
	for(int i = 0; i < 4; i++){
		clickSwitch(clocks, switchNum, i, false);
		minClick = min(minClick ,simulation(clocks, switchNum+1, curClicked + i));
		clickSwitch(clocks, switchNum, i, true);
	}

	return minClick;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int testCase; cin >> testCase;

	for(int tc = 0; tc < testCase; tc++){
		int clocks[CLOCK_COUNT];
		for(int i = 0; i < CLOCK_COUNT; i++) {
			cin >> clocks[i];
			if(clocks[i] == 12) clocks[i] = 0;
		};

		int result = simulation(clocks, 0, 0);

		if(result == INF) cout << -1 << endl;
		else cout << result << endl;
	}
	
}