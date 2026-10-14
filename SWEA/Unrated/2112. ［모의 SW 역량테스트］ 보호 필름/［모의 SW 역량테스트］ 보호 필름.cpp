#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int t, d, w, k;
vector<vector<int>> v;
vector<int> changed;

bool isEnd;

bool check() {
	for (int c = 0; c < w; c++) {
		int prev = (changed[0] != -1) ? changed[0] : v[0][c];
		int cnt = 1;

		for (int r = 1; r < d; r++) {
			int cur = (changed[r] != -1) ? changed[r] : v[r][c];

			if (prev == cur) cnt++;
			else {
				cnt = 1;
				prev = cur;
			}

			if (cnt >= k) break;
		}

		if (cnt < k) return false;
	}

	return true;
}

void dfs(int r, int curCnt, int cnt) {
	if (isEnd) return;

	if (curCnt > cnt) return;

	if (r == d) {
		if (check()) isEnd = true;
		return;
	}

	// 변경 X
	changed[r] = -1;
	dfs(r + 1, curCnt, cnt);
	
	// 변경 A
	changed[r] = 0;
	dfs(r + 1, curCnt + 1, cnt);

	// 변경 B
	changed[r] = 1;
	dfs(r + 1, curCnt + 1, cnt);

	changed[r] = -1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> t;
	for (int tc = 1; tc <= t; tc++) {

		isEnd = false;

		cin >> d >> w >> k;
		v.assign(d, vector<int>(w, 0));
		changed.assign(d, -1);
		for (int i = 0; i < d; i++) {
			for (int j = 0; j < w; j++) cin >> v[i][j];
		}

		int l = 0, r = d;
		while (l <= r) {
			int mid = (l + r) / 2;

			isEnd = false;

			dfs(0, 0, mid);

			if (isEnd) r = mid - 1;
			else l = mid + 1;
		}

		cout << "#" << tc << " " << l << "\n";
	}
}