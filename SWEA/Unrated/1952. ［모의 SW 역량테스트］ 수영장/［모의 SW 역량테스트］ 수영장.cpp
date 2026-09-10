#include <iostream>
#include <algorithm>
using namespace std;

int ans;
int price[4]{ 0 };
int month[13]{ 0 };

void dfs(int idx, int sum) {
	if (idx >= 13) {
		ans = min(ans, sum);
		return;
	}

	dfs(idx + 3, sum + price[2]);

	dfs(idx + 1, sum + price[1]);

	dfs(idx + 1, sum + price[0] * month[idx]);
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		for (int i = 0; i < 4; i++) cin >> price[i];
		for (int i = 1; i <= 12; i++) cin >> month[i];

		ans = price[3];

		dfs(0, 0);

		cout << "#" << tc << " " << ans << "\n";
	}

	return 0;
}