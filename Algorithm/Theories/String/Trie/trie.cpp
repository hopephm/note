#include<iostream>
#include<cstring>

using namespace std;

#define ALPHABETS 26

int charToNum(char c){
	return c-'a';
}

class TrieNode{
private:
	TrieNode* child[ALPHABETS];
	bool terminal;

public:
	TrieNode(): terminal(false) {
		memset(child, 0, sizeof(child));
	}

	~TrieNode(){
		for(int i = 0; i < ALPHABETS; i++)
			if(child[i]) delete child[i];
	}

	bool getTerminal(){
		return terminal;
	}

	void insert(const char* c){
		if(*c == '\0') terminal = true;
		else{
			int num = charToNum(*c);
			if(child[num] == NULL)
				child[num] = new TrieNode();
			child[num]->insert(c+1);
		}
	}

	// 존재시, 마지막 Trie 노드 전달 : 실제 존재하는 Trie내 존재 단어인지는 terminal 조회를 통해 가능
	// 미존재시 NULL 반환
	TrieNode* find(const char* c){
		if(*c == '\0') return this;
		int num = charToNum(*c);

		if(child[num] == NULL) return NULL;
		else return child[num]->find(c+1);
	}

	// 단순 해당 단어 존재시 true
	bool isExist(const char* c){
		if(*c == '\0'){
			if(terminal) return true;
			else return false;
		}else{
			int num = charToNum(*c);
			if(child[num] == NULL) return false;
			else return child[num]->find(c+1);
		}
	}

};

void printIsExist(TrieNode* t, const char* str){
	TrieNode* rst = t->find(str);

	if(rst != NULL) cout << rst->getTerminal() << endl;
	else cout << false << endl;
}

void test(){
	TrieNode* t = new TrieNode();
	t->insert("abcde");
	
	cout << t->isExist("abcde") << endl;

	printIsExist(t, "abcd");
	printIsExist(t, "abcde");
	printIsExist(t, "abcddf");
}

void test2(){
	
}

int main(){
	// test();
	test2();
}