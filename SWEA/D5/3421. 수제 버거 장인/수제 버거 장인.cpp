#include <iostream>
using namespace std;

int n, m;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n >> m;

		int conflict[21]{ 0 };
		for (int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			conflict[a] |= (1 << b);
			conflict[b] |= (1 << a);
		}

		int ans = 0;

		for (int mask = 0; mask < (1 << n); mask++) {
			bool valid = true;

			for (int i = 0; i < n; i++) {
				if (mask & (1 << i)) {
					if (conflict[i] & mask) {
						valid = false;
						break;
					}
				}
			}

			if (valid) ans++;
		}
 
		cout << "#" << tc << " " << ans << "\n";
	}

	return 0;
}