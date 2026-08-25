#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> v;
int dp[1 << 10];

int dfs(int mask) {
	if (mask == 0) return 0;
	if (dp[mask] != -1) return dp[mask];

	int res = 0;
	for (int i = 0; i < n; i++) {
		if (!(mask & (1 << i))) continue;

		int left = i - 1;
		while (left >= 0 && !(mask & (1 << left))) left--;
		int right = i + 1;
		while (right < n && !(mask & (1 << right))) right++;
	
		int score;
		if (left >= 0 && right < n) score = v[left] * v[right];
		else if (left >= 0) score = v[left];
		else if (right < n) score = v[right];
		else score = v[i];

		int newMask = mask & ~(1 << i);

		res = max(res, score + dfs(newMask));
	}

	return dp[mask] = res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n;
		
		v.resize(n);
		for (int i = 0; i < n; i++) cin >> v[i];
		fill(dp, dp + (1 << n), -1);

		int fullMask = (1 << n) - 1;

		int ans = dfs(fullMask);

		cout << "#" << tc << " " << ans << "\n";
	}

	return 0;
}