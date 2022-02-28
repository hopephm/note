#include<iostream>

using namespace std;

#define tableSize 203456817
#define A 0.439869317215

class HASH {

public:
	HASH() {
		for (int i = 0; i < tableSize; i++) Table[i] = 0;
	}

	void insert(int val) {
		int data = val;
		int key = data % tableSize;

		while (Table[key] != 0 && Table[key] != data) {
			key = ((key * A) - (int)(key * A))*tableSize;
		}
		
		Table[key] = data;
	}

	int find(int val) {
		int data = val;
		int key = data % tableSize;

		while (Table[key] != 0 && Table[key] != data) {
			key = ((key * A) - (int)(key * A))*tableSize;
		}

		if (Table[key] == 0) {
			return 0;
		}

		return Table[key];
	}

private:
	int Table[tableSize];
};


int main() {
	HASH H;

	for (int i = 0; i < 203456817; i++) {
		H.insert(i);
	}

	for (int i = 20345680; i >=0; i--) {
		cout << H.find(i) << endl;
	}
}
