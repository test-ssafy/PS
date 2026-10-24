#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
int parent[51];
vector<int> adj[51];

void dfs(int cur) {
    parent[cur] = -2;
    
    for (int i=0; i<n; i++) {
        if (parent[i] == cur) dfs(i);
    }
}

int main() {
    cin >> n;
    for (int i=0; i<n; i++) cin >> parent[i];
    int remove;
    cin >> remove;

    dfs(remove);

    bool isParent[51]{false};
    for (int i=0; i<n; i++) {
        if (isParent[i] == -2) continue;

        if (parent[i] >= 0) {
            isParent[parent[i]] = true;
        }
    }
    
    int ans = 0;
    for (int i=0; i<n; i++) {
        if (parent[i] == -2) continue;
        
        if (!isParent[i]) ans++;
    }

    cout << ans;

    return 0;
}