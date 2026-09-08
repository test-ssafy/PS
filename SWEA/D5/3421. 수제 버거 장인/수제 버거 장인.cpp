#include <iostream>
using namespace std;

int n, m;
int conflict[21];
int ans;

void dfs(int idx, int mask) {
	if (idx == n) {
		ans++;
		return;
	}

	// idx를 선택할 수 있는 경우
	if ((conflict[idx] & mask) == 0) dfs(idx + 1, mask | (1 << idx));
	
	// idx를 선택하지 않는 경우
	dfs(idx + 1, mask);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n >> m;

		for (int i = 0; i < n; i++) conflict[i] = 0;

		for (int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;
			a--; b--;

			conflict[a] |= (1 << b);
			conflict[b] |= (1 << a);
		}

		ans = 0;

		dfs(0, 0);

		cout << "#" << tc << " " << ans << "\n";
	}

	return 0;
}