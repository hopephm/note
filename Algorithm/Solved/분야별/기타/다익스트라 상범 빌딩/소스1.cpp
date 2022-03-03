#include<iostream>
#include<stack>
#include<vector>

using namespace std;

bool is_linked(vector<int> graph, int num) {
	vector<int>::iterator iter = graph.begin();

	while (iter != graph.end()) {
		if (*iter == num)
			return true;
		iter++;
	}
	return false;
}

void dfs(bool* check, vector<int> *graph,int vertice, stack<int> st) {
	if (vertice == 1) {
		st.push(vertice);
		cout << "1 >> ";
		check[1] = true;
	}
	int temp = st.top();
	st.pop();
	

	for (int i = 0; i < 7; i++) {
		if (check[i] == false && is_linked(graph[temp], i)) {
			st.push(i); check[i] = true;
			cout << i << " >> ";
			dfs(check, graph, i, st);
		}
	}

}

int main(void) {
	stack<int> st;
	vector<int> graph[7];

	graph[1].push_back(2);
	graph[1].push_back(5);
	graph[2].push_back(1);
	graph[2].push_back(3);
	graph[2].push_back(5);
	graph[3].push_back(2);
	graph[3].push_back(4);
	graph[4].push_back(3);
	graph[4].push_back(5);
	graph[4].push_back(6);
	graph[5].push_back(1);
	graph[5].push_back(2);
	graph[5].push_back(4);
	graph[6].push_back(4);

	bool check[7];
	for (int i = 1; i < 7; i++) check[i] = false;

	dfs(check, graph, 1,st);
}