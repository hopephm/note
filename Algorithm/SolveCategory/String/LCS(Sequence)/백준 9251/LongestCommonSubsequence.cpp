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

int solve(string str1, string str2){
	int X = str1.length()+1;
	int Y = str2.length()+1;
	int** DP = new int*[Y];
	int rst;

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

	rst = DP[Y-1][X-1];

	delete [] DP;

	return rst;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	string str1, str2;
	cin >> str1 >> str2;

	int rst = solve(str1, str2);

	cout << rst << endl;
}