#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int n, r, c, d;
vector<vector<int>> v;
vector<vector<bool>> visited;
int dr[4]{ -1,1,0,0 };
int dc[4]{ 0,0,-1,1 };
int direction[4][4]{
    {0,1,2,3},
    {2,3,1,0},
    {3,2,0,1},
    {1,0,3,2}
};

vector<vector<int>> bfs(int sr, int sc) {
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, -1));
    queue<pair<int, int>> q;
    
    dist[sr][sc] = 0;
    q.push({ sr,sc });

    while (!q.empty()) {
        int curR = q.front().first;
        int curC = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nr = curR + dr[i];
            int nc = curC + dc[i];

            if (nr <= 0 || nc <= 0 || nr > n || nc > n) continue;
            if (v[nr][nc] == 1) continue;
            if (dist[nr][nc] != -1) continue;

            dist[nr][nc] = dist[curR][curC] + 1;
            q.push({ nr,nc });
        }
    }

    return dist;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> r >> c >> d;
    d--;
    v.assign(n + 1, vector<int>(n + 1, 0));
    visited.assign(n + 1, vector<bool>(n + 1, false));
    int k = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> v[i][j];
            if (v[i][j] == 0) k++;
        }
    }

    vector<pair<int, int>> ans;
    ans.push_back({ r,c });
    visited[r][c] = true;
    k--;

    while (k > 0) {

        bool moved = false;

        for (int i = 0; i < 4; i++) {
            int nd = direction[i][d];
            int nr = r + dr[nd];
            int nc = c + dc[nd];

            if (nr <= 0 || nc <= 0 || nr > n || nc > n) continue;
            if (v[nr][nc] == 1) continue;
            if (visited[nr][nc]) continue;

            r = nr;
            c = nc;
            d = nd;

            visited[r][c] = true;
            ans.push_back({ r,c });
            k--;
            moved = true;
            break;
        }

        if (moved) continue;

        vector<vector<int>> dist = bfs(r, c);
        int tr = -1;
        int tc = -1;
        int minDist = 1e9;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (v[i][j] == 1) continue;
                if (visited[i][j]) continue;
                if (dist[i][j] == -1) continue;

                if (minDist > dist[i][j]) {
                    minDist = dist[i][j];
                    tr = i;
                    tc = j;
                }
            }
        }

        vector<vector<int>> distToTarget = bfs(tr, tc);
        int moveR[4]{ 0,1,0,-1 };
        int moveC[4]{ -1,0,1,0 };
        int moveDir[4]{ 2,1,3,0 };

        while (r != tr || c != tc) {
            for (int i = 0; i < 4; i++) {
                int nr = r + moveR[i];
                int nc = c + moveC[i];

                if (nr <= 0 || nc <= 0 || nr > n || nc > n) continue;
                if (v[nr][nc] == 1) continue;

                if (distToTarget[nr][nc] != (distToTarget[r][c] -1)) continue;

                r = nr;
                c = nc;
                d = moveDir[i];

                if (!visited[r][c]) {
                    visited[r][c] = true;
                    ans.push_back({ r,c });
                    k--;
                }

                break;
            }
        }
    }

    for (pair<int, int> p : ans) cout << p.first << " " << p.second << "\n";
}