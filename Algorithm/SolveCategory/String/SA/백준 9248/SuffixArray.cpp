#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Comp{
public:
	Comp(const vector<int>& _group, int _tmp):group(_group), tmp(_tmp){}

	bool operator() (int suffixNum1, int suffixNum2){
		if(group[suffixNum1] != group[suffixNum2])
			return group[suffixNum1] < group[suffixNum2];
		return group[suffixNum1 + tmp] < group[suffixNum2 + tmp];
	}
private:
	const vector<int>& group;
	int tmp;
};

vector<int> getSuffixArray(const string& str){
	int n = str.size();

	vector<int> group(n+1);
	group[n] = -1;
	int tmp = 1;

	for(int i = 0; i < n; i++)
		group[i] = str[i];

	vector<int> suffixArray(n);
	for(int i = 0; i < n; i++)
		suffixArray[i] = i;

	while(tmp < n){
		Comp comp(group, tmp);
		sort(suffixArray.begin(), suffixArray.end(), comp);

		vector<int> tmpGroup(n+1);
		tmpGroup[n] = -1;
		tmpGroup[suffixArray[0]] = 0;

		for(int i = 1; i < n; i++){
			if(comp(suffixArray[i-1], suffixArray[i]))
				tmpGroup[suffixArray[i]] = tmpGroup[suffixArray[i-1]] + 1;
			else
				tmpGroup[suffixArray[i]] = tmpGroup[suffixArray[i-1]];
		}

		group = tmpGroup;
		tmp *= 2;
	}

	return suffixArray;
}


vector<int> getLCP(vector<int>& suffixArray, const string& str){
	int n = str.size();
	vector<int> rank(str.size());
	vector<int> lcp(str.size());
	lcp[0] = -1;

	for(int i = 0; i < n; i++)
		rank[suffixArray[i]] = i;

	int len = 0;

	for(int i = 0; i < n; i++){
		int substr = rank[i];
		if(substr){
			int j = suffixArray[substr-1]; 

			while(str[j+len] == str[i+len])
				len++;

			lcp[substr] = len;

			if(len)
				len--;
		}
	}

	return lcp;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	string str; cin >> str;

	vector<int> sa = getSuffixArray(str);
	vector<int> lcp = getLCP(sa, str);
	int n = str.size();
	for(int i = 0; i < n; i++)
		cout << sa[i]+1 << " ";
	cout << endl;

	cout << "x ";
	for(int i = 1; i < n; i++) 
		cout << lcp[i] << " ";
	cout << endl;

}