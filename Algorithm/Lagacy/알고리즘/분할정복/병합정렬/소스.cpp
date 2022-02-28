#define _CRT_SECURE_NO_WARNINGS

#include<iostream>

using namespace std;

#define MAX 20000000

void sort(int* &arr, int size) {

	if (size <= 1) {
		return ;
	}

	int *first_arr = new int[size / 2];
	int *second_arr = new int[size - size / 2];

	for (int i = 0; i < size / 2; i++) {
		first_arr[i] = arr[i];
	}
	for (int i = 0; i < size - size / 2; i++) {
		second_arr[i] = arr[size / 2 + i];
	}

	sort(first_arr, size / 2);
	sort(second_arr, size - size / 2);

	int fp = 0; int sp = 0;

	for (int i = 0; i < size; i++) {
		if (sp < size - size / 2 && fp < size / 2)
			arr[i] = first_arr[fp] < second_arr[sp] ? first_arr[fp++] : second_arr[sp++];
		else if (sp < size - size / 2)
			arr[i] = second_arr[sp++];
		else if (fp < size / 2)
			arr[i] = first_arr[fp++];
	}

	delete first_arr; 
	delete second_arr;
}


int main() {
	int arr_size;
	cout << "배열 크기 입력 : ";
	//arr_size = MAX;
	cin >> arr_size;

	int *arr = new int[arr_size];

	for (int i = 0; i < arr_size; i++) {
		cout << i+1 << "번째 값 : ";
		cin >> arr[i];
	}

	/*for (int i = 0; i < MAX; i++) {
		arr[i] = MAX - i;
	}*/

	sort(arr, arr_size);

	cout << "정렬 : ";
	for (int i = 0; i < arr_size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;


}