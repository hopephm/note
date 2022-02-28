#include<iostream>
#include<vector>
#include<string>



using namespace std;

int main() {
	int L,R,C;
	cin >> L >> R >> C;

	bool ***graph = new bool**[L];

	for (int i = 0; i < L; i++) {
		graph[i] = new bool*[R];

		for (int j = 0; j < R; j++) {
			graph[i][j] = new bool[C];

			for (int k = 0; k < C; k++)
				graph[i][j][k] = false;
		}
	}
	
	int start[3], end[3];
	int count = 0;

	for (int i = 0; i < L; i++) {
		for (int j = 0; j < R; j++) {
			string temp;
			cin >> temp;

			for (int k = 0; k < C; k++) {
				if (temp.at(k) == '.') {
					graph[i][j][k] == true;
					count++;
				}
				else if (temp.at(k) == '#') {
					graph[i][j][k] == false;
				}
				else if (temp.at(k) == 'S') {
					graph[i][j][k] == true;
					start[0] = i; start[1] = j; start[2] = k;
					count++;
				}
				else if (temp.at(k) == 'E') {
					graph[i][j][k] == true;
					end[0] = i; end[1] = j; end[2] = k;
					count++;
				}
			}
		}
	}

	vector<int> *graph_ln = new vector<int>[L*R*C];


	//2 3 5
	//2+R*C + C*3 + 5

	for (int i = 0; i < L-1; i++) {
		for (int j = 0; j < R-1; j++) {
			for (int k = 0; k < C-1; k++) {
				if (graph[i][j][k] == true && graph[i + 1][j][k] == true) {
					graph_ln[i].push_back(i + 1);
					graph_ln[i+1].push_back(i);
				}else if (graph[i][j][k] == true && graph[i][j+1][k] == true) {
					graph_ln[i].push_back(i + R);
					graph_ln[i + R].push_back(i);
				}else if (graph[i][j][k] == true && graph[i][j][k+1] == true) {
					graph_ln[i].push_back(i + R * C);
					graph_ln[i + R*C].push_back(i);
				}
			}
		}
	}

	graph_ln[start[0] * R*C + start[1] * C + start[2]]; // 시작점

	graph_ln[end[0] * R*C + end[1] * C + end[2]]; // 끝점

}