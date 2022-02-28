#include<iostream>
#include<stack>

using namespace std;

stack<int> st;

void solve(bool** Graph, bool* visited, int Nation ) {

}

int main() {
	int Testcase;
	int* ANS;
	cin >> Testcase;

	ANS = new int[Testcase];

	for (int n = 0; n < Testcase; n++) {
		int Nation, Airplane;
		cin >> Nation >> Airplane;

		bool* visited = new bool[Nation];
		for (int k = 0; k < Nation; k++)
			visited[k] = false;

		bool **Graph = new bool*[Nation];
		for (int k = 0; k < Nation; k++) 
			Graph[k] = new bool[Nation];
		for (int i = 0; i < Nation; i++)
			for (int j = 0; j < Nation; j++)
				Graph[i][j] = false;

		int x, y;
		for (int k = 0; k < Airplane; k++) {
			cin >> x >> y;
			Graph[x-1][y-1] = true;
			Graph[y-1][x-1] = true;
		}

		ANS[n] = Nation - 1;

		delete[] Graph;
	}

	for (int i = 0; i < Testcase; i++) {
		cout << ANS[i] << endl;
	}
}