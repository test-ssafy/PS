#include <iostream>
#include <queue>
#include <tuple>
#include <cstring>
using namespace std;

int n, m, r, c, l, ans;
int v[50][50]{ 0 };
bool visited[50][50]{ false };

int dr[4]{ -1,1,0,0 };
int dc[4]{ 0,0,-1,1 };

bool pipe[8][4]{
	{0,0,0,0},
	{1,1,1,1},
	{1,1,0,0},
	{0,0,1,1},
	{1,0,0,1},
	{0,1,0,1},
	{0,1,1,0},
	{1,0,1,0}
};

int opposite[4]{ 1,0,3,2 };

void bfs() {
	queue<tuple<int, int, int>> q;
	q.push({ r,c,1 });
	visited[r][c] = true;
	ans = 1;

	while (!q.empty()) {
		int curR = get<0>(q.front());
		int curC = get<1>(q.front());
		int curTime = get<2>(q.front());
		q.pop();

		if (curTime == l) continue;

		int curNum = v[curR][curC];

		for (int i = 0; i < 4; i++) {
			if (!pipe[curNum][i]) continue;

			int nr = curR + dr[i];
			int nc = curC + dc[i];

			if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
			if (visited[nr][nc]) continue;
			if (v[nr][nc] == 0) continue;

			int nextNum = v[nr][nc];
			if (!pipe[nextNum][opposite[i]]) continue;

			visited[nr][nc] = true;
			ans++;

			q.push({ nr, nc, curTime + 1 });
		}

	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n >> m >> r >> c >> l;
		ans = 1;
		memset(visited, false, sizeof(visited));

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) cin >> v[i][j];
		}

		bfs();

		cout << "#" << tc << " " << ans << "\n";
	}

	return 0;
}