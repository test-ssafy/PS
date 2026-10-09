#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    int n,m;
    cin >> n >> m;
    vector<int> v(n, 0);
    unordered_map<int, int> um;
    for (int i=0; i<n; i++) {
        cin >> v[i];
        um[v[i]]++;
    }

    for (int i=0; i<m; i++) {
        int x;
        cin >> x;
        cout << um[x] << " ";
    }
    
    return 0;
}