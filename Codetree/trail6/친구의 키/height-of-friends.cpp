#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n,m;
vector<int> adj[100001];
int inDegree[100001];

void topologySort() {
    queue<int> q;
    
    for (int i=1; i<=n; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
            inDegree[i]--;
        }
    }

    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        cout << cur << " ";

        for (int next : adj[cur]) {
            inDegree[next]--;
            if (inDegree[next] == 0) q.push(next);
        }
    }
}

int main() {
    cin >> n >> m;

    for (int i=0; i<m; i++) {
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        inDegree[b]++;
    }

    topologySort();

    return 0;
}