#include<iostream>
#include<vector>
#include<cstring>

using namespace std;
	
#define ALPHABETS 26
#define MAX 81

class TrieNode{
private:
	bool isTerminal;
	int childNum;
	vector<int> childNo;
	TrieNode *child[ALPHABETS];

public:
	TrieNode(): isTerminal(false), childNum(0){
		memset(child, 0, sizeof(child));
	}

	~TrieNode(){
		for(int i = 0; i < ALPHABETS; i++)
			if(child[i]) delete child[i];
	}

	int getChildNum() {return childNum;}

	int charToNo(char c){
		return c - 'a';
	}

	void push(const char* c){
		if(*c == '\0'){
			isTerminal = true;
		}else{
			int n = charToNo(*c);

			if(child[n] == NULL){
				child[n] = new TrieNode();
				childNo.push_back(n);
				childNum++;
			}

			child[n]->push(c+1);
		}
	}

	bool isExist(const char* c){
		if(*c == '\0'){
			if(isTerminal) return true;
			else return false;
		}else{
			int n = charToNo(*c);
			if(child[n] == NULL) return false;
			else return child[n]->isExist(c+1);
		}
	}

	int calculateClickNum(int click){
		if(childNum == 0) return click;
		
		if(!isTerminal && childNum == 1)
			return child[childNo[0]]->calculateClickNum(click);
		else{
			int total = 0;
			if(isTerminal) total += click;
			for(int i = 0; i < childNum; i++)
				total += child[childNo[i]]->calculateClickNum(click+1);
			return total;
		}
	}

};

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);cout.tie(NULL);

	int tc;
	while(cin >> tc){
		TrieNode trie;

		for(int i = 0; i < tc; i++){
			char str[MAX];
			cin >> str;
			trie.push(str);
		}
		
		if(trie.getChildNum() == 1)
			printf("%.2lf\n", trie.calculateClickNum(1)/(double)tc);
		else
			printf("%.2lf\n", trie.calculateClickNum(0)/(double)tc);
	}

}