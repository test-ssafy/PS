#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int n, ans;
int v[102][102]{ 0 };
int block[6][4]{
	{},
	{ 1, 3, 0, 2 },
	{ 3, 0, 1, 2 },
	{ 2, 0, 3, 1 },
	{ 1, 2, 3, 0 },
	{ 1, 0, 3, 2 }
};
vector<pair<int, int>> wormhole[5];
int dr[4]{ -1,1,0,0 };
int dc[4]{ 0,0,-1,1 };
// 반대방향으로 그대로 돌아가는 경우
int opposite[4]{ 1, 0, 3, 2 };

void simulate(int sr, int sc, int dir) {
	int r = sr;
	int c = sc;
	int score = 0;

	while (true) {
		// 현재 방향으로 1칸 이동
		r += dr[dir];
		c += dc[dir];

		if ((r == sr && c == sc) || v[r][c] == -1) {
			ans = max(ans, score);
			break;
		}

		int val = v[r][c];

		if (1 <= val && val <= 5) {
			score++;
			int nd = block[val][dir];

			// 방금 부딪힌 블록 때문에 왔던 방향의 정반대로 돌아가는 경우
			if (nd == opposite[dir]) {
				ans = max(ans, score * 2 - 1);
				return;
			}

			dir = nd;
			continue;
		}

		if (val >= 6) {
			int idx = val - 6;
			
			if (wormhole[idx][0].first == r && wormhole[idx][0].second == c) {
				r = wormhole[idx][1].first;
				c = wormhole[idx][1].second;
			}
			else {
				r = wormhole[idx][0].first;
				c = wormhole[idx][0].second;
			}
			continue;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		ans = 0;
		for (int i = 0; i < 5; i++) wormhole[i].clear();
		
		cin >> n;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> v[i][j];
				if (v[i][j] >= 6) wormhole[v[i][j] - 6].push_back({ i,j });
			}
		}
		for (int i = 0; i <= n + 1; i++) {
			v[0][i] = 5;
			v[n + 1][i] = 5;
			v[i][0] = 5;
			v[i][n + 1] = 5;
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (v[i][j] != 0) continue;
				for (int dir = 0; dir < 4; dir++) {
					simulate(i, j, dir);
				}
			}
		}

		cout << "#" << tc << " " << ans << "\n";
	}

	return 0;
}