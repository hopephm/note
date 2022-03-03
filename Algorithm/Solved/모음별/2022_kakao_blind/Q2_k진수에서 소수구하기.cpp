#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int get_max_power(int n, int k) {
    int p = 0;
    while (n / (int)pow(k, p) >= 1) {
        p++;
    }
    return p-1;
}

bool is_prime(long long n) {
    if (n <= 1) return false;
    else if (n == 2 || n == 3) return true;

    for (long long i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int solution1(int n, int k) {
    int answer = 0;
    
    // n�� k������ ��ȯ
    //  - n���� k^p �� ���� 1�̻��� p�� Ž��
    //  - p�� �ϳ��� �ٿ�������, k������ �ڸ��� ����
    //  - ���� 0�� �������� ��������� ���� ���� �Ҽ� �˻�
    //  - �Ҽ���� ī��Ʈ ����

    int p = get_max_power(n, k);

    long long cur_v = 0;
    int cur_n = n;

    for (int i = p; i >= 0; i--) {
        int cur_t = (int)pow(k, i);
        int cur_q = cur_n / cur_t;
        int cur_m = cur_n % cur_t;

        if (cur_q == 0) {
            // ���� ���� 0�̶�� �Ҽ� �˻� �� �ʱ�ȭ
            if (is_prime(cur_v)) answer++;
            cur_v = 0;
        }
        else {
            // ���� ���� 0�� �ƴ϶��, value ���� ���� 10�� ���ϰ� ���� ���� ����
            cur_v = cur_v * 10 + cur_q;
        }

        cur_n = cur_m;
    }

    if (is_prime(cur_v)) answer++;

    return answer;
}

///////////////////////////////////////////////////////////////////////////////////////////

vector<int> get_k_nums(int n, int k) {
    vector<int> k_nums;

    int p = get_max_power(n, k);

    int cur_n = n;
    for (int i = p; i >= 0; i--) {
        k_nums.push_back(cur_n / (int)pow(k, i));
        cur_n = cur_n % (int)pow(k, i);
    }

    return k_nums;
}

int solution2(int n, int k) {
    int answer = 0;

    vector<int> k_nums = get_k_nums(n, k);
    
    int val = 0;
    for (int i = 0; i < k_nums.size(); i++) {
        if (k_nums[i] == 0) {
            if (is_prime(val)) answer++;
            val = 0;
        }
        else
            val = val * 10 + k_nums[i];
    }
    if (val != 0)
        if (is_prime(val)) answer++;

    return answer;
}

void test1() {
    int answer = solution2(1000000, 3);
    cout << answer << endl;
}

void test2() {
    int answer = solution2(1000000, 3);
    cout << answer << endl;
}

int main() {
    test1();
    test2();
}