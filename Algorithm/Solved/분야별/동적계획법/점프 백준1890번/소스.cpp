#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdio.h>
using namespace std;

#define MAX 100

int Graph[MAX][MAX];
long long DP[MAX][MAX];

int main() {
	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%1d", &Graph[i][j]);
			DP[i][j] = 0;
		}
	}
	DP[0][0] = 1;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == N - 1 && j == N - 1) break;
			if(i+Graph[i][j] < N) DP[i + Graph[i][j]][j] += DP[i][j];
			if(j+Graph[i][j] < N) DP[i][j + Graph[i][j]] += DP[i][j];
			}
	}

	cout << DP[N - 1][N - 1] << endl;
}

/*
*/