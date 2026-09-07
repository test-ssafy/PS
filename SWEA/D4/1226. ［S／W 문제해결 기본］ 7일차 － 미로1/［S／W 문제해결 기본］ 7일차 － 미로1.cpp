#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cstring>
using namespace std;

string v[16];
int dr[4]{ -1,1,0,0 };
int dc[4]{ 0,0,-1,1 };
bool visited[16][16]{ false };
int startR, startC, endR, endC, ans;

void bfs() {
	queue<pair<int, int>> q;
	q.push({ startR,startC });

	while (!q.empty()) {
		int r = q.front().first;
		int c = q.front().second;
		q.pop();

		if (visited[r][c]) continue;
		visited[r][c] = true;

		if (r == endR && c == endC) {
			ans = 1;
			return;
		}

		for (int i = 0; i < 4; i++) {
			int nr = r + dr[i];
			int nc = c + dc[i];

			if (nr < 0 || nc < 0 || nr >= 16 || nc >= 16) continue;

			if (!visited[nr][nc] && v[nr][nc] != '1') q.push({ nr,nc });
		}

	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	//cin >> t;

	for (int tc = 1; tc <= 10; tc++) {
		cin >> t;
		memset(visited, false, sizeof(visited));

		for (int i = 0; i < 16; i++) {
			string str;
			cin >> str;
			v[i] = str;
			for (int j = 0; j < str.length(); j++) {
				if (str[j] == '2') {
					startR = i;
					startC = j;
				}
				else if (str[j] == '3') {
					endR = i;
					endC = j;
				}
			}
		}

		ans = 0;
		bfs();

		cout << "#" << t << " " << ans << "\n";
	}

	return 0;
}