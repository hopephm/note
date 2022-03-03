#include<iostream>
#include<vector>

using namespace std;

void printPicked(vector<int>& picked) {
	for (int i = 0; i < picked.size(); i++) {
		cout << picked[i] << " ";
	}
	cout << endl;
}

void pick(int n, vector<int>& picked, int toPick) {
	if (toPick == 0) { printPicked(picked); return; }

	int smallest;

	if (picked.empty()) {
		smallest = 0;
	}
	else {
		smallest = picked.back() + 1;
	}

	for (int i = smallest; i < n; i++) {
		picked.push_back(i);
		pick(n, picked, toPick - 1);
		picked.pop_back();
	}
}


int main() {
	int n, m;
	vector<int> picked;

	cin >> n >> m;

	int temp;

	pick(n, picked, m);
}