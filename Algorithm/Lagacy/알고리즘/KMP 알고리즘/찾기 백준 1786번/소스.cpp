#include<iostream>
#include<string>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

#define MAX_str 1000000

int* getPi_m3(string P, int PL) {
	int *PI = new int[PL];
	for (int i = 0; i < PL; i++) {
		PI[i] = 0;
	}

	for (int i = 0; i < PL; i++) {
		string cur_P = P.substr(0, i+1);
		//cout << cur_P << ", " << i << endl; 
		for (int j = 0; j < i; j++) {
			string front = cur_P.substr(0, j+1);
			string back = cur_P.substr(i - j, i+1);
			//cout << "front : " << front << " / " << "back : " << back << endl;
			bool is_matched = true;
			for (int k = 0; k < j+1; k++) {
				if (front[k] != back[k]) {
					is_matched = false;
					break;
				}
			}
			if (is_matched) {
				//cout << "matched :" << j+1 << endl;
				PI[i] = j+1;
			}
		}
	}
	
	return PI;
}

int* getPi_m2(string P, int PL) {
	int *PI = new int[PL];
	for (int i = 0; i < PL; i++) {
		PI[i] = 0;
	}

	for (int begin = 1; begin < PL; begin++) {
		int max_matched = PL - begin;
		for (int cur_pos = 0; cur_pos < max_matched; cur_pos++) {
			int compare_pos = begin + cur_pos; 
			int substr_size = begin + cur_pos;

			if (P[compare_pos] != P[cur_pos]) break;

			int matched = cur_pos + 1;
			PI[substr_size] = max(PI[begin + cur_pos], matched);
		}
	}

	return PI;
}

int* getPi_m(string P, int PL) {
	int *PI = new int[PL];
	for (int i = 0; i < PL; i++) {
		PI[i] = 0;
	}

	int begin = 1, matched = 0;

	while (begin + matched < PL) {
		//cout << "begin :" << begin << " / " << "matched : " << matched << endl;
		if (P[begin + matched] == P[matched]) {
			matched++;
			PI[begin + matched - 1] = matched;
		}
		else {
			if (matched == 0) {
				begin++;
			}
			else {
				begin = begin + matched - PI[matched-1];
				matched = PI[matched-1];
			}
		}
	}

	return PI;
}




pair<vector<int>, int> kmp(string T, string P, int TL, int PL, int* PI) {
	vector<int> result;

	int count = 0;
	int begin = 0, matched = 0;

	while (begin <= TL - PL) {
		//cout << "begin :" << begin << " / " << "matched : " << matched << endl;
		if (matched < PL && T[begin + matched] == P[matched]) {
			matched++;
			if (matched == PL) {
				result.push_back(begin);
				count++;
				//matched = 0;
				//begin = begin + matched + 1;
			}
		}
		else {
			if (matched == 0) {
				begin++;
			}
			else {
				begin = begin + matched - PI[matched-1];
				matched = PI[matched-1];
			}
		}

	}

	return { result, count };
}




void print_PI(int *PI, int PL) {
	for (int i = 0; i < PL; i++) {
		cout << "PI[" << i << "] = " << PI[i] << endl;
	}
}

void print_result(vector<int> result) {
	for (int i = 0; i < result.size(); i++) {
		//cout << result[i]+1 << endl;
		printf("%d\n", result[i] + 1);
	}
}

int main() {
	string T, P;

	getline(cin, T);
	getline(cin, P);

	int TL = T.length();
	int PL = P.length();

	//int *t_PI = getPi_m3(P, PL);
	//int *t_PI = getPi_m2(P, PL);
	int *t_PI = getPi_m(P, PL);

	//print_PI(t_PI, PL);

	pair<vector<int>, int> result = kmp(T, P, TL, PL, t_PI);

	cout << result.second << endl;
	print_result(result.first);
}