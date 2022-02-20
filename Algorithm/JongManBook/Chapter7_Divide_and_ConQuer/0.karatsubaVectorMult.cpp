#include<iostream>
#include<vector>
#include<time.h>

using namespace std;

void printNum(vector<int>& num){
	for(int i = num.size()-1; i >= 0; i--) cout << num[i];
	cout << endl;
}

void normalize(vector<int>& num){
	num.push_back(0);

	for(int i = 0; i < num.size()-1; i++){
		if(num[i] >= 10){
			num[i+1] += num[i]/10;
			num[i] %= 10;
		}else if(num[i] < 0){
			num[i + 1]--;
			num[i]+=10;
		}
	}

	while(num.size()>1 && num.back() == 0) num.pop_back();
}

void addTo(vector<int>& num1, const vector<int>& num2){
	num1.resize(max(num1.size(), num2.size()));
	for(int i = 0; i < num2.size(); i++) num1[i] += num2[i];
	normalize(num1);
}

void subFrom(vector<int>& num1, const vector<int>& num2){
	// 항상 num1 > num2 인 경우에만 호출
	for(int i = 0; i < num2.size(); i++) num1[i] -= num2[i];
	normalize(num1);
}

void multTenPowK(vector<int>& num, int K){
	num.insert(num.begin(), K, 0);
}

vector<int> generalMult(const vector<int>& num1, const vector<int>& num2){	
	vector<int> rst(num1.size() + num2.size() +1, 0);

	for(int i = 0; i < num1.size(); i++)
		for(int j = 0; j < num2.size(); j++)
			rst[i+j] += num1[i] * num2[j];

	normalize(rst);

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

	addTo(a1, a0); addTo(b1, b0);
	vector<int> z1 = karatsuba(a1, b1);
	subFrom(z1, z0); subFrom(z1, z2);

	vector<int> rst;
	addTo(rst, z2);
	multTenPowK(z1, halfN);
	addTo(rst, z1);
	multTenPowK(z0, 2*halfN);
	addTo(rst, z0);

	return rst;
}



int main(){
	vector<int> num1, num2, rst;

	for(int i = 0; i < 200000; i++) num1.push_back(1);
	for(int i = 0; i < 200000; i++) num2.push_back(1);

	clock_t st = clock();
	rst = karatsuba(num2, num1);
	clock_t end = clock();
	cout << (double)(end-st)/CLOCKS_PER_SEC << "초 " << endl;
}