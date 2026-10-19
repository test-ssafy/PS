#include <iostream>
#include <bitset>
using namespace std;

int n, m;
bitset<501> graph[501];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n >> m;

		for (int i = 1; i <= n; i++) graph[i].reset();

		for (int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;

			graph[a][b] = 1;
		}

		for (int k = 1; k <= n; k++) {
			for (int i = 1; i <= n; i++) {
				if (graph[i][k]) graph[i] |= graph[k];
			}
		}

		int ans = 0;

		for (int i = 1; i <= n; i++) {
			int cnt = 0;

			for (int j = 1; j <= n; j++) {
				if (graph[j][i] || graph[i][j]) cnt++;
			}

			if (cnt == n - 1) ans++;
		}

		cout << "#" << tc << " " << ans << '\n';
	}

	return 0;
}