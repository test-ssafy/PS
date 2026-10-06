#include <iostream>
#include <vector>
using namespace std;

int dr[8]{-1,1,0,0,-1,-1,1,1};
int dc[8]{0,0,-1,1,-1,1,-1,1};

int main() {
    int n, m;
    cin >> n >> m;

    int size = n*n;

    vector<vector<int>> v(n, vector<int>(n,0));
    vector<pair<int,int>> points(size+1, {0,0});
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cin >> v[i][j];
            points[v[i][j]] = {i,j};
        }
    }

    while(m--) {
        for (int i=1; i<=size; i++) {
            int r = points[i].first;
            int c = points[i].second;

            int maxVal = 0;
            int nextR = r, nextC = c;
            for (int i=0; i<8; i++) {
                int nr = r+dr[i];
                int nc = c+dc[i];

                if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;

                if (maxVal < v[nr][nc]) {
                    maxVal = v[nr][nc];
                    nextR = nr;
                    nextC = nc;
                }
            }

            swap(v[r][c], v[nextR][nextC]);
            points[i] = {nextR, nextC};
            points[maxVal] = {r, c};
        }
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) cout << v[i][j] << " ";
        cout << "\n";
    }

    return 0;
}