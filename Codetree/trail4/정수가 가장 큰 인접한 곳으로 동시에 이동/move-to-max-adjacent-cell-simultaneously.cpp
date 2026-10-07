#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

int dr[4]{-1,1,0,0};
int dc[4]{0,0,-1,1};

int main() {

    int n,m,t;
    cin >> n >> m >> t;

    vector<vector<int>> v(n+1, vector<int>(n+1,0));
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) cin >> v[i][j];
    }

    vector<vector<int>> count(n+1, vector<int>(n+1,0));
    set<pair<int,int>> s;
    for (int i=0; i<m; i++) {
        int r,c;
        cin >> r >> c;
        s.insert({r,c});
        count[r][c] = 1;
    }


    while(t--) {
        vector<vector<int>> nextCount(n+1, vector<int>(n+1,0));
        set<pair<int,int>> nextSet;

        for (pair<int,int> p : s) {
            int curR = p.first;
            int curC = p.second;

            int nextR = curR;
            int nextC = curC;
            int maxVal = 0;
            for (int i=0; i<4; i++) {
                int nr = curR + dr[i];
                int nc = curC + dc[i];

                if (nr<=0||nc<=0||nr>n||nc>n) continue;

                if (maxVal < v[nr][nc]) {
                    maxVal = v[nr][nc];
                    nextR = nr;
                    nextC = nc;
                }
            }

            nextCount[nextR][nextC]++;
        }

        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) {
                if (nextCount[i][j] == 1) nextSet.insert({i, j});
                if (nextCount[i][j] > 1) nextCount[i][j] = 0; 
            }
        }

        count = nextCount;
        s = nextSet;
    }
    
    cout << s.size();

    return 0;
}