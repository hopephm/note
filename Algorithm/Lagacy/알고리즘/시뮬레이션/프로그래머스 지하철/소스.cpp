#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<algorithm>
#include<stdio.h>

using namespace std;

vector< pair<int, int> > st_s;
vector <pair<int, int> > tr_s;

int main() {
	pair<int, int> cur_time;
	int st_t, tr_t;
	int st, tr;

	scanf("%d:%d", &cur_time.first, &cur_time.second);

	cin >> st_t >> tr_t;
	cin >> st >> tr;

	pair<int, int> temp;

	for (int i = 0; i < st; i++) {
		scanf("%d:%d", &temp.first, &temp.second);
		st_s.push_back(temp);
	}

	for (int i = 0; i < tr; i++) {
		scanf("%d:%d", &temp.first, &temp.second);
		tr_s.push_back(temp);
	}

	sort(st_s.begin(), st_s.end());
	sort(tr_s.begin(), tr_s.end());

	for (int i = 0; i < st_s.size(); i++) {
		if (st_s[i].first == cur_time.first) {

			if (st_s[i].second >= cur_time.second) {

				cur_time.second = st_s[i].second + st_t;

				int flag = 0;

				if (cur_time.second >= 60) {
					flag = cur_time.second / 60;
					cur_time.second = cur_time.second % 60;
				}

				cur_time.first = st_s[i].first + flag;

				break;

			}

		}
		else if (st_s[i].first > cur_time.first) {

			cur_time.second = st_s[i].second + st_t;

			int flag = 0;

			if (cur_time.second >= 60) {
				flag = cur_time.second / 60;
				cur_time.second = cur_time.second % 60;
			}

			cur_time.first = st_s[i].first + flag;
			break;

		}
	}

	for (int i = 0; i < tr_s.size(); i++) {

		if (tr_s[i].first == cur_time.first) {
			if (tr_s[i].second >= cur_time.second) {
				cur_time.second = tr_s[i].second + tr_t;
				int flag = 0;
				if (cur_time.second >= 60) {
					flag = cur_time.second / 60;
					cur_time.second = cur_time.second % 60;
				}
				cur_time.first = tr_s[i].first + flag;
				break;
			}

		}
		else if (tr_s[i].first > cur_time.first) {
			cur_time.second = tr_s[i].second + tr_t;
			int flag = 0;
			if (cur_time.second >= 60) {
				flag = cur_time.second / 60;
				cur_time.second = cur_time.second % 60;
			}
			cur_time.first = tr_s[i].first + flag;
			break;
		}
	}
	if (cur_time.first < 10) {
		cout << "0";
	}
	cout << cur_time.first;

	cout << ":";

	if (cur_time.second < 10) {
		cout << "0";
	}
	cout << cur_time.second;
}


/*#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<algorithm>
#include<stdio.h>

using namespace std;

vector<pair<int, int> > st;
vector<pair<int, int> > tr;

int main() {
	pair<int, int> cur;
	int st_t, tr_t;
	int st_s, tr_s;

	scanf("%d:%d", &cur.first, &cur.second);

	cin >> st_t >> tr_t;
	cin >> st_s >> tr_s;

	int t_h, t_m;
	for (int i = 0; i < st_s; i++) {
		scanf("%d:%d", &t_h, &t_m);
		st.push_back({ t_h, t_m });
	}

	for (int i = 0; i < tr_s; i++) {
		scanf("%d:%d", &t_h, &t_m);
		tr.push_back({ t_h, t_m });
	}

	sort(st.begin(), st.end());
	sort(tr.begin(), tr.end());

	for (int i = 0; i < st.size(); i++) {
		if (st[i].first * 60 + st[i].second >= cur.first * 60 + cur.second) {

			int flag = 0;
			cur.second = st[i].second + st_t;

			if (cur.second >= 60) {
				flag = 1;
				cur.second = cur.second % 60;
			}

			cur.first = st[i].first + flag;

		}

	}

	for (int i = 0; i < tr.size(); i++) {
		if (tr[i].first * 60 + tr[i].second >= cur.first * 60 + cur.second) {

			int flag = 0;
			cur.second = tr[i].second + tr_t;

			if (cur.second >= 60) {
				flag = 1;
				cur.second = cur.second % 60;
			}

			cur.first = tr[i].first + flag;

		}

	}

	cout << cur.first << ":" << cur.second << endl;


}*/