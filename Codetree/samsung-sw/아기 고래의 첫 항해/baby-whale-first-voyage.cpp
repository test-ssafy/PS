#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

// 상하좌우
int dr[4]{ -1,1,0,0 };
int dc[4]{ 0,0,-1,1 };

int direction[4][4]{
    {0,1,2,3},
    {2,3,1,0},
    {3,2,0,1},
    {1,0,3,2}
};

// BFS 거리 배열 생성
vector<vector<int>> bfs(int sr, int sc, int n, const vector<vector<int>>& board) {
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, -1));
    queue<pair<int, int>> q;

    dist[sr][sc] = 0;
    q.push({ sr, sc });

    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr <= 0 || nc <= 0 || nr > n || nc > n) continue;

            // 암초
            if (board[nr][nc] == 1) continue;

            // BFS에서 이미 방문
            if (dist[nr][nc] != -1) continue;

            dist[nr][nc] = dist[r][c] + 1;
            q.push({ nr, nc });
        }
    }

    return dist;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, r, c, d;
    cin >> n >> r >> c >> d;
    // 입력은 1부터 상하좌우 -> 매핑은 0부터니까 입력받자마자 d--
    d--;

    int k = 0;
    vector<vector<int>> v(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> v[i][j];
            if (v[i][j] == 0) k++;
        }
    }

    vector<vector<bool>> visited(n + 1, vector<bool>(n + 1, false));

    vector<pair<int, int>> ans;

    visited[r][c] = true;
    ans.push_back({ r,c });
    k--;

    while (k > 0) {

        bool moved = false;

        // 방문하지 않은 바다가 있는지 체크
        for (int i = 0; i < 4; i++) {
            int nd = direction[i][d];
            int nr = r + dr[nd];
            int nc = c + dc[nd];

            if (nr <= 0 || nc <= 0 || nr > n || nc > n) continue;
            if (v[nr][nc] == 1 || visited[nr][nc]) continue;

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

        vector<vector<int>> distFromCur = bfs(r, c, n, v);
        int tr = -1;
        int tc = -1;
        int minDist = 1e9;

        for (int i=1; i<=n; i++) {
            for (int j = 1; j <= n; j++) {

                if (v[i][j] == 1) continue;
                if (visited[i][j]) continue;
                if (distFromCur[i][j] == -1) continue;

                if (distFromCur[i][j] < minDist) {
                    minDist = distFromCur[i][j];

                    tr = i;
                    tc = j;
                }
            }
        }
        
        // 선택한 칸 까지 최단 거리로 이동
        // 매 이동마다 선택한 칸까지의 거리가 1 줄어드는 인접한 칸 중 하나로 이동
        // 그러한 칸이 여러개 -> 좌하우상 순서로 우선순위 선택
        // 도착 후 바라보는 방향은 마지막 이동방향으로 선택
        // tr, tc 는 목적지
        // r,c는 현재 위치
        // 즉 r,c -> tr,tc로 이동해야함

        // T에서 시작해서 S로 이동
        // -> 실제로 이동하는건 아니고, 거리를 저장하기 위함
        vector<vector<int>> distToTarget = bfs(tr, tc, n, v);
        // 우선순위 -> 좌, 하, 우, 상
        int moveR[4]{ 0,1,0,-1 };
        int moveC[4]{ -1,0,1,0 };
        int moveDir[4]{ 2,1,3,0 };

        while (r != tr || c != tc) {
            for (int i = 0; i < 4; i++) {
                int nr = r + moveR[i];
                int nc = c + moveC[i];

                if (nr <= 0 || nc <= 0 || nr > n || nc > n) continue;
                if (v[nr][nc] == 1) continue;

                // 현재 거리 -1인 애들로만 이동해야함
                // 여러개면 좌 -> 하 -> 우 -> 상
                if (distToTarget[nr][nc] != (distToTarget[r][c] - 1)) continue;

                r = nr;
                c = nc;
                d = moveDir[i];

                if (!visited[nr][nc]) {
                    visited[r][c] = true;
                    ans.push_back({ r, c });
                    k--;
                }

                break;
            }
        }
    }

    for (pair<int, int> p : ans) cout << p.first << " " << p.second << "\n";

}