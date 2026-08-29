#include <iostream>
#include <vector>
using namespace std;

int v[4][8];
int idx[4];

void rotate(int num, int dir) {

    bool move[4]{ false };
    int rotateDir[4]{ 0 };

    move[num] = true;
    rotateDir[num] = dir;

    for (int i = num; i > 0; i--) {
        int cur = v[i][(idx[i] + 6) % 8];
        int next = v[i - 1][(idx[i - 1] + 2) % 8];

        if (cur == next) break;

        move[i - 1] = true;
        rotateDir[i - 1] = -rotateDir[i];
    }

    for (int i = num; i < 3; i++) {
        int cur = v[i][(idx[i] + 2) % 8];
        int next = v[i + 1][(idx[i + 1] + 6) % 8];

        if (cur == next) break;

        move[i + 1] = true;
        rotateDir[i + 1] = -rotateDir[i];
    }

    for (int i = 0; i < 4; i++) {
        if (!move[i]) continue;
        
        idx[i] = (idx[i] - rotateDir[i] + 8) % 8;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++) {
        int k;
        cin >> k;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 8; j++) cin >> v[i][j];
        }

        for (int i = 0; i < 4; i++) idx[i] = 0;

        for (int i = 0; i < k; i++) {
            int num, dir;
            cin >> num >> dir;

            rotate(num - 1, dir);
        }

        int ans = 0;
        for (int i = 0; i < 4; i++) {
            if (v[i][idx[i]] == 1) ans += (1 << i);
        }

        cout << "#" << tc << " " << ans << '\n';
    }

    return 0;
}