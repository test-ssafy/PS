#include <iostream>
#include <algorithm>
using namespace std;

int price[4];
int month[13];
int dp[13];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		for (int i = 0; i < 4; i++) cin >> price[i];
		for (int i = 1; i <= 12; i++) cin >> month[i];

		dp[0] = 0;

		for (int i = 1; i <= 12; i++) {
			// 1일
			dp[i] = dp[i - 1] + month[i] * price[0];

			// 1달
			dp[i] = min(dp[i], dp[i - 1] + price[1]);

			// 3달
			if (i >= 3) dp[i] = min(dp[i], dp[i - 3] + price[2]);
		}

		int ans = min(dp[12], price[3]);

		cout << "#" << tc << " " << ans << "\n";
	}

	return 0;
}