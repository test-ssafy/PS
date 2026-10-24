#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int parent[100001];

int Find(int a) {
    if (parent[a] == a) return a;

    return parent[a] = Find(parent[a]);
}

void Union(int a, int b) {
    a = Find(a);
    b = Find(b);

    if (a==b) return;

    parent[b] = a;
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i=1; i<=n; i++) parent[i] = i;

    for (int i=0; i<m; i++) {
        int cmd, a, b;
        cin >> cmd >> a >> b;

        if (cmd == 0) Union(a,b);
        else {
            a = Find(a);
            b = Find(b);

            cout << (a==b ? 1 : 0) << "\n";
        }
    }
    
    return 0;
}