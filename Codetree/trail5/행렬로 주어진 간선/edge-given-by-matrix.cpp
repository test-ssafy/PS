#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define INF 1e9

int n;
vector<int> adj[101];
int dist[101][101];

void floyd() {
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) dist[i][j] = (i==j) ? 0 : INF;
    }

    for (int i=1; i<=n; i++) {
        for (int curNode : adj[i]) {
            dist[i][curNode] = min(dist[i][curNode], 1);
        }
    }

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
    cin >> n;
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            int check;
            cin >> check;

            if (check == 1) adj[i].push_back(j);
        }
    }

    floyd();

    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            cout << (dist[i][j]==INF ? 0 : 1) << " ";
        }
        cout << "\n";
    }

    return 0;
}