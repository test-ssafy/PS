#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, l, ans;
vector<pair<int, int>> v;

void dfs(int idx, int sumT, int sumK) {
	if (sumK > l) return;

	if (idx == v.size()) {
		ans = max(ans, sumT);
		return;
	}

	dfs(idx + 1, sumT + v[idx].first, sumK + v[idx].second);
	
	// 선택 X
	dfs(idx + 1, sumT, sumK);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		ans = 0;
		v.clear();
		cin >> n >> l;

		// {맛, 칼로리}
		v.assign(n, {});
		for (int i = 0; i < n; i++) cin >> v[i].first >> v[i].second;

		dfs(0, 0, 0);
		
		cout << "#" << tc << " " << ans << "\n";
	}

	return 0;
}