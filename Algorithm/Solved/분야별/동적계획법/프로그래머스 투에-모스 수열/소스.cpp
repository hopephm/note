#include<iostream>
#include<vector>

using namespace std;

#define MAX_N 101

vector<int> Graph[MAX_N];
int set_info[MAX_N];
int count_[MAX_N] = { 0 };
int n, m;

vector<int> set_size;

int result = 0;

void set(int k) {
	if (k < set_size.size()) {
		for (int i = k+1; i < set_size.size(); i++) {
			result += set_size[k] * set_size[i];
		}
		//cout << result << endl;
		set(k + 1);
	}
}

int main() {

	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		set_info[i] = i;
	}


	int v1, v2;
	for (int i = 0; i < m; i++) {
		cin >> v1 >> v2;
		Graph[v1 - 1].push_back(v2 - 1);
		Graph[v2 - 1].push_back(v1 - 1);
	}

	for (int i = 0; i < n; i++) {
		//각 노드와 노드의 연결성분에 대하여

		for (int j = 0; j < Graph[i].size(); j++) {
			// 연결되어 있는데 두 노드가 집합이 다르다면
			int temp = Graph[i][j];

			if (set_info[i] != set_info[temp]) {
				int tt = set_info[temp];
				int tt2 = set_info[i];
				if (set_info[i] < set_info[temp]) {
					for (int k = 0; k < n; k++) {

						if (tt == set_info[k]) {
							set_info[k] = tt2;
						}
					}
				}
				else {
					for (int k = 0; k < n; k++) {
						if (tt2 == set_info[k]) {
							set_info[k] = tt;
						}
					}
				}
			}

		}
	}


	for (int i = 0; i < n; i++) {
		count_[set_info[i]]++;
	}


	for (int i = 0; i < n; i++) {
		if (count_[i] != 0) {
			set_size.push_back(count_[i]);
		}
	}

	//cout << "size : " << set_size.size() << endl;

	set(0);

	cout << result << endl;


}