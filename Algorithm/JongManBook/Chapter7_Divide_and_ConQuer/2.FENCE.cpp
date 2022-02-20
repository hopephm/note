#include<iostream>

using namespace std;

#define MAX_FENCE 20000

int getMaxRectangle(int *fence, int st, int end){
	if(end-st <= 1) return fence[st];
	int maxArea = -1;

	int mid = (st+end)/2;
	int leftMaxArea = getMaxRectangle(fence, st, mid);
	int rightMaxArea = getMaxRectangle(fence, mid, end);
	maxArea = max(leftMaxArea, rightMaxArea);

	int left = mid-1, right = mid, fenceCount = 2;
	int minHeight = min(fence[left], fence[right]);
	int midMaxArea = fenceCount*minHeight;

	while(fenceCount < (end-st)){

		if(left == st)
			minHeight = min(minHeight, fence[++right]);
		else if(right == (end-1))
			minHeight = min(minHeight, fence[--left]);
		else{
			// 배열 범위 초과 예외처리
			if (fence[left-1] < fence[right+1]) minHeight = min(minHeight, fence[++right]);
			else minHeight = min(minHeight, fence[--left]);
		}
		
		int curArea = ++fenceCount*minHeight;
		midMaxArea = max(midMaxArea, curArea);
	}

	maxArea = max(maxArea, midMaxArea);	

	return maxArea;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int testCase; cin >> testCase;

	for(int tc = 0; tc < testCase; tc++){
		int N; cin >> N;
		int fence[MAX_FENCE];
		for(int i = 0; i < N; i++) cin >> fence[i];

		cout << getMaxRectangle(fence, 0, N) << endl;
	}
}