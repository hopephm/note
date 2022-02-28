#include<iostream>
#include<vector>

using namespace std;

#define MAX 10

vector<int> FI[MAX];
bool left_[MAX];
int n, m;
int count_ = 0;

void Init() {
	for (int i = 0; i < n; i++) {
		left_[i] = true;
		while (!FI[i].empty()) {
			FI[i].pop_back();
		}
	}
	count_ = 0;
}

bool is_empty_() {
	for (int i = 0; i < n; i++) {
		if (left_[i]) { return false; }
	}
	return true;
}

void pairing() {
	//cout << "pairing 호출 " << endl;
	if (is_empty_()) {
		//cout << "카운트 증가!" << endl;
		count_ += 1;
		return;
	}
	
	int first = 0;
	for (int i = 0; i < n; i++) {
		if (left_[i]) {
			first = i; break;
		}
	}

	//cout << "first : " << first << " size : " << FI[first].size() << endl;

	for (int i = 0; i < FI[first].size(); i++) {
		if (left_[FI[first][i]]) {
			left_[first] = false;
			left_[FI[first][i]] = false;

			pairing();

			left_[first] = true;
			left_[FI[first][i]] = true;
		}
	}
}

int main() {
	int c;

	cin >> c;

	for (int k = 0; k < c; k++) {

		int f1, f2;

		cin >> n >> m;

		Init();

		for (int i = 0; i < m; i++) {
			cin >> f1 >> f2;

			FI[f1].push_back(f2);
			FI[f2].push_back(f1);
		}

		

		pairing();

		cout << count_ << endl;

	}
}