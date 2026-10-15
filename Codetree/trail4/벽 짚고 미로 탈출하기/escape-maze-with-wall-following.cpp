#include <iostream>
#include <string>
using namespace std;

int n, d, r, c;
int v[100][100];

int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };

int rightDir[4] = { 3, 2, 0, 1 };
int leftDir[4] = { 2, 3, 1, 0 };

bool visited[100][100][4];

int main() {
    cin >> n;

    int x, y;
    cin >> x >> y;

    r = x - 1;
    c = y - 1;
    d = 3;

    for (int i = 0; i < n; i++) {
        string str;
        cin >> str;

        for (int j = 0; j < n; j++) v[i][j] = (str[j] == '.') ? 1 : 0;
    }

    int time = 0;

    while (true) {
        if (visited[r][c][d]) {
            cout << -1;
            return 0;
        }
        visited[r][c][d] = true;

        int nr = r + dr[d];
        int nc = c + dc[d];

        if (nr >= 0 && nr < n && nc >= 0 && nc < n && v[nr][nc] == 0) {
            d = leftDir[d];
            continue;
        }

        if (nr < 0 || nr >= n || nc < 0 || nc >= n) {
            cout << time + 1;
            return 0;
        }

        int nd = rightDir[d];
        int checkR = nr + dr[nd];
        int checkC = nc + dc[nd];

        if (checkR >= 0 && checkR < n &&
            checkC >= 0 && checkC < n && v[checkR][checkC] == 0) {
            r = nr;
            c = nc;
            time++;
        }
        else {
            r = nr;
            c = nc;
            time++;

            d = nd;

            int tr = r + dr[d];
            int tc = c + dc[d];

            if (tr < 0 || tr >= n || tc < 0 || tc >= n) {
                cout << time + 1;
                return 0;
            }

            r = tr;
            c = tc;
            time++;
        }
    }

    return 0;
}