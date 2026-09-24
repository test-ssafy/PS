#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    int v[100][100]{0};
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) cin >> v[i][j];
    }

    int ans = 0;

    for (int r=0; r<n; r++) {
        int cnt = 1, maxCnt = 1;
        for (int c=1; c<n; c++) {
            if (v[r][c] != v[r][c-1]) cnt = 0;
            cnt++;
            maxCnt = max(maxCnt, cnt);
        }
        if (maxCnt >= m) ans++;
    }

    for (int c=0; c<n; c++) {
        int cnt = 1, maxCnt = 1;
        for (int r=1; r<n; r++) {
            if (v[r][c] != v[r-1][c]) cnt = 0;
            cnt++;
            maxCnt = max(maxCnt, cnt);
        }
        if (maxCnt >= m) ans++;
    }

    cout << ans;

    return 0;
}