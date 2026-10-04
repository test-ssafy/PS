#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> v(n+1, vector<int>(n+1,0));
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) cin >> v[i][j];
    }
    
    int minR = n;
    for (int c=k; c<=k+m-1; c++) {
        for (int r=1; r<=n; r++) {
            if (v[r][c] == 1) {
                minR = min(minR, r - 1);
                break;
            }
        }
    }
    
    for (int c=k; c<=k+m-1; c++) v[minR][c] = 1;

    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) cout << v[i][j] << " ";
        cout << "\n";
    }

    return 0;
}