#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

#define NUMS 10

class TrieNode{
private:
	bool terminal;
	bool hasChild;
	TrieNode* child[NUMS];

	int charToNum(const char c){
		return c-'0';
	}

	bool getTerminal(){
		return terminal;
	}

public:
	TrieNode():terminal(false), hasChild(false){
		memset(child,0,sizeof(child));
	}

	~TrieNode(){
		for(int i = 0; i < NUMS; i++)
			if(child[i]) delete child[i];
	}

	bool insertWithCheck(const char* c){
		if(*c == '\0'){
			terminal = true;
			if(hasChild) return false;
			else return true;
		}else{
			int num = charToNum(*c);
			if(child[num] == NULL){
				hasChild = true;
				child[num] = new TrieNode();
			}
			else if(*(c+1) != '\0' && child[num]->getTerminal())
				return false;

			return child[num]->insertWithCheck(c+1);
		}
	}

};
	
int main(){
	int tc; cin >> tc;
	
	for(int t = 0; t < tc; t++){
		int n; cin >> n;

		char **nums = new char*[n];
		for(int i = 0; i < n; i++)
			nums[i] = new char[NUMS];

		for(int i = 0; i < n; i++)
			cin >> nums[i];

		bool rst;
		TrieNode* root = new TrieNode();
		for(int i = 0; i < n; i++){
			rst = root->insertWithCheck(nums[i]);
			if(!rst) break;
		}

		if(rst) cout << "YES" << endl;
		else cout << "NO" << endl;

		delete[] nums;
		delete root;
	}
}