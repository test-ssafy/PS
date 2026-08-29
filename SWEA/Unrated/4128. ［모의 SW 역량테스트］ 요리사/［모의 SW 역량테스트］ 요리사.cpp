#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int n, ans;
int v[16][16]{ 0 };
bool used[16]{ false };


void dfs(int idx, int cnt, int sumA) {
    // 종료조건
    if (cnt == n / 2) {
        int sumB = 0;
        
        for (int i = 0; i < n; i++) {
            if (used[i]) continue;

            for (int j = i + 1; j < n; j++) {
                if (!used[j]) sumB += (v[i][j] + v[j][i]);
            }
        }

        ans = min(ans, abs(sumA - sumB));

        return; 
    }

    for (int i = idx; i < n; i++) {
        if (used[i]) continue;

        int plus = 0;
        for (int j = 0; j < i; j++) {
            if (used[j]) plus += (v[i][j] + v[j][i]);
        }

        used[i] = true;
        dfs(i + 1, cnt + 1, sumA + plus);
        used[i] = false;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++) {
        ans = 1e9;
        memset(used, false, sizeof(used));
        cin >> n;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) cin >> v[i][j];
        }

        dfs(0, 0, 0);

        cout << "#" << tc << " " << ans << '\n';
    }

    return 0;
}