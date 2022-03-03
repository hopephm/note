#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

#define maxN 10

int nutrients[maxN][maxN];
int add_nutrients[maxN][maxN];
vector<int> tree[maxN][maxN];

int N, M, K;

void simulator() {
	// spring
	int to_nutrients[maxN][maxN];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			to_nutrients[i][j] = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int dead = 0;

			for (int k = tree[i][j].size() - 1; k >= 0; k--) {
				if (nutrients[i][j] >= tree[i][j][k]) {
					nutrients[i][j] -= tree[i][j][k];
					tree[i][j][k]++;
				}
				else {
					to_nutrients[i][j] += tree[i][j][k] / 2;
					dead++;
				}
			}

			tree[i][j].erase(tree[i][j].begin(), tree[i][j].begin() + dead);
		}
	}

	// summer
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			nutrients[i][j] += to_nutrients[i][j];
		}
	}

	// fall
	int to_tree[maxN][maxN];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			to_tree[i][j] = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < tree[i][j].size(); k++) {
				if (tree[i][j][k] % 5 == 0) {
					if (i + 1 < N)
						to_tree[i + 1][j]++;
					if (i - 1 >= 0)
						to_tree[i - 1][j]++;
					if (j + 1 < N)
						to_tree[i][j + 1]++;
					if (j - 1 >= 0)
						to_tree[i][j - 1]++;

					if (i - 1 >= 0 && j - 1 >= 0)
						to_tree[i - 1][j - 1]++;
					if (i - 1 >= 0 && j + 1 < N)
						to_tree[i - 1][j + 1]++;
					if (i + 1 < N && j - 1 >= 0)
						to_tree[i + 1][j - 1]++;
					if (i + 1 < N && j + 1 < N)
						to_tree[i + 1][j + 1]++;

				}
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < to_tree[i][j]; k++) {
				tree[i][j].push_back(1);
			}
		}
	}

	// winter
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			nutrients[i][j] += add_nutrients[i][j];
		}
	}

}

int get_trees() {
	int sum = 0;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			sum += tree[i][j].size();

	return sum;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M >> K;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			nutrients[i][j] = 5;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> add_nutrients[i][j];
		}
	}

	for (int i = 0; i < M; i++) {
		int x, y, year;
		cin >> x >> y >> year;
		tree[x - 1][y - 1].push_back(year);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			sort(tree[i][j].begin(), tree[i][j].end(), greater<int>());
		}
	}

	for (int i = 0; i < K; i++) {
		simulator();
	}

	cout << get_trees() << endl;
}
