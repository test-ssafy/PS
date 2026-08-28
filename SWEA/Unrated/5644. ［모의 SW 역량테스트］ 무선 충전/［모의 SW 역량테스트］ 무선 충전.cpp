#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct BC {
	int y, x, c, p;
};

int n, m, a;
pair<int, int> v[11][11]{};
int dr[5]{ 0, -1, 0, 1, 0 };
int dc[5]{ 0, 0, 1, 0, -1 };

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> m >> a;

		vector<int> p1(m, 0);
		vector<int> p2(m, 0);
		for (int i = 0; i < m; i++) cin >> p1[i];
		for (int i = 0; i < m; i++) cin >> p2[i];

		vector<BC> bc(a);
		for (int i = 0; i < a; i++) cin >> bc[i].x >> bc[i].y >> bc[i].c >> bc[i].p;


		int r1 = 1, c1 = 1;
		int r2 = 10, c2 = 10;
		int ans = 0;

		for (int time = 0; time <= m; time++) {
			// -1 : 사용X
			vector<int> can1{ -1 };
			vector<int> can2{ -1 };

			for (int i = 0; i < a; i++) {
				if (abs(r1 - bc[i].y) + abs(c1 - bc[i].x) <= bc[i].c) can1.push_back(i);
				if (abs(r2 - bc[i].y) + abs(c2 - bc[i].x) <= bc[i].c) can2.push_back(i);
			}

			int maxCharge = 0;

			for (int b1 : can1) {
				for (int b2 : can2) {
					int charge = 0;

					if (b1 == -1 && b2 == -1) charge = 0;
					else if (b1 == -1) charge = bc[b2].p;
					else if (b2 == -1) charge = bc[b1].p;
					else if (b1 == b2) charge = bc[b1].p;
					else charge = bc[b1].p + bc[b2].p;

					maxCharge = max(maxCharge, charge);
				}
			}

			ans += maxCharge;

			if (time == m) continue;
			r1 += dr[p1[time]];
			c1 += dc[p1[time]];
			r2 += dr[p2[time]];
			c2 += dc[p2[time]];
		}

		cout << "#" << tc << " " << ans << "\n";
	}

	return 0;
}