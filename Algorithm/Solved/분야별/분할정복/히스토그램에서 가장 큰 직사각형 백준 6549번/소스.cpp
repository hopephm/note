#include<iostream>
#include<algorithm>
using namespace std;

/*
	1. 직사각형을 반으로 계속 나눔
	2. 직사각형이 크기가 1 이되면 최대 넓이 반환
	3. 병합시, 각 부분문제의 넓이를 받아옴
	4. 마지막으로 중간부분의 넓이 구함 (중간으로 부터 늘려감)
*/

#define MAX 100000

long long Graph[MAX];

// 각 부분문제에서 가장 큰 직사각형 반환
// 병합시 중간부분 확인

long long Solve(int st_pt, int ed_pt) {

	//1. 기저조건 : 크기가 1이라면 현재 높이 그대로 반환
	if (st_pt == ed_pt) {
		return Graph[st_pt];
	}

	//2. 분할조건 : 중간 값으로 호출
	long long MAX_val = 0;
	long long left_val = 0, right_val = 0;
	int center = (st_pt + ed_pt) / 2;
	
	left_val = Solve(st_pt, center);
	right_val = Solve(center + 1, ed_pt);

	MAX_val = max(left_val, right_val);

	//3. 병합조건 : 각 부분의 MAX값을 받아온뒤, 현재 중앙부터 늘려가며 넓이 계산
	int left_p = center;
	int right_p = center + 1;
	long long min_Height = min(Graph[left_p], Graph[right_p]);

	MAX_val = max(MAX_val, (right_p - left_p + 1) * min_Height);

	while (left_p - 1 >= st_pt || right_p + 1 <= ed_pt) {
		if (left_p - 1 >= st_pt && right_p + 1 <= ed_pt) {
			if (Graph[right_p + 1] > Graph[left_p - 1]) right_p++;
			else left_p--;
		}
		else if (left_p - 1 >= st_pt) left_p--;
		else if (right_p + 1 <= ed_pt) right_p++;

		min_Height = min(min_Height, Graph[left_p]);
		min_Height = min(min_Height, Graph[right_p]);

		MAX_val = max(MAX_val, (right_p - left_p + 1) * min_Height);
	}
	
	return MAX_val;
}

int main() {
	int  Graph_size, value;
	cin >> Graph_size;

	while (Graph_size != 0) {
		for (int i = 0; i < Graph_size; i++) {
			cin >> Graph[i];
		}
		cout << Solve(0, Graph_size - 1) << endl;
		cin >> Graph_size;
	}
}