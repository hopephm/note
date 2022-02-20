#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>

using namespace std;

vector<int> myMakePI(const string& s){
	int n = s.size();
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

vector<int> webMakePI(const string& s){
	int n = s.size();
	vector<int> pi(n);

	for(int i = 1, j = 0; i < n; i++){
		while(j > 0 && s[i] != s[j])
			j = pi[j-1];
		if (s[i] == s[j]) pi[i] = ++j;
	}

	return pi;
}

vector<int> findStrByKmp(const string& s, const string& target){
	int n = s.size();
	int tn = target.size();
	vector<int> idx;
	vector<int> pi = myMakePI(target);

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


void speedTest(){
	srand(time(0));
	string s="";
	for(int i = 0; i < 1000000; i++)
		s += (char)('a'+(rand()%26));

	int st = clock();
	webMakePI(s);
	cout << "web: " << clock() - st << endl;	

	st = clock();
	myMakePI(s);
	cout << "mine: " << clock() - st << endl;
}


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	string s, target; 

	cin >> s >> target; 
	vector<int> rst = findStrByKmp(s, target);

	cout << rst.size() << endl;
	for(int i = 0; i < rst.size(); i++)
		cout << rst[i]+1 << " ";
	cout << endl;
}