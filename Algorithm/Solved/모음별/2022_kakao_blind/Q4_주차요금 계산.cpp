#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#define ERR -1
#define IN 0
#define OUT 1

int get_time(string s_time) {
    int time = 0;
    time += stoi(s_time.substr(0, 2))*60;
    time += stoi(s_time.substr(3, 2));
    return time;
}

int get_car_num(string s_car_num) {
    return stoi(s_car_num);
}

int get_act(string s_act) {
    if (s_act.compare("IN") == 0) return IN;
    else if (s_act.compare("OUT") == 0) return OUT;
    return ERR;
}

void car_in(map<int, int>& parking_lot, int car_num, int time) {
    parking_lot.insert({ car_num, time });
}

void car_out(map<int, int>& parking_lot, map<int,int>& parking_time, int car_num, int time) {
    map<int, int>::iterator it = parking_lot.find(car_num);
    int in_time = (*it).second;
    parking_lot.erase(it);

    if (parking_time.find(car_num) == parking_time.end())
        parking_time.insert({ car_num, time - in_time });
    else
        parking_time[car_num] += time - in_time;
}

vector<int> solution(vector<int> fees, vector<string> records) {
    vector<int> answer;

    // 기본요금, 기본 시간, 단위 시간, 단위 시간 당 요금
    int basic_time = fees[0];
    int basic_fee = fees[1];
    int unit_time = fees[2];
    int unit_fee = fees[3];

    // 현재 주차장에 있는 차 정보 map
    map<int, int> parking_lot;
    // 한번이라도 들어왔던 차량의 누적 주차시간
    map<int, int> parking_time;

    // records를 돌며 입출차 처리
    for (int i = 0; i < records.size(); i++) {
        int time = get_time(records[i].substr(0, 5));
        int car_num = get_car_num(records[i].substr(6, 4));
        int act = get_act(records[i].substr(11, records[i].length() - 11));

        if (act == IN) {
            car_in(parking_lot, car_num, time);
        }
        else if (act == OUT) {
            car_out(parking_lot, parking_time, car_num, time);   
        }
    }

    // OUT되지 않은 자동차 처리
    vector<int> remain_car_nums;
    int out_time = get_time("23:59");

    for (map<int, int>::iterator it = parking_lot.begin(); it != parking_lot.end(); it++) 
        remain_car_nums.push_back((*it).first);
    
    for (int i = 0; i < remain_car_nums.size(); i++) 
        car_out(parking_lot, parking_time, remain_car_nums[i], out_time);

    // 요금 계산
    for (map<int, int>::iterator it = parking_time.begin(); it != parking_time.end(); it++) {
        int fee = 0;
        int time = (*it).second;
        fee += basic_fee;
        time -= basic_time;

        if (time > 0) {
            fee += unit_fee * (time / unit_time);
            if (time % unit_time != 0) fee += unit_fee;
        }

        answer.push_back(fee);
    }

    return answer;
}

void test() {
    vector<int> fees;
    vector<string> records;

    fees.push_back(180);
    fees.push_back(5000);
    fees.push_back(10);
    fees.push_back(600);

    records.push_back("05:34 5961 IN");
    records.push_back("06:00 0000 IN");
    records.push_back("06:34 0000 OUT");
    records.push_back("07:59 5961 OUT");
    records.push_back("07:59 0148 IN");
    records.push_back("18:59 0000 IN");
    records.push_back("19:09 0148 OUT");
    records.push_back("22:59 5961 IN");
    records.push_back("23:00 5961 OUT");

    vector<int> answer = solution(fees, records);

    for (int i = 0; i < answer.size(); i++)
        cout << answer[i] << " ";
    cout << endl;
}

void test2() {
    vector<int> fees;
    vector<string> records;

    fees.push_back(120);
    fees.push_back(0);
    fees.push_back(60);
    fees.push_back(591);

    records.push_back("16:00 3961 IN");
    records.push_back("16:00 0202 IN");
    records.push_back("18:00 3961 OUT");
    records.push_back("18:00 0202 OUT");
    records.push_back("23:58 3961 IN");

    vector<int> answer = solution(fees, records);

    for (int i = 0; i < answer.size(); i++)
        cout << answer[i] << " ";
    cout << endl;
}

void test3() {
    vector<int> fees;
    vector<string> records;

    fees.push_back(1);
    fees.push_back(461);
    fees.push_back(1);
    fees.push_back(10);

    records.push_back("00:00 1234 IN");

    vector<int> answer = solution(fees, records);

    for (int i = 0; i < answer.size(); i++)
        cout << answer[i] << " ";
    cout << endl;
}


int main() {
    test();
    test2();
    test3();
}