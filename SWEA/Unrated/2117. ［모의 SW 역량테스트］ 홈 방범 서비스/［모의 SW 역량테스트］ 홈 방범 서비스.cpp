#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int n, m;
int v[20][20]{ 0 };

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++) {

        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) cin >> v[i][j];
        }

        int ans = 0;

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {

                for (int k = 1; k <= 2 * n - 1; k++) {
                    int cnt = 0;

                    for (int i = 0; i < n; i++) {
                        for (int j = 0; j < n; j++) {
                            if (v[i][j] == 1 && abs(r - i) + abs(c - j) < k) cnt++;
                        }
                    }

                    int cost = k * k + (k - 1) * (k - 1);

                    if (cnt * m >= cost) ans = max(ans, cnt);
                }
            }
        }

        cout << "#" << tc << " " << ans << '\n';
    }

    return 0;
}