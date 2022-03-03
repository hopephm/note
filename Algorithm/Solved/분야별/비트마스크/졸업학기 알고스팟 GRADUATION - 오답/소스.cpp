
// 가능하면 전부다 넣음 : 오답
/*#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

void getCombination(int subjectCount, int demandedSubject, int semesterCount, int maxSubjects,
	unsigned short* subjects, unsigned short* semesters,
	unsigned short isTaken, int takenCount,
	unsigned short isAvailable, int AvailableCount,
	int cpltSemester, int curSemester, int &minSem,
	int maxVal, int* availableSubject, bool* isSelected, int depth);

void getMinimum(int subjectCount, int demandedSubject, int semesterCount, int maxSubjects,
	unsigned short* subjects, unsigned short* semesters,
	unsigned short isTaken, int takenCount,
	unsigned short isAvailable, int AvailableCount,
	int cpltSemester, int curSemester, int &minSem);

void getCombination(int subjectCount, int demandedSubject, int semesterCount, int maxSubjects,
	unsigned short* subjects, unsigned short* semesters,
	unsigned short isTaken, int takenCount,
	unsigned short isAvailable, int AvailableCount,
	int cpltSemester, int curSemester, int &minSem,
	int maxVal, int* availableSubject, bool* isSelected, int depth) {

	if (depth == maxVal) {
		for (int i = 0; i < AvailableCount; i++) {
			if (isSelected[i]) {
				isAvailable = (isAvailable & (65535 - (unsigned short)pow(2, availableSubject[i])));
			}
		}
		AvailableCount -= maxVal;

		isTaken = isTaken | isAvailable;
		takenCount += AvailableCount;

		getMinimum(subjectCount, demandedSubject, semesterCount, maxSubjects, subjects, semesters, isTaken, takenCount, isAvailable, AvailableCount, cpltSemester + 1, curSemester + 1, minSem);
		return;
	}

	for (int i = 0; i < AvailableCount; i++) {
		isSelected[i] = true;
		getCombination(subjectCount, demandedSubject, semesterCount, maxSubjects, subjects, semesters, isTaken, takenCount, isAvailable, AvailableCount, cpltSemester, curSemester, minSem, maxVal, availableSubject, isSelected, depth + 1);
		isSelected[i] = false;
	}
}

void getMinimum(int subjectCount, int demandedSubject, int semesterCount, int maxSubjects,
	unsigned short* subjects, unsigned short* semesters,
	unsigned short isTaken, int takenCount,
	unsigned short isAvailable, int AvailableCount,
	int cpltSemester, int curSemester, int &minSem) {

	if (takenCount >= demandedSubject) {
		if (cpltSemester <= minSem) {
			minSem = cpltSemester;
		}
		return;
	}

	if (curSemester >= semesterCount) {
		return;
	}

	// isAvailable : 수강 가능한 과목들 (현재 개설되어 있고, 아직 수강하지 않은 )
	// AvailableCount : 수강 가능한 과목 수 
	isAvailable = 0;
	AvailableCount = 0;

	// 휴학하는 경우 호출
	getMinimum(subjectCount, demandedSubject, semesterCount, maxSubjects, subjects, semesters, isTaken, takenCount, isAvailable, AvailableCount, cpltSemester, curSemester + 1, minSem);

	// 현재 수강가능한 과목번호 기록을 위한 배열
	int *availableSubject = new int[subjectCount];
	memset(availableSubject, 0, sizeof(int)*subjectCount);

	for (int subs = 0; subs < subjectCount; subs++) {
		unsigned short curSub = (unsigned short)pow(2, subs);

		if (((isTaken | subjects[subs]) == 65535) &&  // 수강가능여부 판별
			((semesters[curSemester] & curSub) == curSub) && // 개설 되어있는지 여부 판별
			((isTaken & curSub) != curSub) &&
			((isAvailable & curSub) != curSub)) { // 이미 수강하였는지 판별
			
			isAvailable = isAvailable | curSub;
			availableSubject[AvailableCount++] = subs;
		}
	}

	// 수강 가능한 과목을 다 들을 수 있는 경우 
	if (AvailableCount <= maxSubjects) {
		isTaken = isTaken | isAvailable;
		takenCount += AvailableCount;

		getMinimum(subjectCount, demandedSubject, semesterCount, maxSubjects, subjects, semesters, isTaken, takenCount, isAvailable, AvailableCount, cpltSemester + 1, curSemester + 1, minSem);
	}// 수강 가능한 과목 중 최대 과목만큼 골라야 하는 경우
	else {
		// 입력은 1,2,3,4... 순으로 받았고, AC는 0부터 시작하여서 1 더해주어야 함
		int rmCount = (AvailableCount)-maxSubjects;

		bool *isSelected = new bool[AvailableCount];
		memset(isSelected, false, sizeof(bool)*AvailableCount);

		getCombination(subjectCount, demandedSubject, semesterCount, maxSubjects, subjects, semesters, isTaken, takenCount, isAvailable, AvailableCount, cpltSemester, curSemester, minSem, rmCount, availableSubject, isSelected, 0);
		delete isSelected;
	}

	delete availableSubject;
}


int main() {
	int testCase;
	cin >> testCase;

	for (int Case = 0; Case < testCase; Case++) {
		// get input
		int subjectCount, demandedSubject, semesterCount, maxSubjects;
		cin >> subjectCount >> demandedSubject >> semesterCount >> maxSubjects;

		unsigned short *subjects = new unsigned short[subjectCount];
		memset(subjects, 0, sizeof(short)*subjectCount);

		for (int i = 0; i < subjectCount; i++) {
			int counts; cin >> counts;
			for (int j = 0; j < counts; j++) {
				int val; cin >> val;
				subjects[i] = subjects[i] | (unsigned short)pow(2, val);
			}
			subjects[i] = (~subjects[i]);
		}

		unsigned short *semesters = new unsigned short[semesterCount];
		memset(semesters, 0, sizeof(short)*subjectCount);

		for (int i = 0; i < semesterCount; i++) {
			int counts; cin >> counts;
			for (int j = 0; j < counts; j++) {
				int val; cin >> val;
				semesters[i] = semesters[i] | (unsigned short)pow(2, val);
			}
		}

		unsigned short isTaken = 0; // 이미 수강한 과목
		int takenCount = 0;

		unsigned short isAvailable = 0; // 선택 가능한 과목
		int AvailableCount = 0;

		int minSem = 987654321;

		getMinimum(subjectCount, demandedSubject, semesterCount, maxSubjects, subjects, semesters, isTaken, takenCount, isAvailable, AvailableCount, 0, 0, minSem);

		if (minSem == 987654321)
			cout << "IMPOSSIBLE" << endl;
		else
			cout << minSem << endl;

		// free memory
		delete subjects, semesters;
	}

}*/



// 전체검사 : 시간초과
/*#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

void getCombination(int subjectCount, int demandedSubject, int semesterCount, int maxSubjects,
	unsigned short* subjects, unsigned short* semesters,
	unsigned short isTaken, int takenCount,
	unsigned short isAvailable, int AvailableCount,
	int cpltSemester, int curSemester, int &minSem,
	int maxVal, int* availableSubject, bool* isSelected, int depth);

void getMinimum(int subjectCount, int demandedSubject, int semesterCount, int maxSubjects,
	unsigned short* subjects, unsigned short* semesters,
	unsigned short isTaken, int takenCount,
	unsigned short isAvailable, int AvailableCount,
	int cpltSemester, int curSemester, int &minSem);

void getCombination(int subjectCount, int demandedSubject, int semesterCount, int maxSubjects,
	unsigned short* subjects, unsigned short* semesters,
	unsigned short isTaken, int takenCount,
	unsigned short isAvailable, int AvailableCount,
	int cpltSemester, int curSemester, int &minSem,
	int maxVal, int* availableSubject, bool* isSelected, int depth) {

	if (depth > maxVal || curSemester > semesterCount) return;

	unsigned short rstAvailable = 0;
	int rstCount = 0;

	for (int i = 0; i < AvailableCount; i++) {
		if (isSelected[i]) {
			rstAvailable = rstAvailable | (unsigned short)pow(2, availableSubject[i]);
			rstCount++;
		}
	}

	int nexttakenCount = 0;
	unsigned short nextTaken = 0;

	nextTaken = isTaken | rstAvailable;
	nexttakenCount = takenCount + rstCount;
	getMinimum(subjectCount, demandedSubject, semesterCount, maxSubjects, subjects, semesters, nextTaken, nexttakenCount, rstAvailable, rstCount, cpltSemester + 1, curSemester + 1, minSem);

	for (int i = 0; i < AvailableCount; i++) {
		isSelected[i] = true;
		getCombination(subjectCount, demandedSubject, semesterCount, maxSubjects, subjects, semesters, isTaken, takenCount, isAvailable, AvailableCount, cpltSemester, curSemester, minSem, maxVal, availableSubject, isSelected, depth + 1);
		isSelected[i] = false;
	}
}

void getMinimum(int subjectCount, int demandedSubject, int semesterCount, int maxSubjects,
	unsigned short* subjects, unsigned short* semesters,
	unsigned short isTaken, int takenCount,
	unsigned short isAvailable, int AvailableCount,
	int cpltSemester, int curSemester, int &minSem) {

	if (takenCount >= demandedSubject) {
		if (cpltSemester <= minSem) {
			minSem = cpltSemester;
		}
		return;
	}

	if (curSemester >= semesterCount || cpltSemester >= minSem) {
		return;
	}

	// isAvailable : 수강 가능한 과목들 (현재 개설되어 있고, 아직 수강하지 않은 )
	// AvailableCount : 수강 가능한 과목 수 
	isAvailable = 0;
	AvailableCount = 0;

	// 휴학하는 경우 호출
	getMinimum(subjectCount, demandedSubject, semesterCount, maxSubjects, subjects, semesters, isTaken, takenCount, isAvailable, AvailableCount, cpltSemester, curSemester + 1, minSem);

	// 현재 수강가능한 과목번호 기록을 위한 배열
	int *availableSubject = new int[subjectCount];
	memset(availableSubject, 0, sizeof(int)*subjectCount);

	for (int subs = 0; subs < subjectCount; subs++) {
		unsigned short curSub = (unsigned short)pow(2, subs);

		if (((isTaken | subjects[subs]) == 65535) &&  // 수강가능여부 판별
			((semesters[curSemester] & curSub) == curSub) && // 개설 되어있는지 여부 판별
			((isTaken & curSub) != curSub) && // 이미 수강하였는지 판별
			((isAvailable & curSub) != curSub)) { // 중복인지 판별

			isAvailable = isAvailable | curSub;
			availableSubject[AvailableCount++] = subs;
		}
	}

	// 수강 가능한 과목을 다 들을 수 있는 경우 
	int maxCount = maxSubjects;

	bool *isSelected = new bool[AvailableCount];
	memset(isSelected, false, sizeof(bool)*AvailableCount);

	getCombination(subjectCount, demandedSubject, semesterCount, maxSubjects, subjects, semesters, isTaken, takenCount, isAvailable, AvailableCount, cpltSemester, curSemester, minSem, maxCount, availableSubject, isSelected, 0);
	delete isSelected;

	delete availableSubject;
}


int main() {
	int testCase;
	cin >> testCase;

	for (int Case = 0; Case < testCase; Case++) {
		// get input
		int subjectCount, demandedSubject, semesterCount, maxSubjects;
		cin >> subjectCount >> demandedSubject >> semesterCount >> maxSubjects;

		unsigned short *subjects = new unsigned short[subjectCount];
		memset(subjects, 0, sizeof(short)*subjectCount);

		for (int i = 0; i < subjectCount; i++) {
			int counts; cin >> counts;
			for (int j = 0; j < counts; j++) {
				int val; cin >> val;
				subjects[i] = subjects[i] | (unsigned short)pow(2, val);
			}
			subjects[i] = (~subjects[i]);
		}

		unsigned short *semesters = new unsigned short[semesterCount];
		memset(semesters, 0, sizeof(short)*subjectCount);

		for (int i = 0; i < semesterCount; i++) {
			int counts; cin >> counts;
			for (int j = 0; j < counts; j++) {
				int val; cin >> val;
				semesters[i] = semesters[i] | (unsigned short)pow(2, val);
			}
		}

		unsigned short isTaken = 0; // 이미 수강한 과목
		int takenCount = 0;

		unsigned short isAvailable = 0; // 선택 가능한 과목
		int AvailableCount = 0;

		int minSem = 987654321;

		getMinimum(subjectCount, demandedSubject, semesterCount, maxSubjects, subjects, semesters, isTaken, takenCount, isAvailable, AvailableCount, 0, 0, minSem);

		if (minSem == 987654321)
			cout << "IMPOSSIBLE" << endl;
		else
			cout << minSem << endl;

		// free memory
		delete subjects, semesters;
	}

}*/
