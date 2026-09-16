#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

int n;
vector<string> v;

int dr[8]{ -1, -1, -1, 0, 0, 1, 1, 1 };
int dc[8]{ -1, 0, 1, -1, 1, -1, 0, 1 };

bool check(int r, int c) {
	for (int d = 0; d < 8; d++) {
		int nr = r + dr[d];
		int nc = c + dc[d];

		if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
		if (v[nr][nc] == '*') return false;
	}

	return true;
}

void bfs(int r, int c) {
	queue<pair<int, int>> q;

	q.push({ r,c });

	v[r][c] = 'c';

	while (!q.empty()) {
		int curR = q.front().first;
		int curC = q.front().second;
		q.pop();

		if (!check(curR, curC)) continue;

		for (int d = 0; d < 8; d++) {
			int nr = curR + dr[d];
			int nc = curC + dc[d];

			if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;

			if (v[nr][nc] != '.') continue;

			v[nr][nc] = 'c';
			q.push({ nr, nc });
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n;

		v.resize(n);
		for (int i = 0; i < n; i++) cin >> v[i];

		int ans = 0;

		for (int r = 0; r < n; r++) {
			for (int c = 0; c < n; c++) {

				if (v[r][c] != '.') continue;

				if (check(r, c)) {
					ans++;
					bfs(r, c);
				}
			}
		}

		for (int r = 0; r < n; r++) {
			for (int c = 0; c < n; c++) {
				if (v[r][c] == '.') ans++;
			}
		}

		cout << '#' << tc << ' ' << ans << '\n';
	}

	return 0;
}