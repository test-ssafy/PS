#include <iostream>
#include <algorithm>
using namespace std;

int d, w, k;
int v[13][20];
int changed[13];
int ans;

bool check() {
    for (int c = 0; c < w; c++) {
        int prev = (changed[0] != -1) ? changed[0] : v[0][c];
        int cnt = 1;
        bool passed = (k == 1);

        for (int r = 1; r < d && !passed; r++) {
            int cur = (changed[r] != -1) ? changed[r] : v[r][c];

            if (prev == cur) cnt++;
            else {
                cnt = 1;
                prev = cur;
            }

            if (cnt >= k) passed = true;
        }

        if (!passed) return false;
    }

    return true;
}

void dfs(int r, int curCnt) {
    if (curCnt >= ans) return;

    if (check()) {
        ans = curCnt;
        return;
    }

    if (r == d) return;

    dfs(r + 1, curCnt);

    if (curCnt + 1 >= ans) return;

    changed[r] = 0;
    dfs(r + 1, curCnt + 1);

    changed[r] = 1;
    dfs(r + 1, curCnt + 1);

    changed[r] = -1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++) {
        cin >> d >> w >> k;

        fill(changed, changed + d, -1);

        for (int r = 0; r < d; r++) {
            for (int c = 0; c < w; c++) {
                cin >> v[r][c];
            }
        }

        ans = k;

        if (k == 1) ans = 0;
        else dfs(0, 0);

        cout << "#" << tc << " " << ans << '\n';
    }

    return 0;
}