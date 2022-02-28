#include<iostream>
#include<cstdio>
#include<vector>
#include<string>

using namespace std;

#define MAX 1000000
vector<char*> list;

int main() {
	int testcase;
	char** list;
	char** RESULT;
	char temp[MAX];

	cin >> testcase;

	list = new char*[testcase];
	RESULT = new char*[testcase];

	for (int i = 0; i < testcase; i++) {
		RESULT[i] = new char[MAX];
		list[i] = new char[MAX];

		scanf_s("%s", temp, MAX);
		strcpy_s(list[i],MAX, temp);
	}

	int cur,size;
	for (int i = 0; i < testcase; i++) {
		cur = 0;
		size = 0;
		for (int j = 0; j < strlen(list[i]); j++) {
			if (list[i][j] == '<') {
				if (cur > 0) {
					cur--;
				}
			}
			else if (list[i][j] == '>') {
				if (cur < size) {
					cur++;
				}
			}
			else if (list[i][j] == '-') {
				memmove(RESULT[i] + cur - 1, RESULT[i] + cur, size - cur);
				cur--;
			}
			else {
				memmove(RESULT[i] + cur + 1, RESULT[i] + cur, size - cur);
				RESULT[i][cur] = list[i][j];
				size++;
				cur++;
			}
		}
		RESULT[i][cur] = NULL;
	}


	for (int i = 0; i < testcase; i++) {
		printf("%s\n", RESULT[i]);
	}

}