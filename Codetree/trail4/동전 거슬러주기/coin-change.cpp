#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> coin(n, 0);
    for (int i=0; i<n; i++) cin >> coin[i];
    vector<int> dp(m+1, 1e9);
    dp[0] = 0;

    for (int i=1; i<=m; i++) {
        for (int j=0; j<n; j++) {
            if (i >= coin[j]) {
                if (dp[i - coin[j]] == 1e9) continue;

                dp[i] = min(dp[i], dp[i-coin[j]]+1);
            }
        }
    }
    
    cout << ((dp[m] == 1e9) ? -1 : dp[m]);

    return 0;
}