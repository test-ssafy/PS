#include <iostream>
#include <vector>
using namespace std;

int dr[4]{-1, 1, 0, 0};
int dc[4]{0, 0, -1, 1};

int main() {
    
    int n, r, c;
    cin >> n >> r >> c;

    vector<vector<int>> v(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cin >> v[i][j];
    }

    cout << v[r][c] << " ";

    while (true) {
        int nextR = 0, nextC = 0;
        
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr <= 0 || nc <= 0 || nr > n || nc > n) continue;

            if (v[r][c] < v[nr][nc]) {
                nextR = nr;
                nextC = nc;
                break;
            }
        }

        if (nextR == 0) break;

        r = nextR;
        c = nextC;

        cout << v[r][c] << " ";
    }

    return 0;
}