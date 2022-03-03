#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <iostream>

using namespace std;

pair<string, string> get_report_info(const string& str) {
    string token1;
    string token2;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ' ') {
            token1 = str.substr(0, i);
            token2 = str.substr(i + 1, str.length() - i);
        }
    }

    return { token1, token2 };
}

bool is_reporter_exist(vector<int>& reporter_list, int reporter) {
    for (int i = 0; i < reporter_list.size(); i++)
        if (reporter_list[i] == reporter)
            return true;

    return false;
}

vector<int> solution1(vector<string> id_list, vector<string> report, int k) {
    int id_count = id_list.size();
    vector<int> answer(id_count,0);

    // string 값을 배열 순서로 치환할 map
    map<string, int> to_num;
    for (int i = 0; i < id_count; i++) {
        to_num.insert({id_list[i],i});
    }

    // id_list 만큼 신고한 사람 수를 저장할 배열, 신고 횟수 생성
    vector<int>* reporter_list = new vector<int>[id_count];
    int* report_count = new int[id_count];
    for (int i = 0; i < id_count; i++)
        report_count[i] = 0;

    // report를 반복하며, 해당 배열에 이번에 신고한 사람이 들어있지 않다면, 추가 count 증가
    for (int i = 0; i < report.size(); i++) {
        pair<string, string> token = get_report_info(report[i]);
        string reporter = token.first;
        string reportee = token.second;

        int cur_reportee_num = to_num[reportee];
        int cur_reporter_num = to_num[reporter];
        vector<int>& cur_reporters = reporter_list[cur_reportee_num];
        
        if (!is_reporter_exist(cur_reporters, cur_reporter_num)) {
            cur_reporters.push_back(cur_reporter_num);
            report_count[cur_reportee_num]++;
        }
    }

    // count가 k이상인 reported에 대해 신고한 사람이 받을 메일 추가
    for (int i = 0; i < id_count; i++) {
        if (report_count[i] >= k) {
            for (int j = 0; j < reporter_list[i].size(); j++) {
                answer[reporter_list[i][j]]++;
            }
        }
    }

    return answer;
}

vector<int> solution2(vector<string> id_list, vector<string> report, int k) {
    int id_count = id_list.size();
    vector<int> answer(id_count, 0);

    // string 값을 배열 순서로 치환할 map
    unordered_map<string, int> to_num;
    for (int i = 0; i < id_count; i++) {
        to_num.insert({ id_list[i],i });
    }

    // id_list 만큼 신고한 사람 수를 저장할 배열, 신고 횟수 생성
    set<int>* reporter_list = new set<int>[id_count];
    int* report_count = new int[id_count];
    for (int i = 0; i < id_count; i++)
        report_count[i] = 0;

    // report를 반복하며, 해당 배열에 이번에 신고한 사람이 들어있지 않다면, 추가 count 증가
    for (int i = 0; i < report.size(); i++) {
        pair<string, string> token = get_report_info(report[i]);
        string reporter = token.first;
        string reportee = token.second;

        int cur_reportee_num = to_num[reportee];
        int cur_reporter_num = to_num[reporter];
        set<int>& cur_reporters = reporter_list[cur_reportee_num];

        if (cur_reporters.find(cur_reporter_num) == cur_reporters.end()) {
            cur_reporters.insert(cur_reporter_num);
            report_count[cur_reportee_num]++;
        }
    }

    // count가 k이상인 reported에 대해 신고한 사람이 받을 메일 추가
    for (int i = 0; i < id_count; i++) {
        if (report_count[i] >= k) {
            for (set<int>::iterator it = reporter_list[i].begin(); it != reporter_list[i].end(); it++) {
                answer[*it]++;
            }
        }
    }

    return answer;
}

void test1() {
    vector<string> id_list;
    vector<string> report;
    int k;

    id_list.push_back("muzi");
    id_list.push_back("frodo");
    id_list.push_back("apeach");
    id_list.push_back("neo");

    report.push_back("muzi frodo");
    report.push_back("apeach frodo");
    report.push_back("frodo neo");
    report.push_back("muzi neo");
    report.push_back("apeach muzi");

    k = 2;

    vector<int> answer = solution2(id_list, report, k);

    for (int i = 0; i < answer.size(); i++)
        cout << answer[i] << endl;
}

void test2() {
    vector<string> id_list;
    vector<string> report;
    int k;

    id_list.push_back("muzi");
    id_list.push_back("frodo");

    report.push_back("muzi frodo");
    report.push_back("muzi frodo");
    report.push_back("muzi frodo");
    report.push_back("muzi frodo");

    k = 3;

    vector<int> answer = solution2(id_list, report, k);

    for (int i = 0; i < answer.size(); i++)
        cout << answer[i] << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    test1();
    test2();
}