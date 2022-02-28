/*#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdio.h>

using namespace std;

#define UP 0
#define LEFT 1
#define FRONT 2
#define RIGHT 3
#define BACK 4
#define DOWN 5

char SIDE[6][10] = {
	"UP", "LEFT", "FRONT", "RIGHT", "BACK", "DOWN"
};

class CUBE {
private:
	pair<char,int> FACE[6][3][3];

public:
	CUBE() {
		int count = 1;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				FACE[UP][i][j] = { 'w',count }; FACE[DOWN][i][j] = { 'y',count }; FACE[LEFT][i][j] = { 'g',count };
				FACE[RIGHT][i][j] = { 'b',count }; FACE[FRONT][i][j] = { 'r',count }; FACE[BACK][i][j] = { 'o',count };
				count++;
			}
		}
	}

	void Spin(char Side, char Direction) {
		pair<char,int> Cur_Side[3][3];
		pair<char,int> T_val[3];
		int n_Side;
		bool flag;

		// 현재 면의 플래그 값 확인

		// +, -
		if (Direction == '+') flag = true;
		else if(Direction == '-') flag = false;
		else return;

		// Side
		if (Side == 'U')  n_Side = UP;
		else if (Side == 'D') n_Side = DOWN;
		else if (Side == 'L') n_Side = LEFT;
		else if (Side == 'R') n_Side = RIGHT;
		else if (Side == 'F') n_Side = FRONT;
		else if (Side == 'B') n_Side = BACK;
		else return;

		// 현재 면의 현재정보 저장
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				Cur_Side[i][j] = FACE[n_Side][i][j];

		// 현재 면 자체 회전
		if (flag) {
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					FACE[n_Side][i][j] = Cur_Side[2 - j][i];
		}
		else {
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					FACE[n_Side][i][j] = Cur_Side[j][2 - i];
		}

		// 현재면과 인접한 면의 회전 
		switch (Side) {
		case 'U':
			if (flag) {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[LEFT][0][i];
					FACE[LEFT][0][i] = FACE[FRONT][0][i];
					FACE[FRONT][0][i] = FACE[RIGHT][0][i];
					FACE[RIGHT][0][i] =FACE[BACK][0][i];
					FACE[BACK][0][i] = T_val[i];
				}
			}
			else {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[LEFT][0][i];
					FACE[LEFT][0][i] = FACE[BACK][0][i];
					FACE[BACK][0][i] = FACE[RIGHT][0][i];
					FACE[RIGHT][0][i] = FACE[FRONT][0][i];
					FACE[FRONT][0][i] = T_val[i];
				}
			}
			break;
		case 'D':
			if (flag) {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[LEFT][2][i];
					FACE[LEFT][2][i] = FACE[BACK][2][i];
					FACE[BACK][2][i] = FACE[RIGHT][2][i];
					FACE[RIGHT][2][i] = FACE[FRONT][2][i];
					FACE[FRONT][2][i] = T_val[i];
				}
			}
			else {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[LEFT][2][i];
					FACE[LEFT][2][i] = FACE[FRONT][2][i];
					FACE[FRONT][2][i] = FACE[RIGHT][2][i];
					FACE[RIGHT][2][i] = FACE[BACK][2][i];
					FACE[BACK][2][i] = T_val[i];
				}
			}
			break;
		case 'L':
			if (flag) {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[BACK][2-i][2];
					FACE[BACK][2-i][2] = FACE[DOWN][i][0];
					FACE[DOWN][i][0] = FACE[FRONT][i][0];
					FACE[FRONT][i][0] = FACE[UP][i][0];
					FACE[UP][i][0] = T_val[i];
				}
			}
			else {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[BACK][2 - i][2];
					FACE[BACK][2 - i][2] = FACE[UP][i][0];
					FACE[UP][i][0] = FACE[FRONT][i][0];
					FACE[FRONT][i][0] = FACE[DOWN][i][0];
					FACE[DOWN][i][0] = T_val[i];
				}
			}
			break;
		case 'R':
			if (flag) {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[BACK][2 - i][0];
					FACE[BACK][2 - i][0] = FACE[UP][i][2];
					FACE[UP][i][2] = FACE[FRONT][i][2];
					FACE[FRONT][i][2] = FACE[DOWN][i][2];
					FACE[DOWN][i][2] = T_val[i];
				}
			}
			else {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[BACK][2 - i][0];
					FACE[BACK][2 - i][0] = FACE[DOWN][i][2];
					FACE[DOWN][i][2] = FACE[FRONT][i][2];
					FACE[FRONT][i][2] = FACE[UP][i][2];
					FACE[UP][i][2] = T_val[i];
				}
			}
			break;
		case 'F':
			if (flag) {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[UP][2][2 - i];
					FACE[UP][2][2 - i] = FACE[LEFT][i][2];
					FACE[LEFT][i][2] = FACE[DOWN][0][i];
					FACE[DOWN][0][i] = FACE[RIGHT][2 - i][0];
					FACE[RIGHT][2 - i][0] = T_val[i];
				}
			}
			else {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[UP][2][2 - i];
					FACE[UP][2][2 - i] = FACE[RIGHT][2 - i][0];
					FACE[RIGHT][2 - i][0] = FACE[DOWN][0][i];
					FACE[DOWN][0][i] = FACE[LEFT][i][2];
					FACE[LEFT][i][2] = T_val[i];
				}
			}
			break;
		case 'B':
			if (flag) {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[UP][0][i];
					FACE[UP][0][i] = FACE[RIGHT][i][2];
					FACE[RIGHT][i][2] = FACE[DOWN][2][2 - i];
					FACE[DOWN][2][2 - i] = FACE[LEFT][2 - i][0];
					FACE[LEFT][2 - i][0] = T_val[i];
				}
			}
			else {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[UP][0][i];
					FACE[UP][0][i] = FACE[LEFT][2 - i][0];
					FACE[LEFT][2 - i][0] = FACE[DOWN][2][2 - i];
					FACE[DOWN][2][2 - i] = FACE[RIGHT][i][2];
					FACE[RIGHT][i][2] = T_val[i];
				}
			}
			break;
		}
	}


	void Print() {
		for (int k = 0; k < 6; k++) {
			cout << SIDE[k] << endl << endl;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					cout << FACE[k][i][j].first << FACE[k][i][j].second << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
	}
};

int main() {
	char Temp1, Temp2;
	int c, n;
	CUBE cube1;

	cin >> n;

	//cube1.Print();
	for (int i = 0; i < n; i++) {
		scanf(" %c%c", &Temp1, &Temp2);
		cube1.Spin(Temp1, Temp2);
	}
	

	cube1.Print();

}*/


#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdio.h>

using namespace std;

#define UP 0
#define LEFT 1
#define FRONT 2
#define RIGHT 3
#define BACK 4
#define DOWN 5

class CUBE {
private:
	char FACE[6][3][3];

public:
	CUBE() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				FACE[UP][i][j] = 'w'; FACE[DOWN][i][j] = 'y'; FACE[LEFT][i][j] = 'g';
				FACE[RIGHT][i][j] = 'b'; FACE[FRONT][i][j] = 'r'; FACE[BACK][i][j] = 'o';
			}
		}
	}

	void Spin(char Side, char Direction) {
		char Cur_Side[3][3];
		char T_val[3];
		int n_Side;
		bool flag;

		// 현재 면의 플래그 값 확인

		// +, -
		if (Direction == '+') flag = true;
		else if (Direction == '-') flag = false;
		else return;

		// Side
		if (Side == 'U')  n_Side = UP;
		else if (Side == 'D') n_Side = DOWN;
		else if (Side == 'L') n_Side = LEFT;
		else if (Side == 'R') n_Side = RIGHT;
		else if (Side == 'F') n_Side = FRONT;
		else if (Side == 'B') n_Side = BACK;
		else return;

		// 현재 면의 현재정보 저장
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				Cur_Side[i][j] = FACE[n_Side][i][j];

		// 현재 면 자체 회전
		if (flag) {
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					FACE[n_Side][i][j] = Cur_Side[2 - j][i];
		}
		else {
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					FACE[n_Side][i][j] = Cur_Side[j][2 - i];
		}

		// 현재면과 인접한 면의 회전 
		switch (Side) {
		case 'U':
			if (flag) {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[LEFT][0][i];
					FACE[LEFT][0][i] = FACE[FRONT][0][i];
					FACE[FRONT][0][i] = FACE[RIGHT][0][i];
					FACE[RIGHT][0][i] = FACE[BACK][0][i];
					FACE[BACK][0][i] = T_val[i];
				}
			}
			else {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[LEFT][0][i];
					FACE[LEFT][0][i] = FACE[BACK][0][i];
					FACE[BACK][0][i] = FACE[RIGHT][0][i];
					FACE[RIGHT][0][i] = FACE[FRONT][0][i];
					FACE[FRONT][0][i] = T_val[i];
				}
			}
			break;
		case 'D':
			if (flag) {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[LEFT][2][i];
					FACE[LEFT][2][i] = FACE[BACK][2][i];
					FACE[BACK][2][i] = FACE[RIGHT][2][i];
					FACE[RIGHT][2][i] = FACE[FRONT][2][i];
					FACE[FRONT][2][i] = T_val[i];
				}
			}
			else {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[LEFT][2][i];
					FACE[LEFT][2][i] = FACE[FRONT][2][i];
					FACE[FRONT][2][i] = FACE[RIGHT][2][i];
					FACE[RIGHT][2][i] = FACE[BACK][2][i];
					FACE[BACK][2][i] = T_val[i];
				}
			}
			break;
		case 'L':
			if (flag) {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[BACK][2 - i][2];
					FACE[BACK][2 - i][2] = FACE[DOWN][i][0];
					FACE[DOWN][i][0] = FACE[FRONT][i][0];
					FACE[FRONT][i][0] = FACE[UP][i][0];
					FACE[UP][i][0] = T_val[i];
				}
			}
			else {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[BACK][2 - i][2];
					FACE[BACK][2 - i][2] = FACE[UP][i][0];
					FACE[UP][i][0] = FACE[FRONT][i][0];
					FACE[FRONT][i][0] = FACE[DOWN][i][0];
					FACE[DOWN][i][0] = T_val[i];
				}
			}
			break;
		case 'R':
			if (flag) {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[BACK][2 - i][0];
					FACE[BACK][2 - i][0] = FACE[UP][i][2];
					FACE[UP][i][2] = FACE[FRONT][i][2];
					FACE[FRONT][i][2] = FACE[DOWN][i][2];
					FACE[DOWN][i][2] = T_val[i];
				}
			}
			else {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[BACK][2 - i][0];
					FACE[BACK][2 - i][0] = FACE[DOWN][i][2];
					FACE[DOWN][i][2] = FACE[FRONT][i][2];
					FACE[FRONT][i][2] = FACE[UP][i][2];
					FACE[UP][i][2] = T_val[i];
				}
			}
			break;
		case 'F':
			if (flag) {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[UP][2][2 - i];
					FACE[UP][2][2 - i] = FACE[LEFT][i][2];
					FACE[LEFT][i][2] = FACE[DOWN][0][i];
					FACE[DOWN][0][i] = FACE[RIGHT][2 - i][0];
					FACE[RIGHT][2 - i][0] = T_val[i];
				}
			}
			else {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[UP][2][2 - i];
					FACE[UP][2][2 - i] = FACE[RIGHT][2 - i][0];
					FACE[RIGHT][2 - i][0] = FACE[DOWN][0][i];
					FACE[DOWN][0][i] = FACE[LEFT][i][2];
					FACE[LEFT][i][2] = T_val[i];
				}
			}
			break;
		case 'B':
			if (flag) {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[UP][0][i];
					FACE[UP][0][i] = FACE[RIGHT][i][2];
					FACE[RIGHT][i][2] = FACE[DOWN][2][2 - i];
					FACE[DOWN][2][2 - i] = FACE[LEFT][2 - i][0];
					FACE[LEFT][2 - i][0] = T_val[i];
				}
			}
			else {
				for (int i = 0; i < 3; i++) {
					T_val[i] = FACE[UP][0][i];
					FACE[UP][0][i] = FACE[LEFT][2 - i][0];
					FACE[LEFT][2 - i][0] = FACE[DOWN][2][2 - i];
					FACE[DOWN][2][2 - i] = FACE[RIGHT][i][2];
					FACE[RIGHT][i][2] = T_val[i];
				}
			}
			break;
		}
	}

	void Print() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << FACE[UP][i][j];
			}
			cout << endl;
		}
	}
};

int main() {
	char Temp1, Temp2;
	int c, n;

	cin >> c;

	for (int i = 0; i < c; i++) {
		CUBE cube1;

		cin >> n;

		for (int i = 0; i < n; i++) {
			scanf(" %c%c", &Temp1, &Temp2);
			cube1.Spin(Temp1, Temp2);
		}


		cube1.Print();
	}

}