#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, maxVal, minVal;
int v[12]{ 0 };
int cnt[4]{ 0 };

int calculate(int flag, int a, int b) {
    if (flag == 0) return a + b;
    else if (flag == 1) return a - b;
    else if (flag == 2) return a * b;
    else return a / b;
}

void dfs(int idx, int sum) {
    if (idx == n) {
        maxVal = max(maxVal, sum);
        minVal = min(minVal, sum);
        return;
    }

    for (int flag = 0; flag < 4; flag++) {
        if (cnt[flag] == 0) continue;

        cnt[flag]--;
        dfs(idx + 1, calculate(flag, sum, v[idx]));
        cnt[flag]++;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++) {
        maxVal = -1e9, minVal = 1e9;
        
        cin >> n;

        for (int i = 0; i < 4; i++) cin >> cnt[i];
        for (int i = 0; i < n; i++) cin >> v[i];

        dfs(1, v[0]);

        cout << "#" << tc << " " << maxVal - minVal << '\n';
    }

    return 0;
}