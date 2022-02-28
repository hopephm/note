#include<iostream>

using namespace std;

#define NUMS 10

class Trie {
public:
	Trie() {
		for (int i = 0; i < NUMS; i++) {
			child[i] = NULL;
		}
		isValuable = false;
	}

	~Trie() {
		for (int i = 0; i < NUMS; i++) {
			if (child[i]) {
				delete child[i];
			}
		}
	}

	void insert(const char* str) {
		if (*str == NULL) {
			isValuable = true;
		}
		else {
			int next = (int)str[0] - 48;

			if (child[next] == NULL) {
				child[next] = new Trie();
			}

			child[next]->insert(str + 1);
		}
	}

	Trie* find(const char* str) {
		if (*str == NULL) {
			return this;
		}
		int next = str[0]-48;

		if (child[next] == NULL) return NULL;

		return child[next]->find(str+1);
	}

	bool getValuable() {
		return isValuable;
	}

private:
	Trie *child[NUMS];
	bool isValuable;
};

int main() {
	Trie T;
	T.insert("1234");

	Trie *temp;
	temp = T.find("1234");
	if (temp->getValuable()) {
		cout << "is_Exist" << endl; 
	}
	else {
		cout << "is_nExist" << endl;
	}

}


