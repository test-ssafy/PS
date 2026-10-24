#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int m;
vector<int> adj[10001];
int inDegree[10001];
bool visited[10001];

void dfs(int cur) {
    visited[cur] = true;

    for (int next : adj[cur]) {
        if (!visited[next]) dfs(next);
    }
}

int main() {
    cin >> m;

    for (int i=0; i<m; i++) {
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        inDegree[b]++;
    }

    bool check = true;
    int root = 0;
    int rootCnt = 0;
    for (int i=1; i<=10000; i++) {
        if (inDegree[i] == 0 && !adj[i].empty()) {
            root = i;
            rootCnt++;
        }
    }
    
    // 1. 들어오는 간선이 하나도 없는 루트 노드는 하나
    if (rootCnt != 1) check = false;

    // 2. 루트 노드를 제외한 모든 노드는 반드시 단 하나의 들어오는 간선이 존재
    for (int i=1; i<=10000 && check; i++) {
        if (i != root && (!adj[i].empty() || inDegree[i] > 0)) {
            if (inDegree[i] != 1) {
                check = false;
                break;
            }
        }
    }

    // 3. 루트에서 모든 노드에 도달 가능 & 경로는 유일
    if (root != 0) dfs(root);

    for (int i = 1; i <= 10000 && check; i++) {
        if ((!adj[i].empty() || inDegree[i] > 0) && !visited[i]) {
            check = false;
            break;
        }
    }

    cout << (check ? 1 : 0);

    return 0;
}