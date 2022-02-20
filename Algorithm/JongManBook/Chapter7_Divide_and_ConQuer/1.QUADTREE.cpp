#include<iostream>
#include<string>

using namespace std;

// 문제점 : getScope 와 simulation 에서 재귀를 각각 돎으로 시간이 2배 든다.
//          (사실 줄어드는 시간에 비하면 미미하긴한데... 최적화 고려좀 해보자)


typedef struct Scope{
	int st;
	int end;
}Scope;

Scope getScope(string& compressed, int cur){
	int base = cur+1;

	if(compressed[cur] == 'x'){
		for(int i = 0; i < 4; i++){
			Scope tmp = getScope(compressed, base);
			base = tmp.end;
		}
	}

	return {cur, base};
}

string simulation(string& compressed, int cur){
	string reversed = "";
	reversed += compressed[cur];

	if(compressed[cur] == 'x'){
		int base = cur+1;
		string parts[4];

		for(int i = 0; i < 4; i++){
			parts[i] = simulation(compressed, base);
			Scope tmp = getScope(compressed, base);
			base = tmp.end;
		}

		reversed += parts[2] + parts[3] + parts[0] + parts[1];
	}

	return reversed;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int testCase; cin >> testCase;

	for(int tc = 0; tc < testCase; tc++){
		string compressed; 
		cin >> compressed;

		cout << simulation(compressed, 0) << endl;
	}
}