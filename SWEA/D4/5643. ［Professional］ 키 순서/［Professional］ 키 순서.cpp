#include <iostream>
#include <cstring>
using namespace std;

int n, m;
bool graph[501][501];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++) {
        cin >> n >> m;
        memset(graph, false, sizeof(graph));

        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;

            graph[a][b] = true;
        }

        // 플로이드-워셜
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (graph[i][k] && graph[k][j]) graph[i][j] = true;
                }
            }
        }

        int ans = 0;

        // 각 학생의 순위를 알 수 있는지 확인
        for (int i = 1; i <= n; i++) {
            int smaller = 0;
            int bigger = 0;

            for (int j = 1; j <= n; j++) {
                if (graph[j][i]) smaller++;
                if (graph[i][j]) bigger++;
            }

            if (smaller + bigger == n - 1) ans++;
        }

        cout << "#" << tc << " " << ans << '\n';
    }

    return 0;
}