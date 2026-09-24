#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    int v[20][20]{0};
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) cin >> v[i][j];
    }

    int ans = 0;
    for (int i=0; i<n-2; i++) {
        for (int j=0; j<n-2; j++) {
            int sum = 0;

            for (int k=i; k<i+3; k++) {
                for (int l=j; l<j+3; l++) {
                    sum += v[k][l];
                }
            }

            ans = max(ans, sum);
        }
    }

    cout << ans;

    return 0;
}