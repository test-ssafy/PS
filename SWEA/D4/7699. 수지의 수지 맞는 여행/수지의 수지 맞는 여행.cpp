#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

int r, c, ans;
vector<string> v;
int dr[4]{ -1,1,0,0 };
int dc[4]{ 0,0,-1,1 };
bool used[27]{ false };

void dfs(int curR, int curC, int cnt) {
	ans = max(ans, cnt);

	for (int dir = 0; dir < 4; dir++) {
		int nr = curR + dr[dir];
		int nc = curC + dc[dir];

		if (nr < 0 || nc < 0 || nr >= r || nc >= c) continue;

		if (used[v[nr][nc] - 'A']) continue;

		used[v[nr][nc] - 'A'] = true;
		dfs(nr, nc, cnt + 1);
		used[v[nr][nc] - 'A'] = false;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	
	for (int tc = 1; tc <= t; tc++) {
		memset(used, false, sizeof(used));
		ans = 0;
		cin >> r >> c;
		v.resize(r);
		for (int i = 0; i < r; i++) cin >> v[i];

		used[v[0][0] - 'A'] = true;
		dfs(0, 0, 1);

		cout << "#" << tc << " " << ans << "\n";
	}
}