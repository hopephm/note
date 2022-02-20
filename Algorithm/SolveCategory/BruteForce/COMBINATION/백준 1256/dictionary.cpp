#include<iostream>

using namespace std;

#define MAX_VAL 1000000000

int getJudgeVal(int curN, int curM){
	double rst = 1;
	int j = 1;
	for (int i = curN; i <= (curN + curM -1); i++)	{
		rst *= (double)((double)i/(double)j);
		j++;

		if(rst >= MAX_VAL){
			rst = MAX_VAL;
			break;
		}
	}

	int rtn = (int)rst;
	if(rst - int(rst) >= 0.5) rtn += 1;

	return rtn;
}

string solve(int curN, int curM, int K, unsigned long long curVal, string &s){
	if (curN <= 0){
		for (int i = 0; i < curM; i++)
			s += "z";
		return s;	
	} 
	else if(curM <= 0){
		for (int i = 0; i < curN; i++)
			s += "a";
		return s;	
	} 

	string rst;
	unsigned long long judgeVal = getJudgeVal(curN, curM);

	if(K <= curVal + judgeVal){
		s += "a";
		solve(curN-1, curM, K, curVal, s);	
	} 
	else if(K > curVal + judgeVal){
		s += "z";
		solve(curN, curM-1, K, curVal+judgeVal, s);
	}

	return s;
}


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, M, K;
	cin >> N >> M >> K;

	int maxK = getJudgeVal(N+1, M);
	if(maxK < K){
		cout << -1 << endl;
	}else{
		string s = "";
		cout << solve(N,M,K,0,s) << endl;	
	}
}