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

bool check() {
	for (Record re : records) {
		int sum = 0;

		for (int i = re.l; i <= re.r; i++) sum += cur[i];
	
		if (sum != re.s) return false;
	}
	return true;
}

bool isSmall() {
	for (int i = 1; i <= n; i++) {
		if (cur[i] < ans[i]) return true;
		if (cur[i] > ans[i]) return false;
	}
	return false;
}

void dfs(int idx) {
	if (idx == n + 1) {
		if (!check()) return;

		int sum = 0;
		for (int i = 1; i <= n; i++) sum += cur[i];

		if (sum > maxSum) {
			maxSum = sum;
			for (int i = 1; i <= n; i++) ans[i] = cur[i];
		}
		else if (sum == maxSum && isSmall()) {
			for (int i = 1; i <= n; i++) ans[i] = cur[i];
		}

		return;
	}

	for (int i = 0; i <= x; i++) {
		cur[idx] = i;
		dfs(idx + 1);
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

		for (int i = 0; i < m; i++) {
			int l, r, s;
			cin >> records[i].l >> records[i].r >> records[i].s;
		}

		dfs(1);
		
		cout << "#" << tc << " ";
		if (maxSum == -1) cout << -1;
		else {
			for (int i = 1; i <= n; i++) cout << ans[i] << " ";
		}
		cout << "\n";
	}

	return 0;
}