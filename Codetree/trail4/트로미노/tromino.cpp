#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n,m;
    cin >> n >> m;

    int v[200][200]{0};
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) cin >> v[i][j];
    }

    int ans = 0;

    for (int r=0; r<n; r++) {
        for (int c=0; c<m-2; c++) {
            int sum = 0;
            for (int i=c; i<c+3; i++) sum += v[r][i];
            ans = max(ans, sum);
        }
    }

    for (int c=0; c<m; c++) {
        for (int r=0; r<n-2; r++) {
            int sum = 0;
            for (int i=r; i<r+3; i++) sum += v[i][c];
            ans = max(ans, sum);
        }
    }

    for (int r=0; r<n-1; r++) {
        for (int c=0; c<m-1; c++) {
            int sum = 0;
            sum += (v[r][c] + v[r+1][c] + v[r][c+1] + v[r+1][c+1]);
            int sum1 = sum - v[r][c];
            int sum2 = sum - v[r+1][c];
            int sum3 = sum - v[r][c+1];
            int sum4 = sum - v[r+1][c+1];

            ans = max({ans, sum1, sum2, sum3, sum4});
        }
    }

    cout << ans;

    return 0;
}