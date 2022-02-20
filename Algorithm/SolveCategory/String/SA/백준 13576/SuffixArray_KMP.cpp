#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<cstdio>

using namespace std;

class Compare{
private:
	const vector<int>& group;
	const int tmp;
public:
	Compare(const vector<int>& _group, const int _tmp): group(_group), tmp(_tmp) {}

	bool operator() (int s1, int s2){
		if(group[s1] != group[s2]) return group[s1] < group[s2];
		return group[s1+tmp] < group[s2+tmp];
	}
};

vector<int> makeSuffixArray(const string& s){
	int n = s.size();
	int tmp = 1;
	vector<int> group(n+1);
	vector<int> suffixArray(n);

	group[n] = -1;

	for(int i = 0; i < n; i++){
		suffixArray[i] = i;
		group[i] = s[i];
	}

	while(tmp < n){
		Compare c(group, tmp);
		sort(suffixArray.begin(), suffixArray.end(), c);

		vector<int> tmpGroup(n+1);
		tmpGroup[n] = -1;
		tmpGroup[suffixArray[0]] = 0;

		for(int i = 1; i < n; i++){
			if(c(suffixArray[i-1], suffixArray[i]))
				tmpGroup[suffixArray[i]] = tmpGroup[suffixArray[i-1]] + 1;
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

	lcp[0] = -1;
	for(int i = 0; i < n; i++)
		rank[suffixArray[i]] = i;

	for(int s1 = 0; s1 < n; s1++){
		int indexOfS1 = rank[s1];

		if(indexOfS1 == 0) continue;

		int s2 = suffixArray[indexOfS1-1];
		while(s[s1 + len] ==  s[s2 + len]) len++;

		lcp[indexOfS1] = len;

		if(len > 0) len--;
	}

	return lcp;
}

vector<int> makePI(const string& s, int n){
	vector<int> pi(n);

	for(int i = 1, j = 0; i < n; i++){
		while(j > 0 && s[i] != s[j])
			j = pi[j-1];
		if (s[i] == s[j]) pi[i] = ++j;
	}

	return pi;
}

int makeCountDP(vector<int>& dp, const vector<int>& suffixArray, const vector<int>& lcp, const int n, int s){
    if (dp[s] != 0) return dp[s];

    dp[s] = 1;
    // 해당 suffix의 등장횟수는 해당 suffix 길이보다 큰 lcp가 몇번 등장하냐에 의해 결정
    int strLength = n - suffixArray[s];

    for (int i = s + 1; i < n; i++) {
        if (lcp[i] >= strLength) {
        	// 일치하는 만큼 글자의 길이가 더 길어지기 때문에 가능
            dp[s] += makeCountDP(dp, suffixArray, lcp, n, i);
            // 해당 위치까지는 이미 검사가 되어있기 때문
            i += dp[i] - 1;
        } // 더 이상 긴 값이 안나오면 앞으로도 안나옴 (lcp의 특성상)
        else break;
    }

    return dp[s];
}

vector<pair<int,int>> solveQuestion(const vector<int>& suffixArray, const vector<int>& lcp, const string& s){
	int n = s.size();
	vector<pair<int,int>> rst;

	vector<int> rank(n);
	vector<int> pi;
	vector<int> countDp(n);

	for(int i = 0; i < n; i++) rank[suffixArray[i]] = i;

	// KMP pi 배열 계산
	pi = makePI(s, n);
	
	// 각 suffix 등장횟수 계산
	for(int i = 0; i < n; i++)
		makeCountDP(countDp, suffixArray, lcp, n, i);

	// pi배열 재귀 호출 + rst에 push
	int num = n;
	while(num != 0){
		rst.push_back({num,countDp[rank[n - num]]});
		num = pi[num-1];
	}

	return rst;
}

int main(){
	//ios_base::sync_with_stdio(false);
	//cin.tie(NULL); cout.tie(NULL);

	string s; cin >> s;

	vector<int> sa = makeSuffixArray(s);
	vector<int> lcp = makeLCP(sa, s);
	vector<pair<int,int>> rst = solveQuestion(sa,lcp,s);

	/*cout << rst.size() << endl;
	for(int i = rst.size()-1; i >= 0 ; i--){
		cout << rst[i].first << " " <<rst[i].second << endl;
	}*/
    
    printf("%d\n", rst.size());
    for(int i = rst.size()-1; i >= 0; i--)
        printf("%d %d\n", rst[i].first, rst[i].second);
    
}