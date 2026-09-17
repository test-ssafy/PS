#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int r, c, ans;
int v[20][20]{ 0 };
int dr[4]{ -1,1,0,0 };
int dc[4]{ 0,0,-1,1 };

void dfs(int curR, int curC, int cnt, int mask) {
	ans = max(ans, cnt);

	for (int dir = 0; dir < 4; dir++) {
		int nr = curR + dr[dir];
		int nc = curC + dc[dir];

		if (nr < 0 || nc < 0 || nr >= r || nc >= c) continue;
		if (cnt + 26 - __builtin_popcount(mask) <= ans) return;
		int bit = 1 << v[nr][nc];
		if (mask & bit) continue;

		dfs(nr, nc, cnt + 1, mask | bit);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	
	for (int tc = 1; tc <= t; tc++) {
		ans = 0;
		cin >> r >> c;
		
		for (int i = 0; i < r; i++) {
			string str;
			cin >> str;
			for (int j = 0; j < c; j++) v[i][j] = str[j] - 'A';
		}

		dfs(0, 0, 1, 1 << v[0][0]);

		cout << "#" << tc << " " << ans << "\n";
	}
}