#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define maxN 100
#define maxM 4950

int set_num[maxN];

int testcase;

void init() {
	for (int i = 0; i < maxN; i++) {
		set_num[i] = i;
	}
}

int merge(vector< pair<int, int>> friends, int N) {
	// 모든 관계 확인.
	for (int i = 0; i < friends.size()-1; i++) {
		// 발생가능한 모든 조합에 관해 수행
		for (int j = i+1; j < friends.size(); j++) {
			// 각 관계에서 집합이 다른데, 관계가 연결되어 있다면 둘 중 큰 집합을 작은 집합으로 통합
			if (friends[i].first == friends[j].first || friends[i].first == friends[j].second ||
				friends[i].second == friends[j].first || friends[i].second == friends[j].second) {
				int min_set_num = min(set_num[friends[i].first], set_num[friends[j].first]);
				int target_set = max(set_num[friends[i].first], set_num[friends[j].first]);

				for (int k = 0; k < N; k++) {
					if (set_num[k] == target_set) {
						set_num[k] = min_set_num;
					}
				}
			}
		}
	}

	sort(set_num, set_num + N);

	for (int i = 0; i < N; i++) {
		cout << set_num[i] << endl;
	}

	int count = 0;
	int value = -1;
	for (int i = 0; i < N; i++) {
		if (set_num[i] != value) {
			value = set_num[i];
			count++;
		}
	}

	return count;
}

int main() {
	cin >> testcase;

	for (int i = 0; i < testcase; i++) {
		int N, M;
		cin >> N >> M;

		vector< pair<int, int> > friends;

		init();

		for (int i = 0; i < M; i++) {
			int t1, t2;
			cin >> t1 >> t2;
			friends.push_back({ t1, t2 });
			set_num[t1] = min(set_num[t1], set_num[t2]);
			set_num[t2] = min(set_num[t1], set_num[t2]);
		}

		
		//sort(friends.begin(), friends.end());

		merge(friends, N);
		//cout << "#" << i+1 << " ";
		//cout << merge(friends, N) << endl;
	}
}