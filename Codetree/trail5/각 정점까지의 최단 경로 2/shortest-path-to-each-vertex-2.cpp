#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define INF 1e9

int n, m;
vector<pair<int,int>> adj[101];
int dist[101][101];

void floydWarshall() {
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) dist[i][j] = (i==j) ? 0 : INF;
    }

    for (int i=1; i<=n; i++) {
        for (auto cur : adj[i]) {
            int curNode = cur.first;
            int curCost = cur.second;

            dist[i][curNode] = min(dist[i][curNode], curCost);
        }
    }

    // 즉 i->j 간의 구간에서
    // i - > k -> j 가 더 최소인 곳이 있는지 판단하는거
    // 그러면 i k / k j
    for (int k=1; k<=n; k++) {
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) {
                if (dist[i][k] == INF || dist[k][j] == INF) continue;

                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    
}

int main() {
    
    cin >> n >> m;
    for (int i=0; i<m; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;

        adj[from].push_back({to, weight});
    }

    floydWarshall();

    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            cout << ((dist[i][j] == INF) ? -1 : dist[i][j]) << " ";
        }
        cout << "\n";
    }
    
    return 0;
}