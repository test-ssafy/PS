
#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> adj[100001];
int parent[100001];
bool visited[100001];

void dfs(int cur) {
    visited[cur] = true;

    for (int next : adj[cur]) {
        if (visited[next]) continue;

        parent[next] = cur;
        dfs(next);
    }
}

int main() {
    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1);

    for (int i = 2; i <= n; i++) cout << parent[i] << "\n";

    return 0;
}