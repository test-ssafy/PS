#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define INF 1e9

int n,m,k;
vector<pair<int,int>> graph[20001];
vector<int> dist(20001, INF);

void dijkstra(int start) {
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while(!pq.empty()) {
        int curCost = pq.top().first;
        int curNode = pq.top().second;
        pq.pop();
        
        if (curCost > dist[curNode]) continue;

        for (auto next : graph[curNode]) {
            int nextNode = next.first;
            int nextCost = next.second + curCost;

            if (dist[nextNode] <= nextCost) continue;

            dist[nextNode] = nextCost;
            pq.push({nextCost, nextNode});
        }
    }
}

int main() {
    cin >> n >> m >> k;
    
    for (int i=0; i<m; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;

        graph[from].push_back({to, cost});
        graph[to].push_back({from, cost});
    }

    dijkstra(k);

    for (int i=1; i<=n; i++) {
        if (dist[i] == INF) cout << -1 << "\n";
        else cout << dist[i] << "\n";
    }

    return 0;
}