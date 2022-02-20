#include<iostream>
#include<vector>
#include<cstdio>
#include<cstdlib>

using namespace std;

vector<int> makePI(const string& s){
	int n = s.length();
	vector<int> pi(n);

	pi[0] = 0;
	int begin = 1, matched = 0;

	while(begin < n){
		while(s[begin+matched]==s[matched])
			pi[begin+matched-1] = ++matched;

		if(matched==0) begin++;
		else{
			begin += matched - pi[matched-1];
			matched = pi[matched-1];
		}
	}

	return pi;
}

int isIn(const string& s, const string& t){
	int sn = s.length();
	int tn = t.length();

	vector<int> pi;
	int begin = 0, matched = 0;
	int rst = 0;

	pi = makePI(t);

	while(begin+matched < sn){
		while(matched<tn && s[begin+matched] == t[matched]) matched++;

		if(matched == tn){
			rst = 1; break;
		}

		if(matched == 0) begin++;
		else{
			begin += matched - pi[matched-1];
			matched = pi[matched-1];
		}
	}

	return rst;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	string s,t;
	cin >> s >> t;

	int rst = isIn(s,t);

	cout << rst << endl;
}