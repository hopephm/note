/*#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<stack>

using namespace std;

#define MAX 50

vector<string> Graph[MAX];
map<string, int> Str_to_int;

bool Blocked[MAX+1];
bool is_Cycle;
string Cycle_value;
stack<string> st;

int num_of_Web = 1;

void Init() {
	for (int i = 1; i < num_of_Web; i++) {
		Blocked[i] = false;
	}
	is_Cycle = false;
}


int dfs(string f_WN) {
	st.push(f_WN);

	int re = 1;	

	// 종료조건 : 사이클 발생시 return 0; (사이클에 해당하는 값들은 전부 0이 되어야 함에 주의)
	if (Blocked[Str_to_int[f_WN]]) {
		is_Cycle = true;
		Cycle_value = st.top(); st.pop();
		return 0;
	}

	// 기저조건 : 해당 그래프가 비어있을경우 return 1;
	// 호출조건 : 자신과 연결된 노드가 있을경우, 연결된 노드에 대해 호출 값을 최종 반환
		
	int F_N = Str_to_int[f_WN];
	for (int i = 0; i < Graph[F_N].size(); i++) {
		Blocked[F_N] = true;
		re += dfs(Graph[F_N][i]);
		Blocked[F_N] = false;

		if (is_Cycle) {
			if (st.top() != Cycle_value) {
				st.pop(); return 0;
			}
			else {
				is_Cycle = false; 
				//st.pop(); return 1;
			}
		}

	}

	st.pop();
	return re;
}

int main() {
	int N, Link;
	string Web_name, to_Webname, find_Webname;

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> Web_name;
		if(Str_to_int[Web_name] == 0) Str_to_int[Web_name] = num_of_Web++;

		cin >> Link;

		for (int j = 0; j < Link; j++) {
			cin >> to_Webname;
			Graph[Str_to_int[Web_name]].push_back(to_Webname);
		}
	}

	cin >> find_Webname;

	cout << dfs(find_Webname) << endl;
}*/

// 시간초과뜬다...



/*#include<iostream>
#include<stdio.h>
#include<string>
#include<vector>
#include<map>
#include<stack>

using namespace std;

#define MAX 51

map< string, vector<string> > Graph;

map < string, bool > Blocked;
map < string, long long > Searched;

bool is_Cycle;
string Cycle_value;
stack<string> st;

int num_of_Web = 1;

long long search(string f_WN) {
	st.push(f_WN);
	if (Blocked[f_WN]) {
		is_Cycle = true;
		Cycle_value = st.top(); st.pop();
		return 0;
	}
	if (Searched[f_WN] != -1) {
		cout << "f_WN : " << f_WN;
		cout << "  / Searched[f_WN] = " << Searched[f_WN] << endl;
		return Searched[f_WN];
	}

	

	long long re = 1;

	// 종료조건 : 사이클 발생시 return 0; (사이클에 해당하는 값들은 전부 0이 되어야 함에 주의)
	

	// 기저조건 : 해당 그래프가 비어있을경우 return 1;
	// 호출조건 : 자신과 연결된 노드가 있을경우, 연결된 노드에 대해 호출 값을 최종 반환

	for (int i = 0; i < Graph[f_WN].size(); i++) {
		Blocked[f_WN] = true;
		re += search(Graph[f_WN][i]);
		Blocked[f_WN] = false;

		if (is_Cycle) {
			if (st.top() != Cycle_value) {
				st.pop(); return 0;
			}
			else {
				is_Cycle = false;
			}
		}

	}

	st.pop();
	Searched[f_WN] = re;
	return re;
}

int main() {
	is_Cycle = false;

	int N, Link;
	string Web_name, to_Webname, find_Webname;

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> Web_name;
		Blocked[Web_name] = false;
		Searched[Web_name] = -1;

		cin >> Link;

		for (int j = 0; j < Link; j++) {
			cin >> to_Webname;
			Blocked[to_Webname] = false;
			Searched[to_Webname] = -1;

			Graph[Web_name].push_back(to_Webname);
		}
	}

	cin >> find_Webname;

	cout << search(find_Webname) << endl;

}*/

// 사이클 처리실패




/*#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<stack>

using namespace std;

#define MAX 60

map< string, vector<string> > Graph;
map < string, long long > Searched;

int num_of_Web = 1;

map< string, vector<string> > r_Graph;
map< string, bool > visited;
vector< string > SCC[MAX];
int SCC_count = 0;

void Init(string f_name) {
	for (map<string, bool>::iterator it = visited.begin(); it != visited.end(); it++) {
		(*it).second = false;
	}
}

stack< string > st;

void f_dfs(string f_webname) {
	//cout << f_webname << " ";
	for (int i = 0; i < Graph[f_webname].size(); i++) {
		if (!visited[Graph[f_webname][i]]) {
			visited[Graph[f_webname][i]] = true;
			f_dfs(Graph[f_webname][i]);
		}
	}
	st.push(f_webname);
}

void s_dfs(string r_webname) {
	//cout << r_webname << " ";
	for (int i = 0; i < r_Graph[r_webname].size(); i++) {
		if (!visited[r_Graph[r_webname][i]]) {
			visited[r_Graph[r_webname][i]] = true;
			s_dfs(r_Graph[r_webname][i]);
		}
	}
	SCC[SCC_count].push_back(r_webname);
}

long long search(string f_WN) {
	if (Searched[f_WN] != -1) {
		//cout << "f_WN : " << f_WN;
		//cout << "  / Searched[f_WN] = " << Searched[f_WN] << endl;
		return Searched[f_WN];
	}

	long long re = 1;

	for (int i = 0; i < Graph[f_WN].size(); i++) {
		re += search(Graph[f_WN][i]);
	}

	Searched[f_WN] = re;
	return re;
}

int main() {
	int N, Link;
	string Web_name, to_Webname, find_Webname;

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> Web_name;
		Searched[Web_name] = -1;
		visited[Web_name] = false;

		cin >> Link;

		for (int j = 0; j < Link; j++) {
			cin >> to_Webname;
			Searched[to_Webname] = -1;
			visited[Web_name] = false;

			Graph[Web_name].push_back(to_Webname);
			r_Graph[to_Webname].push_back(Web_name);
		}
	}

	cin >> find_Webname;

	Init(find_Webname);
	visited[find_Webname] = true;
	f_dfs(find_Webname);
	for (map<string, bool>::iterator it = visited.begin(); it != visited.end(); it++) {
		if ((*it).second == false) {
			(*it).second = true;
			f_dfs((*it).first);
		}
	}

	Init(st.top());
	string cur_webname;
	while (!st.empty()) {
		//cout << "스택호출 : " << st.top() << endl;
		cur_webname = st.top(); st.pop();
		if (!visited[cur_webname]) {
			visited[cur_webname] = true;
			s_dfs(cur_webname);
			SCC_count++;
		}
		//cout << endl;
	}

	for (int i = 0; i < SCC_count; i++) {
		if (SCC[i].size() > 1) {
			for (int j = 0; j < SCC[i].size(); j++) {
				Searched[SCC[i][j]] = 1;
			}
		}
	}

	/*for (int i = 0; i < SCC_count; i++) {
		cout << i << "번째 SCC : ";
		for (int j = 0; j < SCC[i].size(); j++) {
			cout << SCC[i][j] << " ";
		}
		cout << endl;
	}*/

	/*cout << search(find_Webname) << endl;
}*/

//런타임 에러





/*#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<stack>

using namespace std;

#define MAX 1000

map < string, vector<string> > Graph;
map < string, long long > Searched;

map< string, vector<string> > r_Graph;

map< string, bool > visited;
map< string, int > SCC_num;
map< int, vector< string > > SCC;

int SCC_count_ = 0;

void Init(string f_name) {
	for (map<string, bool>::iterator it = visited.begin(); it != visited.end(); it++) {
		(*it).second = false;
	}
}

stack< string > st;

void f_dfs(string f_webname) {
	//cout << f_webname << " ";
	for (unsigned int i = 0; i < Graph[f_webname].size(); i++) {
		if (!visited[Graph[f_webname][i]]) {
			visited[Graph[f_webname][i]] = true;
			f_dfs(Graph[f_webname][i]);
		}
	}
	st.push(f_webname);
}

void s_dfs(string r_webname) {
	//cout << r_webname << " ";
	for (unsigned int i = 0; i < r_Graph[r_webname].size(); i++) {
		if (!visited[r_Graph[r_webname][i]]) {
			visited[r_Graph[r_webname][i]] = true;
			s_dfs(r_Graph[r_webname][i]);
		}
	}
	SCC[SCC_count_].push_back(r_webname);
}

bool is_in_SCC(string to_name, int SCC_num) {
	for (unsigned int i = 0; i < SCC[SCC_num].size(); i++) {
		if (SCC[SCC_num][i] == to_name) {
			return true;
		}
	}
	return false;
}

long long search(string f_WN) {
	if (Searched[f_WN] != -1) {
		//cout << "f_WN : " << f_WN;
		//cout << "  / Searched[f_WN] = " << Searched[f_WN] << endl;
		return Searched[f_WN];
	}

	long long re = 1;

	for (unsigned int i = 0; i < Graph[f_WN].size(); i++) {
		if (!is_in_SCC(Graph[f_WN][i], SCC_num[f_WN])) {
			if (Searched[f_WN] == -1) {
				re += search(Graph[f_WN][i]);
			}
			else {
				re += Searched[f_WN];
			}
		}
	}

	Searched[f_WN] = re;
	return re;
}

int main() {
	int N, Link;
	string Web_name, to_Webname, find_Webname;

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> Web_name;
		Searched[Web_name] = -1;
		visited[Web_name] = false;

		cin >> Link;

		for (int j = 0; j < Link; j++) {
			cin >> to_Webname;
			Searched[to_Webname] = -1;
			visited[Web_name] = false;

			Graph[Web_name].push_back(to_Webname);
			r_Graph[to_Webname].push_back(Web_name);
		}
	}

	cin >> find_Webname;

	Init(find_Webname);
	visited[find_Webname] = true;
	f_dfs(find_Webname);
	for (map<string, bool>::iterator it = visited.begin(); it != visited.end(); it++) {
		if ((*it).second == false) {
			(*it).second = true;
			f_dfs((*it).first);
		}
	}

	Init(st.top());
	string cur_webname;
	while (!st.empty()) {
		//cout << "스택호출 : " << st.top() << endl;
		cur_webname = st.top(); st.pop();
		if (!visited[cur_webname]) {
			visited[cur_webname] = true;

			s_dfs(cur_webname);
			SCC_num[cur_webname] = SCC_count_++;			
		}
		//cout << endl;
	}

	/*for (int i = 0; i < SCC_count; i++) {
		cout << i << "번째 SCC : ";
		for (int j = 0; j < SCC[i].size(); j++) {
			cout << SCC[i][j] << " ";
		}
		cout << endl;
	}

	cout << search(find_Webname) << endl;

}*/


// 메모리 초과 >> map에서 찾는 연산이 추가되므로



#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<stack>

using namespace std;

#define MAX 2500

map <string, int> Str_to_int;
map <int, string> Int_to_string;

vector<int> Graph[MAX];
vector<int> r_Graph[MAX];
long long Searched[MAX];

bool visited[MAX];
vector<int> SCC[MAX];
int SCC_num[MAX];


/*map < string, vector<string> > Graph;
map < string, long long > Searched;

map< string, vector<string> > r_Graph;

map< string, bool > visited;
map< string, int > SCC_num;
map< int, vector< string > > SCC;*/

int SCC_count_ = 0;
int name_count_ = 1;

void Init() {
	for (int i = 1; i < name_count_; i++) {
		visited[i] = false;
	}
}

stack< int > st;

void f_dfs(int f_webname) {
	//cout << f_webname << " ";
	for (unsigned int i = 0; i < Graph[f_webname].size(); i++) {
		if (!visited[Graph[f_webname][i]]) {
			visited[Graph[f_webname][i]] = true;
			f_dfs(Graph[f_webname][i]);
		}
	}
	st.push(f_webname);
}

void s_dfs(int r_webname) {
	//cout << r_webname << " ";
	for (unsigned int i = 0; i < r_Graph[r_webname].size(); i++) {
		if (!visited[r_Graph[r_webname][i]]) {
			visited[r_Graph[r_webname][i]] = true;
			s_dfs(r_Graph[r_webname][i]);
		}
	}
	SCC_num[r_webname] = SCC_count_;
	SCC[SCC_count_].push_back(r_webname);
}

long long search(int f_WN) {
	
	if (Searched[f_WN] != -1) {
		//cout << "f_WN : " << f_WN;
		//cout << "  / Searched[f_WN] = " << Searched[f_WN] << endl;
		return Searched[f_WN];
	}

	long long re = 1;

	for (unsigned int i = 0; i < Graph[f_WN].size(); i++) {
		if (SCC_num[Graph[f_WN][i]] != SCC_num[f_WN]) {
			if (Searched[Graph[f_WN][i]] == -1) {
				re += search(Graph[f_WN][i]);
			}
			else {
				re += Searched[Graph[f_WN][i]];
			}
		}
	}

	Searched[f_WN] = re;
	return re;
}

int main() {
	int N, Link;
	string Web_name, to_Webname, find_Webname;

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> Web_name;
		if (Str_to_int[Web_name] == 0) {
			Searched[name_count_] = -1;
			visited[name_count_] = false;
			Int_to_string[name_count_] = Web_name;
			Str_to_int[Web_name] = name_count_++;
		}

		cin >> Link;

		for (int j = 0; j < Link; j++) {
			cin >> to_Webname;
			if (Str_to_int[to_Webname] == 0) {
				Searched[name_count_] = -1;
				visited[name_count_] = false;
				Int_to_string[name_count_] = to_Webname;
				Str_to_int[to_Webname] = name_count_++;
			}

			Graph[Str_to_int[Web_name]].push_back(Str_to_int[to_Webname]);
			r_Graph[Str_to_int[to_Webname]].push_back(Str_to_int[Web_name]);
		}
	}

	cin >> find_Webname;

	Init();
	visited[Str_to_int[find_Webname]] = true;
	f_dfs(Str_to_int[find_Webname]);
	for (int i = 1; i < name_count_; i++) {
		if (!visited[i]) {
			visited[i] = true;
			f_dfs(i);
		}
	}

	Init();
	int cur_webname;
	while (!st.empty()) {
		//cout << "스택호출 : " << st.top() << endl;
		cur_webname = st.top(); st.pop();
		if (!visited[cur_webname]) {
			visited[cur_webname] = true;

			s_dfs(cur_webname);
			SCC_count_++;
		}
		//cout << endl;
	}

	/*for (int i = 0; i < SCC_count_; i++) {
		cout << i << "번째 SCC : ";
		for (int j = 0; j < SCC[i].size(); j++) {
			cout << Int_to_string[SCC[i][j]] << "(" << SCC_num[SCC[i][j]] << " )" ;
		}
		cout << endl;
	}*/

	cout << search(Str_to_int[find_Webname]) << endl;

	/*for (int i = 1; i < name_count_; i++) {
		cout << "Searched[" << Int_to_string[i] << "] = " << Searched[i] << endl;
	}
	cout << endl;*/
}