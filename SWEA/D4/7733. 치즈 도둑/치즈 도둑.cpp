#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int n, ans, cnt;
int v[100][100]{ 0 };
int dr[4]{ -1,1,0,0 };
int dc[4]{ 0,0,-1,1 };
bool visited[100][100]{ false };

void bfs(int r, int c, int time) {
	if (visited[r][c] || v[r][c] <= time) return;

	queue<pair<int, int>> q;
	q.push({ r,c });
	visited[r][c] = true;

	while (!q.empty()) {
		int curR = q.front().first;
		int curC = q.front().second;
		q.pop();


		for (int i = 0; i < 4; i++) {
			int nr = curR + dr[i];
			int nc = curC + dc[i];


			if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;

			if (!visited[nr][nc] && v[nr][nc] > time) {
				visited[nr][nc] = true;
				q.push({ nr,nc });

			}
		}
	}

	cnt++;
}
 
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		ans = 0;
		cin >> n;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) cin >> v[i][j];
		}

		for (int time = 0; time <= 100; time++) {
			memset(visited, false, sizeof(visited));
			cnt = 0;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) bfs(i, j, time);
			}
			ans = max(ans, cnt);
		}

		cout << "#" << tc << " " << ans << "\n";
	}

	return 0;
}