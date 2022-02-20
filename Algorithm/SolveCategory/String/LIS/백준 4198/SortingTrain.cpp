#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define MAX 2000

// 최장 증가수열은 lower_bound,
// 최장 감소수열은 upper_bound, greater<int>(),
// 특정 수를 기준으로 lis lds 구하고 싶다면, begin을 갱신하지 말고 그거보다 작거나 클때만 추가

int solve(int size, int *weight){
	int maxVal = 0;

	for(int j = 0; j < size; j++){
		vector<int> lis; 
		vector<int> lds;

		if(size > 0){
				lis.push_back(weight[j]);
				lds.push_back(weight[j]);
		}

		for(int i = j+1; i < size; i++){
			if(weight[i] > lis[lis.size()-1]) lis.push_back(weight[i]);
			else {
				vector<int>::iterator it = lower_bound(lis.begin(), lis.end(), weight[i]);
				if(it != lis.begin()) *it = weight[i];
			}

			if(weight[i] < lds[lds.size()-1]) lds.push_back(weight[i]);
			else {
				vector<int>::iterator it = upper_bound(lds.begin(), lds.end(), weight[i], greater<int>());
				if(it != lds.begin()) *it = weight[i];
			}
		}

		int pred = lis.size() + lds.size()-1;
		if(maxVal < pred) maxVal = pred;
	}

	return maxVal;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int size; cin >> size;
	int weight[MAX];
	for(int i = 0; i < size; i++) cin >> weight[i];

	cout << solve(size, weight) << endl;
}