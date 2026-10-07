#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;

struct Vacuum {
    int r, c;
};

int dr[5]{0,-1,1,0,0};
int dc[5]{0,0,0,-1,1};
int checkDir[4][4]{
    {0,1,2,4},
    {0,2,3,4},
    {0,1,2,3},
    {0,1,3,4}
};

int main() {
    int n,k,l;
    cin >> n >> k >> l;

    vector<vector<int>> v(n+1, vector<int>(n+1,0));
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) cin >> v[i][j];
    }
    
    vector<Vacuum> vacuums(k);
    for (int i=0; i<k; i++) cin >> vacuums[i].r >> vacuums[i].c;

    while(l--) {
        // Step1
        vector<vector<bool>> isVacuum(n + 1, vector<bool>(n + 1, false));
        for (Vacuum va : vacuums) isVacuum[va.r][va.c] = true;

        for (Vacuum& va : vacuums) {

            int sr = va.r;
            int sc = va.c;

            // 현재 청소기로부터 각 칸까지의 최단거리
            vector<vector<int>> dist(n + 1, vector<int>(n + 1, -1));
            queue<pair<int,int>> q;
            q.push({sr, sc});
            dist[sr][sc] = 0;

            while (!q.empty()) {
                int r = q.front().first;
                int c = q.front().second;
                q.pop();

                for (int dir = 1; dir <= 4; dir++) {
                    int nr = r + dr[dir];
                    int nc = c + dc[dir];

                    if (nr <= 0 || nc <= 0 || nr > n || nc > n) continue;
                    if (v[nr][nc] < 0) continue;
                    if (isVacuum[nr][nc]) continue;
                    if (dist[nr][nc] != -1) continue;

                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }

            // 가장 가까운 먼지 찾기
            int bestDist = 1e9;
            int nextR = sr;
            int nextC = sc;

            for (int r = 1; r <= n; r++) {
                for (int c = 1; c <= n; c++) {

                    // 먼지 없음
                    if (v[r][c] <= 0) continue;
                    // 도달 불가능
                    if (dist[r][c] == -1) continue;

                    if (dist[r][c] < bestDist) {
                        bestDist = dist[r][c];

                        nextR = r;
                        nextC = c;
                    }
                }
            }

            isVacuum[sr][sc] = false;

            va.r = nextR;
            va.c = nextC;

            isVacuum[nextR][nextC] = true;
        }
        

        // Step2
        // 아 4가지가 가능한데
        // ㅏ , ㅜ , ㅓ , ㅗ 순으로 우선순위
        // 이때 방향은 그 4가지에서 가장 큰 값으로 하는데
        // 그 때 합이 같다면 위의 우선순위 순으로 선택
        // 그럼 일단 십자가 다 더하고
        // - r c-1
        // - r-1 c
        // - r c+1
        // - r+1 c
        for (Vacuum& va : vacuums) {
            int r = va.r;
            int c = va.c;

            int maxVal = -1;
            int bestDir = 0;
            for (int dir=0; dir<4; dir++) {
                int sum = 0;
                for (int i=0; i<4; i++) {
                    int curDir = checkDir[dir][i];

                    int nr = r+dr[curDir];
                    int nc = c+dc[curDir];

                    if (nr <= 0 || nc <= 0 || nr > n || nc > n) continue;
                    if (v[nr][nc] <= 0) continue;
                    
                    sum += min(20, v[nr][nc]);
                }

                if (maxVal < sum) {
                    maxVal = sum;
                    bestDir = dir; 
                }
            }

            for (int i=0; i<4; i++) {
                int curDir = checkDir[bestDir][i];

                int nr = r+dr[curDir];
                int nc = c+dc[curDir];

                if (nr <= 0 || nc <= 0 || nr > n || nc > n) continue;
                if (v[nr][nc] <= 0) continue;

                v[nr][nc] = max(0, v[nr][nc] - 20);
            }
        }
        
        // Step3
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) {
                if (v[i][j] > 0) v[i][j] += 5;
            }
        }

        // Step4
        vector<vector<int>> nextV = v;
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) {
                if (v[i][j] != 0) continue;

                int sum = 0;
                for (int dir=1; dir<=4; dir++) {
                    int nr = i+dr[dir];
                    int nc = j+dc[dir];

                    if (nr <= 0 || nc <= 0 || nr > n || nc > n) continue;
                    if (v[nr][nc] <= 0) continue;

                    sum += v[nr][nc];
                }

                nextV[i][j] = sum / 10;
            }
        }
        v = nextV;
        
        // Step5
        int ans = 0;
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) {
                if (v[i][j] > 0) ans += v[i][j];
            }
        }

        cout << ans << "\n";
    }


    return 0;
}