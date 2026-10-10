#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Turtle {
    int r, c, state;
};

struct Volcano {
    int r, c, p, curP;
};

int dr[4]{ 0,1,0,-1 };
int dc[4]{ 1,0,-1,0 };

int main() {

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> v(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> v[i][j];
    }

    vector<Turtle> turtles(m, { 0,0,0 });
    for (int i = 0; i < m; i++) cin >> turtles[i].r >> turtles[i].c;

    vector<Volcano> volcanoes(k, { 0,0,0,0 });
    for (int i = 0; i < k; i++) cin >> volcanoes[i].r >> volcanoes[i].c >> volcanoes[i].p;

    vector<int> ans(m, -1);

    for (int turn = 1; turn <= 100; turn++) {

        // Step1
        for (int id = 0; id < m; id++) {
            if (turtles[id].state > 0) continue;
            int r = turtles[id].r;
            int c = turtles[id].c;

            queue<pair<int, int>> q;
            q.push({ n - 1, n - 1 });
            vector<vector<int>> turtleMap(n, vector<int>(n, -1));
            for (int i = 0; i < m; i++) {
                if (turtles[i].state > 0) continue;

                turtleMap[turtles[i].r][turtles[i].c] = i;
            }
            vector<vector<int>> dist(n, vector<int>(n, -1));
            dist[n - 1][n - 1] = 0;

            while (!q.empty()) {
                int curR = q.front().first;
                int curC = q.front().second;
                q.pop();

                for (int i = 0; i < 4; i++) {
                    int nr = curR + dr[i];
                    int nc = curC + dc[i];

                    if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
                    if (v[nr][nc] > 0) continue;
                    if (turtleMap[nr][nc] != -1 && turtleMap[nr][nc] != id) continue;
                    if (dist[nr][nc] != -1) continue;

                    dist[nr][nc] = dist[curR][curC] + 1;
                    q.push({ nr, nc });
                }
            }

            if (dist[r][c] == -1) continue;

            // 우선순위 -> 우하좌상
            int nextR = r;
            int nextC = c;

            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
                if (v[nr][nc] > 0) continue;
                if (turtleMap[nr][nc] != -1 && turtleMap[nr][nc] != id) continue;

                if (dist[nr][nc] == dist[r][c] - 1) {
                    nextR = nr;
                    nextC = nc;
                    break;
                }
            }

            turtles[id].r = nextR;
            turtles[id].c = nextC;
            if (nextR == n - 1 && nextC == n - 1) {
                turtles[id].state = 1;
                ans[id] = turn;
            }
        }

        // Step2
        for (Volcano& v : volcanoes) v.curP += 10;

        // Step3
        vector<vector<int>> sumFire(n, vector<int>(n, 0));
        vector<bool> fired(k, false);
        queue<int> fireQ;

        // Step 3.1
        for (int i = 0; i < k; i++) {
            if (volcanoes[i].curP >= volcanoes[i].p) {
                fired[i] = true;
                fireQ.push(i);
            }
        }

        // Step 3.2
        while (!fireQ.empty()) {
            int curIdx = fireQ.front();
            fireQ.pop();

            int r = volcanoes[curIdx].r;
            int c = volcanoes[curIdx].c;
            int p = volcanoes[curIdx].p;

            sumFire[r][c] += p;

            for (int dir = 0; dir < 4; dir++) {
                int nr = r;
                int nc = c;
                int curP = p;

                while (true) {
                    nr += dr[dir];
                    nc += dc[dir];

                    curP /= 2;

                    if (nr < 0 || nc < 0 || nr >= n || nc >= n) break;
                    if (curP == 0) break;
                    if (v[nr][nc] == 1) break;

                    sumFire[nr][nc] += curP;
                }
            }

            for (int i = 0; i < k; i++) {
                if (fired[i]) continue;

                int r = volcanoes[i].r;
                int c = volcanoes[i].c;
                int p = volcanoes[i].p;
                int curP = volcanoes[i].curP;

                if (curP + sumFire[r][c] >= p) {
                    fired[i] = true;
                    fireQ.push(i);
                }
            }
        }

        // Step 3.3
        for (Turtle& t : turtles) {
            if (t.state > 0) continue;

            if (sumFire[t.r][t.c] >= 20) {
                t.state = 2;
                v[t.r][t.c] = 2;
            }
        }

        // Step4
        for (int i = 0; i < k; i++) {
            if (fired[i]) volcanoes[i].curP = 0;
        }
    }

    for (int i : ans) cout << i << "\n";

    return 0;
}