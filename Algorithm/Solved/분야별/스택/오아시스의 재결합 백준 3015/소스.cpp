#include<iostream>
#include<algorithm>
#include<stack>

using namespace std;

#define MAX 500000

struct hinfo {
	int height;
	int num;
};

int N;
int persons[MAX];
stack<hinfo> st;

unsigned long long ans = 0;

void solve() {
	for (int i = 0; i < N; i++) {
		int height = persons[i];
		int same = 1;

		while (!st.empty()) {
			if (st.top().height < height) {
				ans += st.top().num;
				st.pop();
			}
			else if (st.top().height == height) {
				ans += st.top().num;
				same = st.top().num + 1;
				st.pop();
			}
			else if(st.top().height > height){
				ans++;
				break;
			}
		}

		st.push({ height, same });
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; i++) {
		int height;
		cin >> height;
		persons[i] = height;
	}

	solve();

	cout << ans << endl;
}
