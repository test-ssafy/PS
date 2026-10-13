
#include <iostream>
#include <vector>
using namespace std;

int n, m, q;
vector<vector<int>> v;

bool isEffect(int r, int checkR) {
    for (int i = 0; i < m; i++) {
        if (v[r][i] == v[checkR][i]) return true;
    }

    return false;
}

void newV(int r, char d) {
    vector<int> tmp(m);

    if (d == 'L') {
        for (int i = 0; i < m; i++) tmp[i] = v[r][(i - 1 + m) % m];
    }
    else {
        for (int i = 0; i < m; i++) tmp[i] = v[r][(i + 1) % m];
    }

    v[r] = tmp;
}

int main() {
    cin >> n >> m >> q;

    v.assign(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cin >> v[i][j];
    }

    while (q--) {
        int r;
        char d;
        cin >> r >> d;
        r--;

        newV(r, d);

        int up = r;
        char upD = d;
        while (up > 0) {
            if (!isEffect(up, up - 1)) break;
            up--;

            upD = (upD == 'L' ? 'R' : 'L');
            newV(up, upD);
        }

        int down = r;
        char downD = d;
        while (down < n - 1) {
            if (!isEffect(down, down + 1)) break;
            down++;

            downD = (downD == 'L' ? 'R' : 'L');
            newV(down, downD);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cout << v[i][j] << " ";
        cout << "\n";
    }

    return 0;
}
