#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdio.h>

using namespace std;

class cube {

private:
	// 면의 위쪽   : [0][0] [0][1] [0][2]
	// 면의 아래쪽 : [2][0] [2][1] [2][2]
	// 면의 왼쪽   : [0][0] [1][0] [2][0]
	// 면의 오른쪽 : [0][2] [1][2] [2][2]

	char UP[3][3];
	char DOWN[3][3];
	char FRONT[3][3];
	char BACK[3][3];
	char LEFT[3][3];
	char RIGHT[3][3];

public:
	cube() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				UP[i][j] = 'w';
				DOWN[i][j] = 'y';
				FRONT[i][j] = 'r';
				BACK[i][j] = 'o';
				LEFT[i][j] = 'g';
				RIGHT[i][j] = 'b';
			}
		}
	}

	

	void spin(char face, char val) {
		char temp[3];
		char top[3][3];
		bool direction;

		if (val == '+') direction = true;
		else if(val == '-') direction = false;
		else cout << "잘못된 값!" << endl;

		switch (face) {
		case 'U': 
			if (direction) { // L(U) -> B(U) -> R(U) -> F(U) -> L(U)    >> 시계방향
				for (int i = 0; i < 3; i++) temp[i] = LEFT[0][i];
				for (int i = 0; i < 3; i++) LEFT[0][i] = FRONT[0][i];
				for (int i = 0; i < 3; i++) FRONT[0][i] = RIGHT[0][i];
				for (int i = 0; i < 3; i++) RIGHT[0][i] = BACK[0][i];
				for (int i = 0; i < 3; i++) BACK[0][i] = temp[i];
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						top[i][j] = UP[i][j];
					}
				}
				UP[0][2] = top[0][0]; UP[1][2] = top[0][1]; UP[2][2] = top[0][2];
				UP[0][1] = top[1][0]; UP[1][1] = top[1][1]; UP[2][1] = top[1][2];
				UP[0][0] = top[2][0]; UP[1][0] = top[2][1]; UP[2][0] = top[2][2];
			}
			else {			 // L(U) -> F(U) -> R(U) -> B(U) -> L(U)    >> 반시계방향
				for (int i = 0; i < 3; i++) temp[i] = LEFT[0][i];
				for (int i = 0; i < 3; i++) LEFT[0][i] = BACK[0][i];
				for (int i = 0; i < 3; i++) BACK[0][i] = RIGHT[0][i];
				for (int i = 0; i < 3; i++) RIGHT[0][i] = FRONT[0][i];
				for (int i = 0; i < 3; i++) FRONT[0][i] = temp[i];
				for (int i = 0; i < 3; i++) { 
					for (int j = 0; j < 3; j++) {
						top[i][j] = UP[i][j];
					}
				}
				UP[0][2] = top[2][2]; UP[1][2] = top[2][1]; UP[2][2] = top[2][0];
				UP[0][1] = top[1][2]; UP[1][1] = top[1][1]; UP[2][1] = top[1][0];
				UP[0][0] = top[0][2]; UP[1][0] = top[0][1]; UP[2][0] = top[0][0];
			}
			break;
		case 'D':
			if (direction) { // L(D) -> F(D) -> R(D) -> B(D) -> L(D) 
				for (int i = 0; i < 3; i++) temp[i] = LEFT[2][i];
				for (int i = 0; i < 3; i++) LEFT[2][i] = BACK[2][i];
				for (int i = 0; i < 3; i++) BACK[2][i] = RIGHT[2][i];
				for (int i = 0; i < 3; i++) RIGHT[2][i] = FRONT[2][i];
				for (int i = 0; i < 3; i++) FRONT[2][i] = temp[i];
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						top[i][j] = DOWN[i][j];
					}
				}
				DOWN[0][2] = top[0][0]; DOWN[1][2] = top[0][1]; DOWN[2][2] = top[0][2];
				DOWN[0][1] = top[1][0]; DOWN[1][1] = top[1][1]; DOWN[2][1] = top[1][2];
				DOWN[0][0] = top[2][0]; DOWN[1][0] = top[2][1]; DOWN[2][0] = top[2][2];
			}
			else {			 // L(D) -> B(D) -> R(D) -> F(D) -> L(D)
				
				for (int i = 0; i < 3; i++) temp[i] = LEFT[2][i];
				for (int i = 0; i < 3; i++) LEFT[2][i] = FRONT[2][i];
				for (int i = 0; i < 3; i++) FRONT[2][i] = RIGHT[2][i];
				for (int i = 0; i < 3; i++) RIGHT[2][i] = BACK[2][i];
				for (int i = 0; i < 3; i++) BACK[2][i] = temp[i];
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						top[i][j] = DOWN[i][j];
					}
				}
				DOWN[0][2] = top[2][2]; DOWN[1][2] = top[2][1]; DOWN[2][2] = top[2][0];
				DOWN[0][1] = top[1][2]; DOWN[1][1] = top[1][1]; DOWN[2][1] = top[1][0];
				DOWN[0][0] = top[0][2]; DOWN[1][0] = top[0][1]; DOWN[2][0] = top[0][0];
			}
			break;
		case 'L':
			if (direction) { // B(R) -> U(L) -> F(L) -> D(L) -> B(R)
				for (int i = 0; i < 3; i++) temp[i] = BACK[2-i][2];
				for (int i = 0; i < 3; i++) BACK[i][2] = DOWN[2-i][0];
				for (int i = 0; i < 3; i++) DOWN[i][0] = FRONT[i][0];
				for (int i = 0; i < 3; i++) FRONT[i][0] = UP[i][0];
				for (int i = 0; i < 3; i++) UP[i][0] = temp[i];
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						top[i][j] = LEFT[i][j];
					}
				}
				LEFT[0][2] = top[0][0]; LEFT[1][2] = top[0][1]; LEFT[2][2] = top[0][2];
				LEFT[0][1] = top[1][0]; LEFT[1][1] = top[1][1]; LEFT[2][1] = top[1][2];
				LEFT[0][0] = top[2][0]; LEFT[1][0] = top[2][1]; LEFT[2][0] = top[2][2];
			}
			else {			 // B(R) -> D(L) -> F(L) -> U(L) -> B(R)
				for (int i = 0; i < 3; i++) temp[i] = BACK[2 - i][2];
				for (int i = 0; i < 3; i++) BACK[i][2] = UP[2 - i][0];
				for (int i = 0; i < 3; i++) UP[i][0] = FRONT[i][0];
				for (int i = 0; i < 3; i++) FRONT[i][0] = DOWN[i][0];
				for (int i = 0; i < 3; i++) DOWN[i][0] = temp[i];
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						top[i][j] = LEFT[i][j];
					}
				}
				LEFT[0][2] = top[2][2]; LEFT[1][2] = top[2][1]; LEFT[2][2] = top[2][0];
				LEFT[0][1] = top[1][2]; LEFT[1][1] = top[1][1]; LEFT[2][1] = top[1][0];
				LEFT[0][0] = top[0][2]; LEFT[1][0] = top[0][1]; LEFT[2][0] = top[0][0];
			}
			break;
		case 'R':
			if (direction) { // B(L) -> D(R) -> F(R) -> U(R) -> B(L)
				for (int i = 0; i < 3; i++) temp[i] = BACK[2 - i][0];
				for (int i = 0; i < 3; i++) BACK[i][0] = UP[2 - i][2];
				for (int i = 0; i < 3; i++) UP[i][2] = FRONT[i][2];
				for (int i = 0; i < 3; i++) FRONT[i][2] = DOWN[i][2];
				for (int i = 0; i < 3; i++) DOWN[i][2] = temp[i];
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						top[i][j] = RIGHT[i][j];
					}
				}
				RIGHT[0][2] = top[0][0]; RIGHT[1][2] = top[0][1]; RIGHT[2][2] = top[0][2];
				RIGHT[0][1] = top[1][0]; RIGHT[1][1] = top[1][1]; RIGHT[2][1] = top[1][2];
				RIGHT[0][0] = top[2][0]; RIGHT[1][0] = top[2][1]; RIGHT[2][0] = top[2][2];
			}
			else {			 // B(L) -> U(R) -> F(R) -> D(R) -> B(L)
				for (int i = 0; i < 3; i++) temp[i] = BACK[2 - i][0];
				for (int i = 0; i < 3; i++) BACK[i][0] = DOWN[2-i][2];
				for (int i = 0; i < 3; i++) DOWN[i][2] = FRONT[i][2];
				for (int i = 0; i < 3; i++) FRONT[i][2] = UP[i][2];
				for (int i = 0; i < 3; i++) UP[i][2] = temp[i];
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						top[i][j] = RIGHT[i][j];
					}
				}
				RIGHT[0][2] = top[2][2]; RIGHT[1][2] = top[2][1]; RIGHT[2][2] = top[2][0];
				RIGHT[0][1] = top[1][2]; RIGHT[1][1] = top[1][1]; RIGHT[2][1] = top[1][0];
				RIGHT[0][0] = top[0][2]; RIGHT[1][0] = top[0][1]; RIGHT[2][0] = top[0][0];
			}
			break;
		case 'F':
			if (direction) { // L(R) -> U(D) -> R(L) -> D(U) -> L(R)
				for (int i = 0; i < 3; i++) temp[i] = LEFT[2-i][2];
				for (int i = 0; i < 3; i++) LEFT[i][2] = DOWN[0][i]; //done
				for (int i = 0; i < 3; i++) DOWN[0][i] = RIGHT[2-i][0];
				for (int i = 0; i < 3; i++) RIGHT[i][0] = UP[2][i];
				for (int i = 0; i < 3; i++) UP[2][i] = temp[i];
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						top[i][j] = FRONT[i][j];
					}
				}
				FRONT[0][2] = top[0][0]; FRONT[1][2] = top[0][1]; FRONT[2][2] = top[0][2];
				FRONT[0][1] = top[1][0]; FRONT[1][1] = top[1][1]; FRONT[2][1] = top[1][2];
				FRONT[0][0] = top[2][0]; FRONT[1][0] = top[2][1]; FRONT[2][0] = top[2][2];
			}
			else {			 // L(R) -> D(U) -> R(L) -> U(D) -> L(R)

				for (int i = 0; i < 3; i++) temp[i] = LEFT[2 - i][2];
				for (int i = 0; i < 3; i++) LEFT[i][2] = UP[2][i];
				for (int i = 0; i < 3; i++) UP[2][i] = RIGHT[2 - i][0];
				for (int i = 0; i < 3; i++) RIGHT[i][0] = DOWN[0][i];
				for (int i = 0; i < 3; i++) DOWN[0][i] = temp[i];
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						top[i][j] = FRONT[i][j];
					}
				}
				FRONT[0][2] = top[2][2]; FRONT[1][2] = top[2][1]; FRONT[2][2] = top[2][0];
				FRONT[0][1] = top[1][2]; FRONT[1][1] = top[1][1]; FRONT[2][1] = top[1][0];
				FRONT[0][0] = top[0][2]; FRONT[1][0] = top[0][1]; FRONT[2][0] = top[0][0];
			}
			break;
		case 'B':
			if (direction) { // L(L) -> D(D) -> R(R) -> U(U) -> L(L)
				for (int i = 0; i < 3; i++) temp[i] = LEFT[i][0];
				for (int i = 0; i < 3; i++) LEFT[i][0] = UP[0][2-i];
				for (int i = 0; i < 3; i++) UP[0][i] = RIGHT[i][2];
				for (int i = 0; i < 3; i++) RIGHT[i][2] = DOWN[2][2-i];
				for (int i = 0; i < 3; i++) DOWN[2][i] = temp[i];
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						top[i][j] = BACK[i][j];
					}
				}
				BACK[0][2] = top[0][0]; BACK[1][2] = top[0][1]; BACK[2][2] = top[0][2];
				BACK[0][1] = top[1][0]; BACK[1][1] = top[1][1]; BACK[2][1] = top[1][2];
				BACK[0][0] = top[2][0]; BACK[1][0] = top[2][1]; BACK[2][0] = top[2][2];
			}
			else {			 // L(L) -> U(U) -> R(R) -> D(D) -> L(L)
				for (int i = 0; i < 3; i++) temp[i] = LEFT[2-i][0];
				for (int i = 0; i < 3; i++) LEFT[i][0] = DOWN[2][i];
				for (int i = 0; i < 3; i++) DOWN[2][i] = RIGHT[2-i][2];
				for (int i = 0; i < 3; i++) RIGHT[i][2] = UP[0][i];
				for (int i = 0; i < 3; i++) UP[0][i] = temp[i];
				for (int i = 0; i < 3; i++){
					for (int j = 0; j < 3; j++) {
						top[i][j] = BACK[i][j];
					}
				}
				BACK[0][2] = top[2][2]; BACK[1][2] = top[2][1]; BACK[2][2] = top[2][0];
				BACK[0][1] = top[1][2]; BACK[1][1] = top[1][1]; BACK[2][1] = top[1][0];
				BACK[0][0] = top[0][2]; BACK[1][0] = top[0][1]; BACK[2][0] = top[0][0];
			}
			break;
		}
	}

	void print_UP() {
		//cout << "UP" << endl;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << UP[i][j];
			}
			cout << endl;
		}
		/*cout << endl;
		cout << "DOWN " << endl;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << DOWN[i][j];
			}
			cout << endl;
		}
		cout << endl;
		cout << "FRONT " << endl;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << FRONT[i][j];
			}
			cout << endl;
		}
		cout << endl;
		cout << "LEFT" << endl;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << LEFT[i][j];
			}
			cout << endl;
		}
		cout << endl;
		cout << "BACK" << endl;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << BACK[i][j];
			}
			cout << endl;
		}

		cout << endl;
		cout << "RIGHT " << endl;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << RIGHT[i][j];
			}
			cout << endl;
		}
		cout << endl; */
	}

};


int main() {
	int case_, count_;
	char Temp1, Temp2;

	cin >> case_;

	for (int i = 0; i < case_; i++) {
		cube CUBE;
		cin >> count_;

		for (int i = 0; i < count_; i++) {
			scanf(" %1c%1c", &Temp1, &Temp2);
			CUBE.spin(Temp1, Temp2);
		}

		CUBE.print_UP();
	}
}
