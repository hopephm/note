#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

int n;
long long count_ = 0;

long long arr[4][4000];
long long c_d_sums[16000000];

int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	long long temp;
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < 4; i++) {
			cin >> temp;
			arr[i][k] = temp;
		}
	}

	int p = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			c_d_sums[p++] = arr[2][i] + arr[3][j];
		}
	}

	sort(c_d_sums, c_d_sums + p);


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int st = 0;
			int ed = p;
			int mid = (st + ed) / 2;

			int min, max;

			long long b_sum = arr[0][i] + arr[1][j];
			
			long long sum = 0;
			while (st < ed) {
				mid = (st + ed) / 2;

				sum = b_sum +c_d_sums[mid];

				if (sum < 0) {
					st = mid+1;
				}
				else {
					ed = mid;
				}
			}

			min = ed;

			st = 0; ed = p;

			while (st < ed) {
				mid = (st + ed) / 2;

				sum = b_sum + c_d_sums[mid];

				if (sum <= 0) {
					st = mid + 1;
				}
				else {
					ed = mid;
				}
			}

			max = ed;

			//cout << "sum : " << sum << " / max : " << max << "/ min : " << min << endl;

			count_ += (long long)(max - min);
		}
	}


	cout << count_;

}