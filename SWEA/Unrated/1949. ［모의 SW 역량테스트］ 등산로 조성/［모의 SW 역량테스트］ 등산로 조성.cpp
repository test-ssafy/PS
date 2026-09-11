#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int n, k, ans;
int v[8][8]{ 0 };
bool visited[8][8]{ false };
vector<pair<int, int>> start;
int dr[4]{ -1,1,0,0 };
int dc[4]{ 0,0,-1,1 };

// change == true -> 공사 했음
void dfs(int r, int c, int height, int len, bool change) {
	ans = max(ans, len);
	
	for (int i = 0; i < 4; i++) {
		int nr = r + dr[i];
		int nc = c + dc[i];

		if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
		if (visited[nr][nc]) continue;
		
		if (v[nr][nc] < height) {
			visited[nr][nc] = true;
			dfs(nr, nc, v[nr][nc], len + 1, change);
			visited[nr][nc] = false;
		}
		else if (!change && v[nr][nc] - k < height) {
			visited[nr][nc] = true;
			dfs(nr, nc, height - 1, len + 1, true);
			visited[nr][nc] = false;
		}
	}

}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n >> k;
		ans = 0;
		start.clear();
		memset(visited, false, sizeof(visited));

		int maxVal = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> v[i][j];
				maxVal = max(maxVal, v[i][j]);
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (v[i][j] == maxVal) start.push_back({ i,j });
			}
		}

		for (pair<int, int> p : start) {
			visited[p.first][p.second] = true;
			dfs(p.first, p.second, maxVal, 1, false);
			visited[p.first][p.second] = false;
		}

		cout << "#" << tc << " " << ans << "\n";
	}

	return 0;
}