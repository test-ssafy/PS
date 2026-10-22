
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define INF 1e9

int n, m;
vector<pair<int, int>> graph[1001];
vector<int> dist;

void dijkstra() {

    dist[1] = 0;

    priority_queue<pair<int, int>,vector<pair<int, int>>,greater<pair<int, int>>> pq;

    // {가중치, 노드번호}
    pq.push({0, 1});

    while (!pq.empty()) {
        int curCost = pq.top().first;
        int curNode = pq.top().second;
        pq.pop();

        if (curCost > dist[curNode]) continue;

        for (auto next : graph[curNode]) {
            int nextNode = next.first;
            int nextCost = next.second;

            int newCost = curCost + nextCost;

            if (newCost < dist[nextNode]) {
                dist[nextNode] = newCost;
                pq.push({newCost, nextNode});
            }
        }
    }
}

int main() {
    cin >> n >> m;

    dist.assign(n + 1, INF);

    for (int i = 0; i < m; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;

        graph[from].push_back({to, weight});
    }

    dijkstra();

    for (int i = 2; i <= n; i++) {
        if (dist[i] == INF) cout << -1 << '\n';
        else cout << dist[i] << '\n';
    }

    return 0;
}
