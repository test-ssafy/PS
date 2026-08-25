#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

#define MOD 4

int n, m, ans;
int v[10][10]{ 0 };
int dr[4]{ 0,1,0,-1 };
int dc[4]{ 1,0,-1,0 };

struct Node {
	int r;
	int c;
	int target;
	int dir;
	int cnt;
};

void bfs() {
	deque<Node> q;
	q.push_back({ 0,0,1,0,0 });
	
	int sum = 0;

	while (!q.empty()) {
		Node cur = q.front();
		q.pop_front();

		int r = cur.r;
		int c = cur.c;
		int target = cur.target;
		int dir = cur.dir;
		int cnt = cur.cnt;

		if (v[r][c] == target && target == m) {
			sum += cnt;
			ans = sum;
			return;
		}
		else if (v[r][c] == target) {
			q = deque<Node>();
			sum += cnt;
			q.push_back({ r, c, target + 1, dir, 0 });
			continue;
		}

		// 그냥 앞으로 가기
		int nr = r + dr[dir];
		int nc = c + dc[dir];
		if (nr >= 0 && nc >= 0 && nr < n && nc < n) q.push_front({ nr,nc,target,dir,cnt });

		// 회전하기
		dir = (dir + 1) % MOD;
		nr = r + dr[dir];
		nc = c + dc[dir];
		if (nr >= 0 && nc >= 0 && nr < n && nc < n) q.push_back({ nr,nc,target,dir,cnt + 1 });

	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n;

		m = 0;
		ans = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> v[i][j];
				m = max(m, v[i][j]);
			}
		}

		bfs();
		
		cout << "#" << tc << " " << ans << "\n";
	}

	return 0;
}