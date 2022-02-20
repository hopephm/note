#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Compare{
private:
	const vector<int>& group;
	const int tmp;
public:
	Compare(const vector<int>& _group, const int _tmp): group(_group), tmp(_tmp){}
	bool operator() (int s1, int s2){
		if(group[s1] != group[s2]) return group[s1] < group[s2];
		return group[s1+tmp] < group[s2+tmp];
	}	
};

void printSuffixArray(const vector<int>& sa, const string& s){
	for(int i = 0; i < sa.size(); i++)
		cout << s.substr(sa[i], s.length()) << endl;
}

void printVector(const vector<int> v){
	for(int i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	cout << endl;
}

vector<int> makeSuffixArray(const string& s){
	const int n = s.size();
	vector<int> suffixArray(n);
	vector<int> group(n+1);
	int tmp = 1;

	group[n] = -1;
	for(int i = 0; i < n; i++){
		suffixArray[i] = i;
		group[i] = s[i];
	}

	while(tmp < n){
		Compare c(group, tmp);
		sort(suffixArray.begin(), suffixArray.end(), c);

		vector<int> nextGroup(n+1);
		nextGroup[n] = -1;
		nextGroup[suffixArray[0]] = 0;

		for(int i = 1; i < n; i++){
			if(c(suffixArray[i-1], suffixArray[i]))
				nextGroup[suffixArray[i]] = nextGroup[suffixArray[i-1]] + 1;
			else 
				nextGroup[suffixArray[i]] = nextGroup[suffixArray[i-1]];
		}

		group = nextGroup;
		tmp*=2;
	}

	return suffixArray;
}

vector<int> makeLCP(const vector<int>& sa, const string& s, int div){
	const int n = s.size();
	int len = 0;
	vector<int> lcp(n);
	vector<int> rank(n);

	lcp[0] = -1;
	for(int i = 0; i < n; i++) rank[sa[i]] = i;

	for(int i = 0; i < n; i++){
		int noS1 = rank[i];
		if(noS1 == 0) continue;

		// 둘 다 뒷 문자열로 이루어 지면 생략
		if(sa[noS1] >= div && sa[noS1-1] >= div) continue;
		// 둘 다 (앞 문자열 + 뒷 문자열) 로 이루어 지면 생략
		if(sa[noS1] <= div && sa[noS1-1] <= div) continue;

		int j = sa[noS1-1];
		while(s[i+len] == s[j+len]) len++;

		int maxVal = n - min(i, j);

		lcp[noS1] = min(len, maxVal);
		if(len > 0) len--;
	}

	return lcp;
}

pair<int, int> getMaxCommonString(const string& s1, const string& s2){
	// 예외처리를 위한 구분문자, 구분문자가 가장 앞에 와야 함.
	string s = s1 + "%" + s2;

	vector<int> sa = makeSuffixArray(s);
	vector<int> lcp = makeLCP(sa, s, s1.size());

	int maxVal = -1, num = 0;
	for(int i = 0; i < lcp.size(); i++){
		if(lcp[i] > maxVal){
			maxVal = lcp[i];
			num = sa[i];
		}
	}

	return {maxVal, num};
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	string s1, s2;
	cin >> s1 >> s2;

	pair<int,int> rst = getMaxCommonString(s1, s2);

	string s = s1 + "%" + s2;
	cout << rst.first << endl;
	cout << s.substr(rst.second, rst.first) << endl;
}