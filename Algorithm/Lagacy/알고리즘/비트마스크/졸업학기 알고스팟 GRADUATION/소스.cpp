#include<iostream>
#include <intrin.h>		//__popcnt
#include<cstring>
#include<cmath>

using namespace std;

#define MAX_SUBJECT 12
#define MAX_SEMESTER 10

void selectSubject(int subjectCount,int maxSemester, int desiredSubject, int takeCount, unsigned short* subjects, unsigned short* semesters, int cpltSemester, int curSemester, int taken) {

	// 필요학점을 모두 채웠다면 
	if (__popcnt(taken) >= desiredSubject) {
		// 현재값을 최소값과 비교, 출력

		return;
	}

	unsigned short canTake = USHRT_MAX;
	canTake &= ~taken;

	for (int i = 0; i < subjectCount; i++) {
		if ((taken & subjects[i]) != subjects[i]) {
			canTake &= (~(1 << i));
		}
	}

	canTake &= semesters[curSemester];

	for (unsigned short toTake = 0; toTake <= canTake; toTake++){
		unsigned short curTake = toTake & canTake;
		selectSubject(subjectCount, maxSemester, desiredSubject, takeCount, subjects, semesters, cpltSemester+1, curSemester+1, curTake | taken);
	}

}

int main() {
	int testCase; cin >> testCase;

	for (int Case = 0; Case < testCase; Case++) {
		int N, K, M, L;
		cin >> N >> K >> M >> L;

		unsigned short subjects[MAX_SUBJECT]; 
		memset(subjects, 0, sizeof(unsigned short)*MAX_SUBJECT);

		unsigned short semesters[MAX_SEMESTER];
		memset(semesters, 0, sizeof(unsigned short)*MAX_SEMESTER);

		// get subject info
		for (int i = 0; i < N; i++) {
			int temp; cin >> temp;
			for (int j = 0; j < temp; j++) {
				int val; cin >> val;
				unsigned short sub = (1 << val);
				subjects[i] |= sub;
			}
		}

		// get semester info
		for (int i = 0; i < M; i++) {
			int temp; cin >> temp;
			for (int j = 0; j < temp; j++) {
				int val; cin >> val;
				unsigned short sem = (1 << val);
				semesters[i] |= sem;
			}
		}

		// get available subjects
		selectSubject(N, M, K, L, subjects, semesters, 0, 0, 0);



#ifdef SHOW_INPUT
		cout << "\nsubject info" << endl;
		for (int i = 0; i < N; i++) {
			cout << "subject[" << i << "] : ";
			for (int j = 0; j < N; j++) {
				unsigned short toFindSub = (1 << j);
				if ((subjects[i] & toFindSub) == toFindSub) cout << j << " ";
			}cout << endl;
		} cout << endl;

		cout << "\nsemester info" << endl;
		for (int i = 0; i < M; i++) {
			cout << "semester[" << i << "] : ";
			for (int j = 0; j < N; j++) {
				unsigned short toFindSub = (1 << j);
				if ((semesters[i] & toFindSub) == toFindSub) cout << j << " ";
			}cout << endl;
		} cout << endl;
#endif

	}

}