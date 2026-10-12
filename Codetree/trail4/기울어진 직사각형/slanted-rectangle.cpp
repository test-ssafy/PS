
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, ans = 0;
vector<vector<int>> v;

int dr[4] = {-1, -1, 1, 1};
int dc[4] = {1, -1, -1, 1};

void calc(int r, int c, int d1, int d2) {
    int curR = r;
    int curC = c;
    int sum = 0;

    int len[4] = {d1, d2, d1, d2};

    for (int dir = 0; dir < 4; dir++) {
        for (int i = 0; i < len[dir]; i++) {
            curR += dr[dir];
            curC += dc[dir];

            if (curR < 0 || curR >= n ||
                curC < 0 || curC >= n) {
                return;
            }

            sum += v[curR][curC];
        }
    }

    ans = max(ans, sum);
}

int main() {
    cin >> n;
    v.assign(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> v[i][j];
        }
    }

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            for (int d1 = 1; d1 < n; d1++) {
                for (int d2 = 1; d2 < n; d2++) {
                    calc(r, c, d1, d2);
                }
            }
        }
    }

    cout << ans << "\n";

    return 0;
}
