#include<iostream>
#include<vector>

using namespace std;

vector<int> makePi(const string& s){
	int n = s.length();
	vector<int> pi(n);

	pi[0] = 0;
	int begin = 1, matched = 0;

	while(begin < n){
		while(s[begin+matched] == s[matched]) 
			pi[begin + matched - 1] = ++matched;

		if(matched == 0) begin++;
		else{
			begin += matched - pi[matched-1];
			matched = pi[matched-1];
		}
	}

	return pi;
}

int getMaxPow(const string& s){
	int n = s.length();
	vector<int> pi = makePi(s);

	int rst = 1;
	int val = pi[n-1];

	if(val >= n/2 && val%(n-val)==0)
		rst += val/(n-val);

	return rst;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	while(true){
		string s; cin >> s;
		if(s[0] == '.') break;

		int rst = getMaxPow(s);
		cout << rst << endl;
	}
}