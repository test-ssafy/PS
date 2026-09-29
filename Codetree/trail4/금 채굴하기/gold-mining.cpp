#include <iostream>
#include <cmath>

using namespace std;

int n, m;
int v[20][20];

int simulate(int r, int c, int k) {
    int cnt = 0;

    for (int nr = r - k; nr <= r + k; nr++) {
        if (nr < 0 || nr >= n) continue;

        for (int nc = c - k; nc <= c + k; nc++) {
            if (nc < 0 || nc >= n) continue;
            if (abs(r - nr) + abs(c - nc) > k) continue;

            if (v[nr][nc] == 1) cnt++;
        }
    }

    if (m * cnt >= 2 * k * k + 2 * k + 1) return cnt;
    return -1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> v[i][j];
    }

    int ans = 0;

    for (int k = 0; k <= 2 * n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int cnt = simulate(i, j, k);

                if (cnt != -1) ans = max(ans, cnt);
            }
        }
    }

    cout << ans;

    return 0;
}