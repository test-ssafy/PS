#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;

int n, q;
vector<vector<int>> v;
vector<int> area;
vector<pair<int, int>> startPos;
int dr[4]{ -1,1,0,0 };
int dc[4]{ 0,0,-1,1 };

void insertMicro(int id, int x1, int y1, int x2, int y2) {
    int r1 = n - y2, c1 = x1;
    int r2 = n - y1, c2 = x2;

    for (int r = r1; r < r2; r++) {
        for (int c = c1; c < c2; c++) v[r][c] = id;
    }
}

void updateArea() {
    fill(area.begin(), area.end(), 0);
    fill(startPos.begin(), startPos.end(), make_pair(-1, -1));

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            int id = v[r][c];

            if (id == 0) continue;
            area[id]++;

            if (startPos[id].first == -1) startPos[id] = { r,c };
        }
    }
}

int bfs(int id, int sr, int sc) {
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    q.push({ sr, sc });
    visited[sr][sc] = true;

    int cnt = 1;

    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
            if (v[nr][nc] != id) continue;
            if (visited[nr][nc]) continue;

            visited[nr][nc] = true;
            cnt++;
            q.push({ nr, nc });
        }
    }

    return cnt;
}

void checkDivide(int id) {
    for (int i = 1; i < id; i++) {
        if (area[i] == 0) continue;

        int sr = startPos[i].first;
        int sc = startPos[i].second;

        int connected = bfs(i, sr, sc);

        if (connected != area[i]) {
            for (int r = 0; r < n; r++) {
                for (int c = 0; c < n; c++) {
                    if (v[r][c] == i) v[r][c] = 0;
                }
            }

            area[i] = 0;
            startPos[i] = { -1,-1 };
        }
    }
}

vector<int> getOrder() {
    vector<int> order;

    for (int id = 1; id <= q; id++) {
        if (area[id] > 0) order.push_back(id);
    }

    sort(order.begin(), order.end(), [&](int a, int b) {
        if (area[a] == area[b]) return a < b;
        return area[a] > area[b];
        });

    return order;
}

// 실제 형태 추출
vector<pair<int, int>> getShape(int id) {
    vector<pair<int, int>> shape;

    int minR = n;
    int minC = n;

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (v[r][c] != id) continue;

            shape.push_back({ r,c });
            minR = min(minR, r);
            minC = min(minC, c);
        }
    }

    // 가장 위쪽, 왼쪽 칸을 기준으로 상대좌표 전환
    for (pair<int, int>& p : shape) {
        p.first -= minR;
        p.second -= minC;
    }

    return shape;
}

bool canMove(const vector<vector<int>>& newV, const vector<pair<int, int>>& shape, int r, int c) {
    for (pair<int, int> p : shape) {
        int nr = r + p.first;
        int nc = c + p.second;

        if (nr < 0 || nc < 0 || nr >= n || nc >= n) return false;
        if (newV[nr][nc] != 0) return false;
    }
    return true;
}

void moveGroup() {
    vector<vector<int>> newV(n, vector<int>(n, 0));
    vector<int> order = getOrder();

    for (int id : order) {
        vector<pair<int, int>> shape = getShape(id);
        bool moved = false;

        // x 좌표가 작은 것 우선&#xA;        // 같다면 y 좌표가 작은 것 우선
        for (int c = 0; c < n && !moved; c++) {
            for (int r = n - 1; r >= 0 && !moved; r--) {
                if (!canMove(newV, shape, r, c)) continue;

                for (pair<int, int> p : shape) newV[r + p.first][c + p.second] = id;
                moved = true;
            }
        }

        if (!moved) area[id] = 0;
    }

    v = newV;
}

long long calculate() {
    set<pair<int, int>> adj;
    int checkR[2]{ 1,0 };
    int checkC[2]{ 0,1 };

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            int id1 = v[r][c];
            if (id1 == 0) continue;

            for (int i = 0; i < 2; i++) {
                int nr = r + checkR[i];
                int nc = c + checkC[i];

                if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;

                int id2 = v[nr][nc];
                if (id2 == 0 || id1 == id2) continue;

                int a = min(id1, id2);
                int b = max(id1, id2);

                adj.insert({ a, b });
            }
        }
    }

    long long res = 0;
    for (pair<int, int> p : adj) {
        res += (1LL * area[p.first] * area[p.second]);
    }

    return res;
}

int main() {
    cin >> n >> q;
    v.assign(n, vector<int>(n, 0));
    area.assign(q + 1, 0);
    startPos.assign(q + 1, { -1,-1 });

    int remain = q;
    for (int id = 1; id <= q; id++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        // Step1
        insertMicro(id, x1, y1, x2, y2);
        updateArea();
        checkDivide(id);

        // Step2
        moveGroup();

        // Step3       
        cout << calculate() << "\n";
    }

    return 0;
}