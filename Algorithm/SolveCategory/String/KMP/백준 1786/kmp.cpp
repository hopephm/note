#include<iostream>
#include<vector>
#include<string>

using namespace std;

vector<int> makePI(const string& s){
	int n = s.length();
	vector<int> pi(n);

	pi[0] = 0;
	int matched = 0, begin = 1;

	while(begin < n){
		while(s[begin+matched] == s[matched])
			pi[begin+matched-1] = ++matched;

		if(matched == 0) begin++;
		else {
			begin += matched-pi[matched-1];
			matched = pi[matched-1];
		}
	}

	return pi;
}

vector<int> findStrByKmp(const string& s, const string& target){
	int n = s.length();
	int tn = target.length();

	vector<int> idx;
	vector<int> pi = makePI(target);

	int begin = 0, matched = 0;

	while(begin + matched < n){
		while(matched < tn && s[begin+matched] == target[matched]) matched++;

		if(tn == matched) idx.push_back(begin);
		if(matched == 0) begin++;
		else{
			begin += matched - pi[matched-1];
			matched = pi[matched-1];
		}
	}

	return idx;
}


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	string s, target; 
	getline(cin, s);
	getline(cin, target);

	vector<int> rst = findStrByKmp(s, target);

	cout << rst.size() << endl;
	for(int i = 0; i < rst.size(); i++)
		cout << rst[i]+1 << " ";
}