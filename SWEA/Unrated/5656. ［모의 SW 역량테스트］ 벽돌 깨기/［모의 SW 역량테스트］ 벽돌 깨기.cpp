#include <iostream>
#include <algorithm>
#include <queue>
#include <tuple>
#include <cstring>
using namespace std;

int t, n, h, w, ans;
int v[15][12];

void boom(int map[15][12], int sr, int sc) {
	queue<tuple<int, int, int>> q;
	q.push({ sr,sc,map[sr][sc] - 1 });
	map[sr][sc] = 0;

	while (!q.empty()) {
		int curR = get<0>(q.front());
		int curC = get<1>(q.front());
		int curLen = get<2>(q.front());
		q.pop();

		for (int r = curR - curLen; r <= curR + curLen; r++) {
			if (r < 0 || r >= h) continue;

			if (map[r][curC] > 1) q.push({ r,curC,map[r][curC] - 1 });
			map[r][curC] = 0;
		}

		for (int c = curC - curLen; c <= curC + curLen; c++) {
			if (c < 0 || c >= w) continue;

			if (map[curR][c] > 1) q.push({ curR,c,map[curR][c] - 1 });
			map[curR][c] = 0;
		}
	}
}

void gravity(int map[15][12]) {
	for (int c = 0; c < w; c++) {
		int bottom = h - 1;

		for (int r = h - 1; r >= 0; r--) {
			if (map[r][c] != 0) {
				map[bottom][c] = map[r][c];
				if (bottom != r) map[r][c] = 0;
				bottom--;
			}
		}
	}
}

int cntBlock(int map[15][12]) {
	int cnt = 0;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) if (map[i][j] != 0) cnt++;
	}

	return cnt;
}

void dfs(int cnt, int map[15][12]) {
	int remain = cntBlock(map);

	if (remain == 0) {
		ans = 0;
		return;
	}

	if (cnt == n) {
		ans = min(ans, remain);
		return;
	}

	for (int c = 0; c < w; c++) {
		int nextMap[15][12];
		memcpy(nextMap, map, sizeof(nextMap));

		int r = -1;
		for (int i = 0; i < h; i++) {
			if (nextMap[i][c] != 0) {
				r = i;
				break;
			}
		}

		if (r == -1) {
			dfs(cnt + 1, nextMap);
			continue;
		}

		boom(nextMap, r, c);
		gravity(nextMap);

		dfs(cnt + 1, nextMap);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n >> w >> h;

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) cin >> v[i][j];
		}

		ans = h * w;
		dfs(0, v);

		cout << "#" << tc << " " << ans << "\n";
	}
}