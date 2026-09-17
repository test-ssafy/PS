#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

struct Record {
	int l, r, s;
};

int n, x, m, maxSum;
int cur[7];
int ans[7];
vector<Record> records;

bool isSmall() {
	for (int i = 1; i <= n; i++) {
		if (cur[i] < ans[i]) return true;
		if (cur[i] > ans[i]) return false;
	}
	return false;
}

void dfs(int idx, int total) {
	if (idx == n + 1) {
		if (total > maxSum) {
			maxSum = total;

			for (int i = 1; i <= n; i++)
				ans[i] = cur[i];
		}
		else if (total == maxSum && isSmall()) {
			for (int i = 1; i <= n; i++)
				ans[i] = cur[i];
		}

		return;
	}

	for (int i = 0; i <= x; i++) {
		cur[idx] = i;

		bool pos = true;

		for (Record re : records) {
			// 구간 미완성 시 검사 X
			if (re.r > idx) continue;

			int sum = 0;

			for (int j = re.l; j <= re.r; j++) sum += cur[j];

			// 구간 검사 후 햄스터 수와 다르면 실패
			if (sum != re.s) {
				pos = false;
				break;
			}
		}

		if (pos) dfs(idx + 1, total + i);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		records.clear();
		maxSum = -1;

		cin >> n >> x >> m;
		records.resize(m);

		for (int i = 0; i < m; i++) cin >> records[i].l >> records[i].r >> records[i].s;

		dfs(1, 0);

		cout << "#" << tc << " ";
		if (maxSum == -1) cout << -1;
		else {
			for (int i = 1; i <= n; i++) cout << ans[i] << " ";
		}
		cout << "\n";
	}

	return 0;
}