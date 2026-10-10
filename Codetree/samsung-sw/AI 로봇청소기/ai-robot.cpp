#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Robot {
    int r, c;
};

int n, k, l;
vector<vector<int>> v;
vector<Robot> robots;
int dr[5]{ 0,1,0,-1,0 };
int dc[5]{ 1,0,-1,0,0 };

vector<vector<int>> getDist(int sr, int sc) {
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, -1));
    vector<vector<bool>> isRobot(n + 1, vector<bool>(n + 1, false));
    for (Robot robot : robots) isRobot[robot.r][robot.c] = true;

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
            if (v[nr][nc] == -1) continue;
            if (isRobot[nr][nc]) continue;
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

    cin >> n >> k >> l;
    v.assign(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cin >> v[i][j];
    }
    robots.assign(k, { -1,-1 });
    for (int i = 0; i < k; i++) cin >> robots[i].r >> robots[i].c;

    while (l--) {
        // Step1
        for (Robot& robot : robots) {
            vector<vector<int>> dist = getDist(robot.r, robot.c);

            int r = robot.r;
            int c = robot.c;
            int minDist = 1e9;
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (v[i][j] <= 0) continue;
                    if (dist[i][j] == -1) continue;

                    if (minDist > dist[i][j]) {
                        minDist = dist[i][j];
                        r = i;
                        c = j;
                    }
                }
            }

            robot.r = r;
            robot.c = c;
        }

        // Step2
        // 우 하 좌 상 본인
        // int dr[5]{ 0,1,0,-1,0 };
        // int dc[5]{ 1,0,-1,0,0 };
        int direction[4][4]{
            {0, 1, 3, 4},
            {0, 1, 2, 4},
            {1, 2, 3, 4},
            {0, 2, 3, 4}
        };

        for (Robot& robot : robots) {
            int r = robot.r;
            int c = robot.c;

            int maxSum = -1;
            int nd = 0;
            for (int d = 0; d < 4; d++) {
                int sum = 0;

                for (int i = 0; i < 4; i++) {
                    int dir = direction[d][i];
                    int nr = r + dr[dir];
                    int nc = c + dc[dir];

                    if (nr <= 0 || nc <= 0 || nr > n || nc > n) continue;
                    if (v[nr][nc] == -1) continue;

                    sum += min(20, v[nr][nc]);
                }

                if (maxSum < sum) {
                    maxSum = sum;
                    nd = d;
                }
            }

            for (int i = 0; i < 4; i++) {
                int dir = direction[nd][i];
                int nr = r + dr[dir];
                int nc = c + dc[dir];

                if (nr <= 0 || nc <= 0 || nr > n || nc > n) continue;
                if (v[nr][nc] == -1) continue;

                v[nr][nc] = max(0, v[nr][nc] - 20);
            }
        }

        // Step3
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (v[i][j] > 0) v[i][j] += 5;
            }
        }

        // Step4
        vector<vector<int>> newV = v;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (v[i][j] == 0) {
                    int sum = 0;

                    for (int d = 0; d < 4; d++) {
                        int nr = i + dr[d];
                        int nc = j + dc[d];

                        if (nr <= 0 || nc <= 0 || nr > n || nc > n) continue;
                        if (v[nr][nc] == -1) continue;

                        sum += v[nr][nc];
                    }

                    newV[i][j] += sum / 10;
                }
            }
        }
        v = newV;

        // Step5
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (v[i][j] > 0) ans += v[i][j];
            }
        }

        cout << ans << "\n";
    }

    return 0;
}