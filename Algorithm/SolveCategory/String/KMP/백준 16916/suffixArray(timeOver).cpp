#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Compare{
private:
	const vector<int>& group;
	int tmp;

public:
	Compare(const vector<int>& _group, int _tmp) : group(_group), tmp(_tmp) {}
	bool operator() (int s1, int s2){
		if(group[s1] != group[s2]) return group[s1] < group[s2];
		return group[s1 + tmp] < group[s2 + tmp];
	}
};

vector<int> makeSA(const string& s){
	int n = s.length();
	int tmp = 1;
	vector<int> sa(n);
	vector<int> group(n+1);

	group[n] = -1;
	for(int i = 0; i < n; i++){
		sa[i] = i;
		group[i] = s[i];
	}

	while(tmp < n){
		Compare c(group, tmp);
		sort(sa.begin(), sa.end(), c);

		vector<int> nextGroup(n+1);
		nextGroup[n] = -1;
		nextGroup[sa[0]] = 0;

		for(int i = 1; i < n; i++){
			if(c(sa[i-1], sa[i]))
				nextGroup[sa[i]] = nextGroup[sa[i-1]]+1;
			else
				nextGroup[sa[i]] = nextGroup[sa[i-1]];
		}

		group = nextGroup;
		tmp *= 2;
	}

	return sa;
}

vector<int> makeLCP(const vector<int>& sa, const string& s){
	int n = s.length();
	vector<int> lcp(n, 0);
	vector<int> rank(n);
	int len = 0;

	lcp[0] = -1;
	for(int i = 0; i < n; i++)
		rank[sa[i]] = i;

	for(int i = 0; i < n; i++){
		int noS1 = rank[i];
		if(noS1 == 0) continue;

		int j = sa[noS1-1];
		while(s[i+len] == s[j+len]) len++;

		lcp[noS1] = len;

		if(len > 0) len--;
	}

	return lcp;
}

int isIn(const string& s, const string& t){
	int rst = 0;
	string st = s+'%'+t;
	int n = st.length(), sn = s.length(), tn = t.length();

	vector<int> sa;
	vector<int> lcp;
	vector<int> rank(n);

	sa = makeSA(st);
	lcp = makeLCP(sa, st);

	for(int i = 0; i < n; i++)
		rank[sa[i]] = i;

	if(rank[sn+1]+1 < n &&lcp[rank[sn+1]+1] == tn) rst = 1;

	return rst;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	string s, t;
	cin >> s >> t;

	int rst = isIn(s,t);

	cout << rst << endl;
}