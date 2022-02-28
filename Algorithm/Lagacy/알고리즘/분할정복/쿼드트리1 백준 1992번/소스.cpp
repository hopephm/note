#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
using namespace std;

#define MAX 64
bool Img[MAX][MAX];
int N;

void Quad_compressing(int size, int start_y, int start_x) {
	bool temp = Img[start_y][start_x];
	bool flag = false;
	int n_size = size / 2;
	
	for (int i = start_y; i < start_y + n_size; i++) {
		for (int j = start_x; j < start_x + n_size; j++) {
			if (Img[i][j] != temp | Img[i][j + n_size] != temp | Img[i+n_size][j] != temp | Img[i+n_size][j+n_size] != temp) {
				cout << "(";
				Quad_compressing(n_size, start_y, start_x);
				Quad_compressing(n_size, start_y, start_x + n_size );
				Quad_compressing(n_size, start_y + n_size , start_x );
				Quad_compressing(n_size, start_y + n_size , start_x + n_size );
				cout << ")";
				flag = true; break;
			}
		}
		if (flag) break;
	}
	if (!flag) {
		if (temp)cout << 1;
		else  cout << 0;
	}
}

int main() {
	int temp;
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%1d", &temp);
			if (temp == 1) Img[i][j] = true;
			else if (temp == 0) Img[i][j] = false;
		}
	}

	Quad_compressing(N, 0, 0);
}