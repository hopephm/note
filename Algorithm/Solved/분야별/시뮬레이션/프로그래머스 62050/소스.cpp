#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

struct pos {
    int x;
    int y;
    int dif;
};

struct cmp {
    bool operator()(pos a, pos b) {
        return a.dif > b.dif;
    }
};

int solution(vector<vector<int>> land, int height) {
    int answer = 0;
    int N = land.size();

    vector<vector<bool>> visited;

    for (int i = 0; i < N; i++) {
        vector<bool> cols;
        for (int j = 0; j < N; j++) {
            cols.push_back(false);
        }
        visited.push_back(cols);
    }

    pair<int, int> direction[4] = {
        {0,1},{1,0},{0,-1},{-1,0 }
    };

    priority_queue< pos, vector<pos>, cmp > laderQ;
    
    laderQ.push({ 0, 0, 0 });
    


    while (!laderQ.empty()) {
        pos t = laderQ.top();
        laderQ.pop();
        
        int x = t.x;
        int y = t.y;
        int dif = t.dif;

        if (visited[x][y]) {
            continue;
        }
        else {
            visited[x][y] = true;
            answer += dif;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + direction[i].first;
            int ny = y + direction[i].second;

            if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                int ndif = abs(land[x][y] - land[nx][ny]);
                if (visited[nx][ny] == false) {

                    if (ndif <= height)
                        ndif = 0;

                    laderQ.push({ nx,ny,ndif });
                }
            }
        }
    }

    return answer;
}

int main() {
    vector<vector<int>> land;

    vector<int> test[4];
    test[0].push_back(10);
    test[0].push_back(11);
    test[0].push_back(10);
    test[0].push_back(11);

    test[1].push_back(2);
    test[1].push_back(21);
    test[1].push_back(20);
    test[1].push_back(10);

    test[2].push_back(1);
    test[2].push_back(20);
    test[2].push_back(21);
    test[2].push_back(11);

    test[3].push_back(2);
    test[3].push_back(1);
    test[3].push_back(2);
    test[3].push_back(1);

    for (int i = 0; i < 4; i++) {
        land.push_back(test[i]);
    }

    int answer = solution(land, 1);

    cout << answer << endl;
}
