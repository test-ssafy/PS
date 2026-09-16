#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cstring>
using namespace std;

int n, sr, sc, er, ec;
bool isAns = false;
int v[100][100]{ 0 };
bool visited[100][100]{ false };
int dr[4]{ -1,1,0,0 };
int dc[4]{ 0,0,-1,1 };

int bfs() {
	queue<pair<int, int>> q;
	q.push({ sr,sc });
	visited[sr][sc] = true;

	while (!q.empty()) {
		int curR = q.front().first;
		int curC = q.front().second;
		q.pop();

		if (curR == er && curC == ec) return 1;

		for (int i = 0; i < 4; i++) {
			int nr = curR + dr[i];
			int nc = curC + dc[i];

			if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;

			if (v[nr][nc] != 1 && !visited[nr][nc]) {
				visited[nr][nc] = true;
				q.push({ nr,nc });
			}
		}
	}

	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int t;
	// cin >> t;

	for (int tc = 1; tc <= 10; tc++) {
		isAns = false;
		memset(visited, false, sizeof(visited));
		
		cin >> n;
		n = 100;
		for (int i = 0; i < n; i++) {
			string str;
			cin >> str;
			for (int j = 0; j < str.length(); j++) {
				v[i][j] = str[j] - '0';
				if (v[i][j] == 2) sr = i, sc = j;
				else if (v[i][j] == 3) er = i, ec = j;
			}
		}

		cout << '#' << tc << ' ' << bfs() << '\n';
	}

	return 0;
}