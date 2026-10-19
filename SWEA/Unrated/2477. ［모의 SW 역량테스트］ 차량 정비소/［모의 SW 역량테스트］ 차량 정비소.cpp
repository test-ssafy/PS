#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct People {
    int num, endTime, receptionNum, repairNum;
};

int t, n, m, k, a, b;
int reception[9]{ 0 };
int repair[9]{ 0 };
int receptionEnd[9]{ 0 };
int repairEnd[9]{ 0 };

int getReception(int arrive) {
    int idx = -1;

    for (int i = 0; i < n; i++) {
        if (receptionEnd[i] <= arrive) {
            idx = i;
            break;
        }
    }

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

    for (int i = 0; i < m; i++) {
        if (repairEnd[i] <= arrive) {
            idx = i;
            break;
        }
    }

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

        sort(people.begin(), people.end(), [&](People a, People b) {
            if (a.endTime == b.endTime) return a.receptionNum < b.receptionNum;
            return a.endTime < b.endTime;
            });

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