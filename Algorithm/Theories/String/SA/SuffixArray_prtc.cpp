#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// 입력받은 그룹 배열과 tmp로 비교하는 함수 객체
class Comp{
public:
	// 이렇게 const로 생성시 정의 안하면 배열 복사시간이 굉장히 오래걸림..
	Comp(const vector<int>& _group, int _tmp):group(_group), tmp(_tmp){}

	bool operator() (int suffixNum1, int suffixNum2){
		// 현재 글자 그룹 비교, 현재 글자가 같다면 tmp만큼 더한 값의 그룹을 비교
		if(group[suffixNum1] != group[suffixNum2])
			return group[suffixNum1] < group[suffixNum2];
		return group[suffixNum1+tmp] < group[suffixNum2+tmp];
	}

private:
	const vector<int>& group;
	int tmp;
};

void print(vector<int>& sa, string str){
	for(auto& e: sa)
		cout << str.substr(e,str.size()) << endl;
	cout << endl;
}

vector<int> getSuffixArray(const string& s){
	int n = s.size();
	int tmp = 1;

	// 그룹[N]을 가장 작은수로 하여 가장 앞에 오도록 해야 정상 비교 가능
	vector<int> group(n+1);
	group[n] = -1;

	for(int i = 0; i < n; i++)
		group[i] = s[i];

	// 순서를 임의로 초기화 한다 (0 ~ n-1)까지
	vector<int> suffixArray(n);
	for(int i = 0; i < n; i++)
		suffixArray[i] = i;

	// 최대 비교 길이가 문자열 길이를 넘으면 안됨
	while(tmp < n){
		// 일단 suffix Array를 현 그룹에 의해 정렬
		Comp comp(group, tmp);
		sort(suffixArray.begin(), suffixArray.end(), comp);

		vector<int> tmpGroup(n+1);
		tmpGroup[n] = -1;
		tmpGroup[suffixArray[0]] = 0;

		// 다음 그룹을 재지정
		//  >> 현재 문자가 다르면 뒤에 있는 놈이 group 이 다름
		//  >> 현재 문자가 같으면 tmp 뒤의 문자를 비교하여 group 결정
		//     * tmp 비교 갯수만큼은 이미 순서가 검증되어 있기 때문 (해당 tmp만큼 해당 문자를 이미 검증하였으므로)
		for(int i = 1; i < n; i++){
			if(comp(suffixArray[i-1], suffixArray[i]))
				tmpGroup[suffixArray[i]] = tmpGroup[suffixArray[i-1]]+1;
			else 
				tmpGroup[suffixArray[i]] = tmpGroup[suffixArray[i-1]];
		}

		group = tmpGroup;
		tmp *= 2;
	}	

	return suffixArray;
}

vector<int> getLCP(vector<int> suffixArray, const string& str){
	int n = str.size();
	vector<int> rank(n);
	vector<int> lcp(n);
	lcp[0] = -1;

	for(int i = 0; i < n; i++)
		rank[suffixArray[i]] = i;

	int len = 0;

	for(int i = 0; i < n; i++){
		int substr = rank[i];
		// 문자열이 긴 순서대로 진행

		// substr이 전체 문자열이 아닐 때
		if(substr){
			int j = suffixArray[substr-1]; // sa 에서 바로 전 문자열

			// 인접 문자열의 길이 확인
			while(str[j+len] == str[i+len])
				len++;

			lcp[substr] = len;

			// substr은 하나씩 줄어가며 수를 지정해 주므로 len을 줄인다.
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

	for(auto& e : sa)
		cout << e+1 << " ";
	cout << endl;

	for(auto& e : lcp){
		if(e == -1) cout << "x ";
		else cout << e << " ";
	}
	cout << endl;
}