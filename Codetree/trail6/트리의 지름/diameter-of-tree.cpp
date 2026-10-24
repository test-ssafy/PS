#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<pair<int,int>> adj[100001];
bool visited[100001];
int dist[100001];

void dfs(int cur) {
    visited[cur] = true;

    for (pair<int,int> next : adj[cur]) {
        int nextNode = next.first;
        int nextDist = next.second;

        if (visited[nextNode]) continue;
        dist[nextNode] = dist[cur] + nextDist;
        dfs(nextNode);
    }
}

int main() {
    cin >> n;

    for (int i=0; i<n-1; i++) {
        int a,b,dist;
        cin >> a >> b >> dist;
        adj[a].push_back({b,dist});
        adj[b].push_back({a,dist});
    }

    dfs(1);
    int farNode = 1;
    for (int i=1; i<=n; i++) {
        if (dist[i] > dist[farNode]) farNode = i;
    }

    fill(visited, visited+n+1, false);
    fill(dist, dist+n+1, 0);

    dfs(farNode);
    int answer = 0;
    for (int i=1; i<=n; i++) answer = max(answer, dist[i]);

    cout << answer;

    return 0;
}