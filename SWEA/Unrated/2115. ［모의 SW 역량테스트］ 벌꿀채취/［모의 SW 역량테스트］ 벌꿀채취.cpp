#include <iostream>
#include <algorithm>
using namespace std;

int n, m, c;
int v[10][10];
int profit[10][10];

int getMax(int r, int start) {
	int res = 0;

	for (int mask = 0; mask < (1 << m); mask++) {
		int sum = 0, money = 0;

		for (int i = 0; i < m; i++) {
			if (mask & (1 << i)) {
				sum += v[r][start + i];
				money += v[r][start + i] * v[r][start + i];
			}
		}

		if (sum <= c) res = max(res, money);
	}

	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n >> m >> c;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) cin >> v[i][j];
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= n - m; j++) profit[i][j] = getMax(i, j);
		}

		int ans = 0;

		for (int r1 = 0; r1 < n; r1++) {
			for (int c1 = 0; c1 <= n - m; c1++) {

				for (int r2 = 0; r2 < n; r2++) {
					for (int c2 = 0; c2 <= n - m; c2++) {

						// 같은 행에서 겹치는 경우
						if (r1 == r2) {
							if (c1 < c2 + m && c2 < c1 + m) continue;
						}

						ans = max(ans, profit[r1][c1] + profit[r2][c2]);
					}
				}
			}
		}

		cout << "#" << tc << " " << ans << '\n';
	}

	return 0;
}