#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define INF 987654321

int calculate_score_diff(vector<int>& ryan_shots, vector<int>& apeach_shots) {
    int apeach_score = 0;
    int ryan_score = 0;

    for (int i = 0; i < apeach_shots.size(); i++) {
        if (apeach_shots[i] == 0 && ryan_shots[i] == 0)
            continue;

        if (apeach_shots[i] >= ryan_shots[i])
            apeach_score += 10 - i;
        else
            ryan_score += 10 - i;
    }

    return ryan_score - apeach_score;
}

bool compare_low_score(vector<int>& cur_shots, vector<int>& answer) {
    for (int i = answer.size() - 1; i >= 0; i--) {
        if (!(cur_shots[i] == 0 && answer[i] == 0)) {
            if (cur_shots[i] > answer[i]) 
                return true;
            else 
                return false;
        }
    }
    return false;
}

void recursion(vector<int>& cur_shots, int remain_shot, int depth, vector<int>& answer, vector<int>& info, int& max_diff) {
    if (depth == 10) {
        cur_shots[depth] = remain_shot;
        cur_shots[depth] = remain_shot;
        int diff = calculate_score_diff(cur_shots, info);

        if (diff > max_diff) {
            max_diff = diff;
            for (int i = 0; i < cur_shots.size(); i++)
                answer[i] = cur_shots[i];
        }
        else if (diff == max_diff) {
            if (compare_low_score(cur_shots, answer)) {
                for (int i = 0; i < cur_shots.size(); i++)
                    answer[i] = cur_shots[i];
            }
        }
        return;
    }
    for (int i = remain_shot; i >= 0; i--) {
        cur_shots[depth] = i;
        recursion(cur_shots, remain_shot - i, depth + 1, answer, info, max_diff);
    }
}

vector<int> solution(int n, vector<int> info) {
    vector<int> answer(11);
    vector<int> cur_shots(11);
    int max_diff = INF*(-1);

    // �⺻ ���̵�� : �ܼ� ��� ����Ǽ�, ���� ������ ����� ������ üũ�ؾ� �־��� ���ǿ� ����
    // �� �˰��� : ����Ž��, ���
    // �ð� ���⵵ : �� ����� ���� ������ �� �ִ� ���� �ϳ��� ���� 0~10���� 11! = �뷫 4000�� �ð� �γ�
    // �����÷ο� ���ɼ� : n 10, info 10, ����10+9 ...0 55, ���� �� 10 ����

    recursion(cur_shots, n, 0, answer, info, max_diff);

    if (max_diff <= 0) {
        while (answer.size() > 0)
            answer.pop_back();
        answer.push_back(-1);
    }
        

    return answer;
}

void test1() {
    vector<int> info(11,0);
    info[0] = 2; info[1] = 1; info[2] = 1; info[3] = 1;

    vector<int> answer = solution(5, info);
    for (int i = 0; i < answer.size(); i++)
        cout << answer[i] << " ";
    cout << endl;
}

void test2() {
    vector<int> info(11, 0);
    info[0] = 1;

    vector<int> answer = solution(1, info);
    for (int i = 0; i < answer.size(); i++)
        cout << answer[i] << " ";
    cout << endl;
}

void test3() {
    vector<int> info(11, 0);
    info[2] = 1; info[3] = 2;
    info[5] = 1; info[6] = 1; info[7] = 1;
    info[8] = 1; info[9] = 1; info[10] = 1;

    vector<int> answer = solution(9, info);
    for (int i = 0; i < answer.size(); i++)
        cout << answer[i] << " ";
    cout << endl;
}

void test4() {
    vector<int> info(11, 0);
    info[8] = 3; info[9] = 4; info[10] = 3;

    vector<int> answer = solution(10, info);
    for (int i = 0; i < answer.size(); i++)
        cout << answer[i] << " ";
    cout << endl;
}

int main() {
    test1();
    test2();
    test3();
    test4();
}