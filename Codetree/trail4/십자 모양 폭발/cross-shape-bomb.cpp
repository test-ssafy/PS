#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> v(n, vector<int>(n,0));
    int r,c;

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) cin >> v[i][j];
    }

    cin >> r >> c;
    r--; c--;
    int len = v[r][c] - 1;

    for (int nr = r-len; nr <= r+len; nr++) {
        if (nr < 0 || nr >= n) continue;
        v[nr][c] = 0;
    }

    for (int nc = c-len; nc <= c+len; nc++) {
        if (nc < 0 || nc >= n) continue;
        v[r][nc] = 0;
    }

    vector<vector<int>> ans(n, vector<int>(n,0));
    
    for (int i=0; i<n; i++) {
        int curIdx = n-1;
        for (int j=n-1; j>=0; j--) {
            if (v[j][i] == 0) continue;

            ans[curIdx--][i] = v[j][i];
        }

        for (int j=curIdx; j>=0; j--) ans[j][i] = 0;
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) cout << ans[i][j] << " ";
        cout << "\n";
    }

    return 0;
}