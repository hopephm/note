#include<iostream>
#include<vector>
#include<queue>

using namespace std;

#define MAX 1000

int V, G;
vector<int> Graph[MAX];
vector<int> RESULT;
int indegree[MAX] = { 0 };

void GraphSort() {
	queue<int> Q;

	for (int i = 0; i < V; i++) {
		if (indegree[i] == 0) {
			Q.push(i);
			RESULT.push_back(i);
		}
	}

	int val;
	while (!Q.empty()) {
		val = Q.front();
		Q.pop();

		for (int i = 0; i < Graph[val].size(); i++) {
			indegree[Graph[val][i]]--;
			if (indegree[Graph[val][i]] == 0) {
				Q.push(Graph[val][i]);
				RESULT.push_back(Graph[val][i]);
			}
		}
	}

}


int main() {
	cin >> V >> G;
	int count, temp, before;
	for (int i = 0; i < G; i++) {
		cin >> count;

		cin >> temp;
		for (int j = 1; j < count; j++) {
			before = temp;
			cin >> temp;
			Graph[before - 1].push_back(temp - 1);
			indegree[temp - 1]++;
		}
	}

	GraphSort();

	if (RESULT.size() != V) {
		printf("%d\n",0);
	}
	else {
		for (int i = 0; i < RESULT.size(); i++) {
			printf("%d\n", RESULT[i] + 1);
		}
	}

	/*for (int i = 0; i < V; i++) {
		cout << indegree[i] << endl;
	}*/
}