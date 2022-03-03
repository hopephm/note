#include<iostream>
#include<stdio.h>
#include<vector>
using namespace std;

#define MAX 8

bool visited[MAX];
int arr[MAX];
vector<int> value;

int M_count = 0;
int N, M;

void Init() {
	for (int i = 0; i < N; i++) {
		visited[i] = false;
		arr[i] = i;
	}
}

void Print() {
	for (int i = 0; i < value.size(); i++) {
		printf("%d ", value[i] + 1);
	}printf("\n");
}

void Solve() {
	if (M_count == M) {
		Print();
		return;
	}

	for (int i = 0; i < N; i++) {
		if (!visited[i]) {
			value.push_back(i); visited[i] = true; M_count++;
			Solve();
			value.pop_back(); visited[i] = false; M_count--;
		}
	}
}

int main() {
	cin >> N >> M;
	Init();

	Solve();
}