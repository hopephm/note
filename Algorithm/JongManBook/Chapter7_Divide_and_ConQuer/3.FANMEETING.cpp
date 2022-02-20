#include<iostream>
#include<vector>
#include<string>

using namespace std;

// void printNum(vector<int>& num){
// 	for(int i = num.size()-1; i >= 0; i--) cout << num[i];
// 	cout << endl;
// }

// void normalize(vector<int>& num){
// 	num.push_back(0);

// 	for(int i = 0; i < num.size()-1; i++){
// 		if(num[i] >= 10){
// 			num[i+1] += num[i]/10;
// 			num[i] %= 10;
// 		}else if(num[i] < 0){
// 			num[i + 1]--;
// 			num[i]+=10;
// 		}
// 	}

// 	while(num.size()>1 && num.back() == 0) num.pop_back();
// }

void addTo(vector<int>& num1, const vector<int>& num2, int k){
	num1.resize(max(num1.size(), num2.size() + k));
	for(int i = 0; i < num2.size(); i++) num1[i + k] += num2[i];
	// normalize(num1);
}

void subFrom(vector<int>& num1, const vector<int>& num2){
	// 항상 num1 > num2 인 경우에만 호출
	for(int i = 0; i < num2.size(); i++) num1[i] -= num2[i];
	// normalize(num1);
}

// void multTenPowK(vector<int>& num, int K){
// 	num.insert(num.begin(), K, 0);
// }

vector<int> generalMult(const vector<int>& num1, const vector<int>& num2){	
	vector<int> rst(num1.size() + num2.size() +1, 0);

	for(int i = 0; i < num1.size(); i++)
		for(int j = 0; j < num2.size(); j++)
			rst[i+j] += num1[i] * num2[j];

	// normalize(rst);

	return rst;
}

vector<int> karatsuba(vector<int>& num1, vector<int>& num2){
	int an = num1.size(), bn = num2.size();

	if(an < bn) return karatsuba(num2, num1);
	if(an <= 50) return generalMult(num1, num2);

	int halfN = num1.size()/2;
	vector<int> a0(num1.begin(), num1.begin() + halfN);
	vector<int> a1(num1.begin()+halfN, num1.end());
	vector<int> b0(num2.begin(), num2.begin() + min((int)num2.size(), halfN));
	vector<int> b1(num2.begin() + min((int)num2.size(), halfN), num2.end());

	vector<int> z0 = karatsuba(a1, b1);
	vector<int> z2 = karatsuba(a0, b0);

	addTo(a1, a0, 0); addTo(b1, b0, 0);
	vector<int> z1 = karatsuba(a1, b1);
	subFrom(z1, z0); subFrom(z1, z2);

	vector<int> rst;
	addTo(rst, z2, 0);
	// multTenPowK(z1, halfN);
	addTo(rst, z1, halfN);
	// multTenPowK(z0, 2*halfN);
	addTo(rst, z0, 2*halfN);

	return rst;
}

int hug(string members, string fans){
	int rst = 0;
	int memberN = members.length(), fanN = fans.length();

	vector<int> memberNum(memberN,0), fanNum(fanN, 0);
	for(int i = 0; i < memberN; i++)
		if(members[i]=='M') memberNum[i] = 1;
	for(int i = 0; i < fanN; i++)
		if(fans[i]=='M') fanNum[fans.length()-1-i] = 1;

	vector<int> hugCase = karatsuba(memberNum, fanNum);

	for(int i = memberN-1; i < fanN; i++)
		if(hugCase[i] == 0) rst++;
	
	return rst;
}


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int testCase; cin >> testCase;

	for(int tc = 0; tc < testCase; tc++){
		string members, fans;
		cin >> members;
		cin >> fans;

		cout << hug(members, fans) << endl;
	}
}
