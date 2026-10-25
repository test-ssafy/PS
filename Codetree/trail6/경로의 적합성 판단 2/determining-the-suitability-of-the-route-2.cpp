#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int parent[100001];
int sz[100001];

int Find(int a) {
    if (parent[a] == a) return a;
    return parent[a] = Find(parent[a]);
}

void Union(int a, int b) {
    a = Find(a);
    b = Find(b);

    if (a==b) return;
    
    if (sz[a] < sz[b]) swap(a,b);
    parent[b] = a;
    sz[a] += sz[b];
}

int main() {
    int n,m,k;
    cin >> n >> m >> k;

    for (int i=1; i<=n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }

    for (int i=0; i<m; i++) {
        int a,b;
        cin >> a >> b;
        Union(a,b);
    }

    vector<int> path(k);
    for (int i=0; i<k; i++) cin >> path[i];

    bool pos = true;
    for (int i=0; i<k-1; i++) {
        int a = path[i];
        int b = path[i+1];

        if (Find(a) != Find(b)) {
            pos = false;
            break;
        }
    }

    cout << (pos ? 1 : 0);

    return 0;
}