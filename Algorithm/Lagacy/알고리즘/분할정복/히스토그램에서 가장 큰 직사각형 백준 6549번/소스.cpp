#include<iostream>
#include<algorithm>
using namespace std;

/*
	1. ���簢���� ������ ��� ����
	2. ���簢���� ũ�Ⱑ 1 �̵Ǹ� �ִ� ���� ��ȯ
	3. ���ս�, �� �κй����� ���̸� �޾ƿ�
	4. ���������� �߰��κ��� ���� ���� (�߰����� ���� �÷���)
*/

#define MAX 100000

long long Graph[MAX];

// �� �κй������� ���� ū ���簢�� ��ȯ
// ���ս� �߰��κ� Ȯ��

long long Solve(int st_pt, int ed_pt) {

	//1. �������� : ũ�Ⱑ 1�̶�� ���� ���� �״�� ��ȯ
	if (st_pt == ed_pt) {
		return Graph[st_pt];
	}

	//2. �������� : �߰� ������ ȣ��
	long long MAX_val = 0;
	long long left_val = 0, right_val = 0;
	int center = (st_pt + ed_pt) / 2;
	
	left_val = Solve(st_pt, center);
	right_val = Solve(center + 1, ed_pt);

	MAX_val = max(left_val, right_val);

	//3. �������� : �� �κ��� MAX���� �޾ƿµ�, ���� �߾Ӻ��� �÷����� ���� ���
	int left_p = center;
	int right_p = center + 1;
	long long min_Height = min(Graph[left_p], Graph[right_p]);

	MAX_val = max(MAX_val, (right_p - left_p + 1) * min_Height);

	while (left_p - 1 >= st_pt || right_p + 1 <= ed_pt) {
		if (left_p - 1 >= st_pt && right_p + 1 <= ed_pt) {
			if (Graph[right_p + 1] > Graph[left_p - 1]) right_p++;
			else left_p--;
		}
		else if (left_p - 1 >= st_pt) left_p--;
		else if (right_p + 1 <= ed_pt) right_p++;

		min_Height = min(min_Height, Graph[left_p]);
		min_Height = min(min_Height, Graph[right_p]);

		MAX_val = max(MAX_val, (right_p - left_p + 1) * min_Height);
	}
	
	return MAX_val;
}

int main() {
	int  Graph_size, value;
	cin >> Graph_size;

	while (Graph_size != 0) {
		for (int i = 0; i < Graph_size; i++) {
			cin >> Graph[i];
		}
		cout << Solve(0, Graph_size - 1) << endl;
		cin >> Graph_size;
	}
}