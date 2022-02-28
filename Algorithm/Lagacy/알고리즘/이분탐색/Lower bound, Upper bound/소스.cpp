#include<iostream>

using namespace std;


int lower_bound(int* arr, int size, int find_value) {
	int left = 0;
	int right = size - 1;
	int mid;

	// 범위가 존재한다면 실행
	while (left < right) {
		mid = (left + right) / 2;
		if (find_value > arr[mid]) {
			left = mid+1;
		}
		else {
			right = mid;
		}
	}

	return right;
}

int upper_bound(int* arr, int size, int find_value) {
	int left = 0;
	int right = size - 1;
	int mid;

	// 범위가 존재한다면 실행
	while (left < right) {
		mid = (left + right) / 2;
		if (find_value >= arr[mid]) {
			left = mid + 1;
		}
		else {
			right = mid;
		}
	}

	return right;
}


int main() {
	int arr[9] = {0,0,0,0,0,1,2,3,4};
	int arr2[9] = { -4,-3-2,-1,1,2,3,4,5};
	
	cout << "arr : ";
	for (int i = 0; i < 9; i++) {
		cout << arr[i] << ", ";
	}
	cout << endl;

	cout << "arr2 : ";
	for (int i = 0; i < 9; i++) {
		cout << arr2[i] << ", ";
	}
	cout << endl;


	cout << "arr_lower : " << lower_bound(arr, 9, 0) << endl;
	cout << "arr_upper : " << upper_bound(arr, 9, 0) << endl;

	cout << "arr2_lower : " << lower_bound(arr2, 9, 0) << endl;
	cout << "arr2_upper : " << upper_bound(arr2, 9, 0) << endl;
}