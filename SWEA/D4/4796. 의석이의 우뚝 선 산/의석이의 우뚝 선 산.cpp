#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	for (int tc = 1; tc <= t; tc++) {
		int n;
		cin >> n;

		vector<int> v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];

		int u = 0, d = 0, ans = 0;
		for (int i = 0; i < n - 1; i++) {
			if (v[i] < v[i + 1]) {
				if (d > 0) {
					u = 0, d = 0;
				}
				u++;
			}
			else {
				ans += u;
				d++;
			}
		}

		cout << "#" << tc << " " << ans << "\n";
	}

	return 0;
}