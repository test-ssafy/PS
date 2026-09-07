#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		int n, m;
		cin >> n >> m;

		vector<pair<int, int>> house;
		int ans = 0;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int x;
				cin >> x;

				if (x == 1) house.push_back({ i, j });
			}
		}

		for (int r = 0; r < n; r++) {
			for (int c = 0; c < n; c++) {

				int cnt[41]{ 0 };

				for (const auto& h : house) {
					int dist = abs(r - h.first) + abs(c - h.second);
					cnt[dist + 1]++;
				}

				for (int k = 1; k < 41; k++) {
					cnt[k] += cnt[k - 1];

					int cost = k * k + (k - 1) * (k - 1);

					if (cnt[k] * m >= cost) ans = max(ans, cnt[k]);
				}
			}
		}

		cout << "#" << tc << " " << ans << '\n';
	}

	return 0;
}