#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define MAX 1000

int solveN2(int size, int* value){
	int dp[MAX];
	for(int i = 0; i < size; i++) dp[i] = -1;

	int max = 1;
	dp[0] = 1;

	for(int i = 1; i < size; i++){
		dp[i] = 1;
		for(int j = 0; j < i; j++)
			if(value[i] > value[j] && dp[j] + 1 > dp[i])
				dp[i] = dp[j] + 1;
		if (max < dp[i]) max = dp[i];
	}

	return max;
}

int solveNLogN(int size, int* value){
	vector<int> minValue;	

	if(size >= 1)
		minValue.push_back(value[0]);

	for(int i = 0; i < size; i++){
		if(minValue[minValue.size()-1] < value[i])
			minValue.push_back(value[i]);
		else
			*lower_bound(minValue.begin(), minValue.end(), value[i]) = value[i];
	}

	return minValue.size();
}


int main(){
	int size; cin >> size;
	int value[MAX];
	for(int i = 0; i < size; i++) cin >> value[i];

	// cout << solveN2(size, value) << endl;
		cout << solveNLogN(size, value) << endl;
}


