#include<iostream>
#include<vector>

using namespace std;

#define MAX 10

bool selected[MAX];

void initSelected(int n){
	for(int i = 0; i < n; i++) selected[i] = false;
}

bool isAllMatched(int n){
	for(int i = 0; i < n; i++)
		if(!selected[i]) return false;
	return true;
}

void swapInt(int& n, int& m){
	int tmp;
	tmp = n; n = m; m = tmp;
}

bool checkFriends(vector<pair<int,int>> friends, int s1, int s2){
	for(int i = 0; i < friends.size(); i++){
		if(s1 == friends[i].first)
			if(s2 == friends[i].second)
				return true;
	}
	return false;
}

int getNumOfCase(vector<pair<int,int>> friends, int studentsNum, int st){
	if(isAllMatched(studentsNum))	return 1;

	int result = 0;

	for(int i = st; i < studentsNum-1; i++){
		if(selected[i]) continue;

		for(int j = i+1; j < studentsNum; j++){
			if(selected[j]) continue;

			if(checkFriends(friends, i, j)){
				selected[i] = true; selected[j] = true;
				result += getNumOfCase(friends, studentsNum, i+1);
				selected[i] = false; selected[j] = false;
			}
		}
	}

	return result;
}

int main(){
	ios_base :: sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int testCase;
	cin >> testCase;

	for(int i = 0; i < testCase; i++){
		int studentsNum, pairNum;
		cin >> studentsNum >> pairNum;

		initSelected(studentsNum);

		vector<pair<int,int>> friends;

		for(int j = 0; j < pairNum; j++){
			int s1, s2;
			cin >> s1 >> s2;

			if(s2 < s1) swapInt(s1, s2);

			friends.push_back({s1, s2});
		}

		cout << getNumOfCase(friends, studentsNum, 0) << endl;	
	}
}