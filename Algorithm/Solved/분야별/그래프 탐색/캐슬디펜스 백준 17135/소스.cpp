#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdio.h>
#include<cmath>

using namespace std;

#define MAP_MAX 15

int N, M, D;
int MAP[MAP_MAX][MAP_MAX];
int T_MAP[MAP_MAX][MAP_MAX];

bool is_selected[MAP_MAX];

int killed = 0;

void Init_selected() {
	for (int i = 0; i < M; i++) {
		is_selected[i] = false;
	}
}

void start_game(int ar_info[3]) { 
	
}

void select_archer(int ar_num, int last_ar_location, int ar_info[3]) {
	if (ar_num == 3) {
		start_game(ar_info);
		return;
	}
	for (int i = last_ar_location; i < M; i++) {
		if (!is_selected[i]) {
			is_selected[i] = true;
			ar_info[ar_num] = i;
			select_archer(ar_num + 1, i, ar_info);
			is_selected[i] = false;
		}
	}
}

int main() {
	cin >> N >> M >> D;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%1d", &MAP[i][j]);
		}
	}

	Init_selected();

	int ar_info[3] = { 0,0,0 };
	select_archer(0, 0, ar_info );

	cout << killed << endl;
}