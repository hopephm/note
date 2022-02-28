#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
	int x, y, w, h;
	cin >> x >> y >> w >> h;

	vector<int> min;

	min.push_back(abs(0 - x));
	min.push_back(abs(w - x));
	min.push_back(abs(0 - y));
	min.push_back(abs(h - y));

	sort(min.begin(), min.end());

	cout << min[0];
}