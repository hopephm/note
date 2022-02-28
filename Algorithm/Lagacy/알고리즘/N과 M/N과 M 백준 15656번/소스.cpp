/*#include<iostream>
#include<algorithm>
#include<vector>

#define maxN 7

using namespace std;

int arr[maxN];
int N, M;

void solve(int cur, int d, int depth, vector<int> &buf) {
	if (depth == M) {
		for (int i = 0; i < buf.size(); i++) 
			cout << buf[i] << " ";
		cout << endl;
		return;
	}

	for (int i = cur; i < N; i++) {
		//cout << "arr[" << i << "] - arr[" << cur << "] : " << arr[i] - arr[cur] << " / d : " << d << endl;
		if (arr[i] - arr[cur] == d) {
			buf.push_back(arr[i]);
			solve(i, d, ++depth, buf);
			break;
		}
	}
}

int main() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	sort(arr, arr + N);

	for (int i = 0; i < N; i++) {
		for (int j = i; j < N; j++) {
			vector<int> buf;
			buf.push_back(arr[i]);
			solve(i, arr[j] - arr[i], 1, buf);
		}
	}
}
*/
#include<iostream>
#include<algorithm>
#include<vector>

#define MAX 7

int arr[MAX];
int N, M;

using namespace std;

int buf[MAX];

void solve(int cur) {
	if (cur == M) {
		for (int i = 0; i < M; i++)
			cout << buf[i] << " ";
		cout << "\n";
		return;
	}

	for (int i = 0; i < N; i++) {
		buf[cur] = arr[i];
		solve(cur+1);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	sort(arr, arr + N);

	solve(0);
}