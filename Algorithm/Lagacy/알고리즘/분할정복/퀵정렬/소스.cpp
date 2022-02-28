#include<iostream>

using namespace std;

#define Swap(x, y) { int t; t = x; x = y; y = t;  }

int partition(int* &arr, int start_val, int end_val) {
	int left = start_val;
	int right = end_val;
	int pivot = arr[left++];

	while (left <= right) {
		while (left <= end_val && arr[left] <= pivot) left++;
		while (right > start_val && arr[right] >= pivot) right--;
		if(left <= right) Swap(arr[left], arr[right]);
	}
	Swap(arr[right], arr[start_val]);
	return right;
}

void sort(int* &arr, int left, int right){
	for (int i = 0; i < right - left + 1; i++) {
		cout << arr[left + i] << " ";
	}cout << endl;

	if (left <= right) {
		int p = partition(arr, left, right);
		sort(arr, left, p - 1);
		sort(arr, p + 1, right);
	}
}

int main() {
	int arr_size;
	cout << "배열 크기 입력 : ";
	cin >> arr_size;

	int *arr = new int[arr_size];

	for (int i = 0; i < arr_size; i++) {
		cout << i + 1 << "번쨰 배열 값 : ";
		cin >> arr[i];
	}

	cout << "정렬 전 배열 : ";
	for (int i = 0; i < arr_size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;

	sort(arr, 0, arr_size - 1);

	cout << "정렬 후 배열 : ";
	for (int i = 0; i < arr_size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}