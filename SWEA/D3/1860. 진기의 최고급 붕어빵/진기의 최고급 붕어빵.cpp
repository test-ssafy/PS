#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		string ans = "";

		int n, m, k;
		cin >> n >> m >> k;

		int arrived[11112]{ 0 };
		int sum[11112]{ 0 };
		int maxTime = 0;

		for (int i = 0; i < n; i++) {
			int time;
			cin >> time;
			maxTime = max(maxTime, time);
			arrived[time]++;
		}

		bool check = true;
		if (arrived[0] > 0) check = false;

		for (int i = 1; i <= maxTime; i++) {
			sum[i] = sum[i - 1];
			if (i%m == 0) sum[i] += k;

			if (sum[i] < arrived[i]) {
				check = false;
				break;
			}
			else sum[i] -= arrived[i];
		}
		
		if (check) ans = "Possible";
		else ans = "Impossible";


		cout << "#" << tc << " " << ans << "\n";
	}
}