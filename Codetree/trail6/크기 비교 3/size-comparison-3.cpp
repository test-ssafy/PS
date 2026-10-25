#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n,m;
vector<int> adj[32001];
int inDegree[32001];

void topology() {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i=1; i<=n; i++) {
        if (inDegree[i] == 0) {
            pq.push(i);
            inDegree[i]--;
        }
    }

    while(!pq.empty()) {
        int cur = pq.top();
        pq.pop();

        cout << cur << " ";
        
        for (int next : adj[cur]) {
            inDegree[next]--;
            if (inDegree[next] == 0) pq.push(next);
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i=0; i<m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        inDegree[b]++;
    }

    topology();

    return 0;
}