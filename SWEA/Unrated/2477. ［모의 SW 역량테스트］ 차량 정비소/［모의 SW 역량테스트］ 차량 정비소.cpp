#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct People {
    int num, endTime, receptionNum, repairNum;
};

bool cmp(People p1, People p2) {
    if (p1.endTime == p2.endTime) return p1.receptionNum < p2.receptionNum;
    return p1.endTime < p2.endTime;
}

int n, m, k, a, b;
int reception[9]{ 0 };
int repair[9]{ 0 };
int receptionEnd[9]{ 0 };
int repairEnd[9]{ 0 };

int getReception(int arrive) {
    int idx = -1;

    for (int i = 0; i < n; i++) {
        // 빈 창구
        if (receptionEnd[i] <= arrive) {
            idx = i;
            break;
        }
    }

    // 빈 창구 없으면 가장 빨리 끝나는 창구
    if (idx == -1) {
        idx = 0;

        for (int i = 0; i < n; i++) {
            if (receptionEnd[i] < receptionEnd[idx]) idx = i;
        }
    }

    return idx;
}

int getRepair(int arrive) {
    int idx = -1;

    // 빈 창구
    for (int i = 0; i < m; i++) {
        if (repairEnd[i] <= arrive) {
            idx = i;
            break;
        }
    }

    // 빈 창구 없으면 가장 빨리 끝나는 창구
    if (idx == -1) {
        idx = 0;

        for (int i = 0; i < m; i++) {
            if (repairEnd[i] < repairEnd[idx]) idx = i;
        }
    }

    return idx;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++) {
        int ans = 0;
        memset(receptionEnd, 0, sizeof(receptionEnd));
        memset(repairEnd, 0, sizeof(repairEnd));

        cin >> n >> m >> k >> a >> b;
        for (int i = 0; i < n; i++) cin >> reception[i];
        for (int i = 0; i < m; i++) cin >> repair[i];

        vector<People> people;
        for (int i = 0; i < k; i++) {
            int arrive;
            cin >> arrive;

            int window = getReception(arrive);

            int start = max(arrive, receptionEnd[window]);
            int end = start + reception[window];

            receptionEnd[window] = end;

            people.push_back({ i + 1, end, window + 1, 0 });
        }

        sort(people.begin(), people.end(), cmp);

        for (People& p : people) {
            int window = getRepair(p.endTime);

            int start = max(p.endTime, repairEnd[window]);
            int end = start + repair[window];

            repairEnd[window] = end;

            p.repairNum = window + 1;
        }

        for (People p : people) {
            if (p.receptionNum == a && p.repairNum == b) ans += p.num;
        }

        if (ans == 0) ans = -1;

        cout << "#" << tc << " " << ans << '\n';
    }

    return 0;
}