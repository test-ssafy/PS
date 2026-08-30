#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct People {
    int dist[2];
};

int n, ans;
int stairLen[2];
vector<People> people;

int simulate(vector<int>& arrive, int k) {
    if (arrive.empty()) return 0;

    sort(arrive.begin(), arrive.end());

    int finish[10]{ 0 };
    for (int i = 0; i < arrive.size(); i++) {
        if (i < 3) finish[i] = arrive[i] + k;
        else {
            // 도착한 시간 vs 자리가 남은 시간 중 더 늦은 시간부터 시작
            finish[i] = max(arrive[i], finish[i - 3]) + k;
        }
    }

    return finish[arrive.size() - 1];
}

void simulateAll(int mask) {
    vector<int> arrive[2];

    for (int i = 0; i < people.size(); i++) {
        int stair = (mask >> i) & 1;
        arrive[stair].push_back(people[i].dist[stair]);
    }

    int t0 = simulate(arrive[0], stairLen[0]);
    int t1 = simulate(arrive[1], stairLen[1]);

    ans = min(ans, max(t0, t1));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;


    for (int tc = 1; tc <= t; tc++) {
        ans = 1e9;
        people.clear();

        cin >> n;
        vector<pair<int, int>> peoplePos;
        vector<pair<int, int>> stairPos;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int x;
                cin >> x;
                if (x == 1) peoplePos.push_back({ i,j });
                else if (x > 1) {
                    stairPos.push_back({ i,j });
                    stairLen[stairPos.size() - 1] = x;
                }
            }
        }

        people.resize(peoplePos.size());

        for (int i = 0; i < people.size(); i++) {
            for (int j = 0; j < 2; j++) {
                people[i].dist[j] = abs(peoplePos[i].first - stairPos[j].first) + abs(peoplePos[i].second - stairPos[j].second);
            }
        }

        for (int mask = 0; mask < (1 << people.size()); mask++) {
            simulateAll(mask);
        }

        cout << "#" << tc << " " << ans + 1 << '\n';
    }

    return 0;
}