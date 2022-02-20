#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Compare{
private:
	const vector<int>& group;
	int tmp;

public:
	Compare(vector<int>& _group, int _tmp):group(_group), tmp(_tmp){}

	bool operator() (int s1, int s2){
		if(group[s1] != group[s2])
			return group[s1] < group[s2];
		return group[s1+tmp] < group[s2+tmp];
	}
};

vector<int> makeSuffixArray(const string& s){
	const int n = s.size();
	int tmp = 1;
	vector<int> group(n+1);
	vector<int> suffixArray(n);

	group[n] = -1;
	for(int i = 0; i < n; i++){
		group[i] = s[i];
		suffixArray[i] = i;
	}

	while(tmp < n){
		Compare c = Compare(group, tmp);
		sort(suffixArray.begin(), suffixArray.end(), c);			

		vector<int> tmpGroup(n+1);
		tmpGroup[n] = -1;
		tmpGroup[suffixArray[0]] = 0;

		for(int i = 1; i < n; i++){
			if(c(suffixArray[i-1], suffixArray[i]))
				tmpGroup[suffixArray[i]] = tmpGroup[suffixArray[i-1]]+1;
			else
				tmpGroup[suffixArray[i]] = tmpGroup[suffixArray[i-1]];	
		}
		
		tmp *= 2;
		group = tmpGroup;
	}	
	
	return suffixArray;
}

vector<int> makeLCP(const vector<int>& suffixArray, const string& s){
	int n = s.size();
	int len = 0;
	vector<int> rank(n);
	vector<int> lcp(n);

	for(int i = 0; i < n; i++)
		rank[suffixArray[i]] = i;

	lcp[0] = 0;

	for(int s1 = 0; s1 < n; s1++){
		int s2num = rank[s1];
		if(s2num == 0) continue;

		int s2 = suffixArray[s2num -1];

		while(s[s1+len] == s[s2+len]) len++;

		lcp[s2num] = len;

		if(len > 0) len--;
	}

	return lcp;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	int n; cin >> n;
	string s; cin >> s;

	vector<int> sa = makeSuffixArray(s); 
	vector<int> lcp = makeLCP(sa, s); 
	
	cout << *max_element(lcp.begin(), lcp.end()) << endl;
}