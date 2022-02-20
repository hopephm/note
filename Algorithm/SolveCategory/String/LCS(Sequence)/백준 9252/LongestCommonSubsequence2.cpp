#include<iostream>
#include<algorithm>

using namespace std;

void printDP(int **DP, int X, int Y){
	for(int i = 0; i < Y; i++){
		for(int j = 0; j < X; j++)
			cout << DP[i][j] << " ";
		cout << endl;
	}
}

pair<int, string> solve(string str1, string str2){
	int X = str1.length()+1;
	int Y = str2.length()+1;
	int** DP = new int*[Y];
	int rstCount = 0;
	string rstString = "";

	for(int i = 0; i < Y; i++){
		DP[i] = new int[X];
		for(int j = 0; j < X; j++)
			DP[i][j] = 0;
	}

	for(int i = 1; i < Y; i++){
		for(int j = 1; j < X; j++){
			if(str2[i-1] == str1[j-1]){
				DP[i][j] = DP[i-1][j-1] + 1;
			}else{
				DP[i][j] = max(DP[i-1][j], DP[i][j-1]);
			}
		}
	}

	rstCount = DP[Y-1][X-1];
	// int curEptSameCount = 1;
	// for(int i = 1; i < X; i++){
	// 	for(int j = 1; j < Y; j++){
	// 		if(DP[j][i] == curEptSameCount){
	// 			rstString += str2[j-1];
	// 			curEptSameCount++;
	// 			break;
	// 		}
	// 	}
	// }
	// 위와 같이 해도 동작해야할 것 같은데 안되는 이유 : 같은 행을 쓰면 안되니까!!
	// 다른 위치의 문자가 비교된다는 걸 알기 위해 행과 열을 같이 -- 해줘야 한다!
	// 같은 행에서 모두 1, 2가 먼저 발견된다 하더라도 그 두번째 2는 사용할 수 없다
	// 예외 입력 : AABAA, ABA 를 하면 ABA가 나와야 하는데 위와 같이하면 AAA가 나온다

	int y = Y-1, x = X - 1;

	while(x > 0 && y > 0){
		if(DP[y][x] == DP[y-1][x]) y--;
		else if(DP[y][x] == DP[y][x-1]) x--;
		else {
			rstString = str2[y-1] + rstString;
			y--; x--;
		}

	}

	delete [] DP;

	return {rstCount, rstString};
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	string str1, str2;
	cin >> str1 >> str2;

	pair<int,string> rst = solve(str1, str2);

	cout << rst.first << endl;
	if(rst.first > 0) cout << rst.second << endl;
}