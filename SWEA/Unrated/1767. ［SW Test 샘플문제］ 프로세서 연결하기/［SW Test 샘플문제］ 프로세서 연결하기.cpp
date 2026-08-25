#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int n, maxCnt, minLen;
int dr[4]{ -1,1,0,0 };
int dc[4]{ 0,0,-1,1 };
int graph[13][13]{ 0 };
bool used[13][13]{ false };
vector<pair<int, int>> core;

int connect(int r, int c, int dir) {
	int nr = r;
	int nc = c;
	int length = 0;
	
	while (true) {
		nr += dr[dir];
		nc += dc[dir];

		// 다른 Core 혹은 설치된 전선
		if (graph[nr][nc] == 1 || used[nr][nc]) return -1;

		length++;

		// 가장자리 도착
		if (nr == 0 || nc == 0 || nr == n - 1 || nc == n - 1) return length;
	}
}

void dfs(int idx, int cnt, int len) {
	if (idx == core.size()) {
		if (cnt > maxCnt) {
			maxCnt = cnt;
			minLen = len;
		}
		else if (cnt == maxCnt) minLen = min(minLen, len);

		return;
	}

	int cr = core[idx].first;
	int cc = core[idx].second;

	for (int dir = 0; dir < 4; dir++) {
		// 연결 시도
		int length = connect(cr, cc, dir);

		if (length == -1) continue;

		// 가능하면 전선설치
		int nr = cr;
		int nc = cc;
		for (int i = 0; i < length; i++) {
			nr += dr[dir];
			nc += dc[dir];
			used[nr][nc] = true;
		}

		dfs(idx + 1, cnt + 1, len + length);

		// 전선 제거
		nr = cr;
		nc = cc;
		for (int i = 0; i < length; i++) {
			nr += dr[dir];
			nc += dc[dir];
			used[nr][nc] = false;
		}
	}

	// core 연결 안하는 경우
	dfs(idx + 1, cnt, len);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		maxCnt = 0;
		minLen = 1e9;
		memset(used, false, sizeof(used));
		core.clear();

		cin >> n;
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> graph[i][j];
				if (graph[i][j] == 1) {
					if (i != 0 && j != 0 &&  i != n - 1 && j != n - 1) core.push_back({ i,j });
				}
			}
		}

		dfs(0, 0, 0);

		cout << '#' << tc << ' ' << minLen << '\n';
	}

	return 0;
}