#include <iostream>
#include <vector>
using namespace std;

#define MOD 8

int k;
int v[5][8]{ 0 };
int checkIdx[5][2]{ 0 };

void check(bool lotate[5], int lotateDir[5], int num, int dir) {
    lotate[num] = true;
    lotateDir[num] = dir;

    for (int i = num; i > 1; i--) {
        int curVal = v[i][checkIdx[i][0]];
        int nextVal = v[i - 1][checkIdx[i - 1][1]];

        if (curVal != nextVal) {
            lotate[i - 1] = true;
            lotateDir[i - 1] = -lotateDir[i];
        }
        else break;
    }

    for (int i = num; i < 4; i++) {
        int curVal = v[i][checkIdx[i][1]];
        int nextVal = v[i + 1][checkIdx[i + 1][0]];

        if (curVal != nextVal) {
            lotate[i + 1] = true;
            lotateDir[i + 1] = -lotateDir[i];
        }
        else break;
    }
}

void move(int num, int dir) {

    bool lotate[5]{ false };
    int lotateDir[5]{ 0 };

    check(lotate, lotateDir, num, dir);

    for (int i = 1; i <= 4; i++) {
        if (!lotate[i]) continue;

        if (lotateDir[i] == 1) {
            checkIdx[i][0] = (checkIdx[i][0] - 1 + MOD) % MOD;
            checkIdx[i][1] = (checkIdx[i][1] - 1 + MOD) % MOD;
        }
        else {
            checkIdx[i][0] = (checkIdx[i][0] + 1) % MOD;
            checkIdx[i][1] = (checkIdx[i][1] + 1) % MOD;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++) {
        cin >> k;

        for (int i = 1; i <= 4; i++) {
            for (int j = 0; j < 8; j++) cin >> v[i][j];
        }

        for (int i = 1; i <= 4; i++) {
            checkIdx[i][0] = 6;
            checkIdx[i][1] = 2;
        }

        for (int i = 0; i < k; i++) {
            int num, dir;
            cin >> num >> dir;
            move(num, dir);
        }

        int ans = 0;
        for (int i = 1; i <= 4; i++) {
            int idx = (checkIdx[i][0] + 2) % MOD;
            if (v[i][idx] == 1) ans += (1 << (i - 1));
        }

        cout << "#" << tc << " " << ans << "\n";
    }

    return 0;
}