#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <string>
using namespace std;

#define INF 1e9

int n;
vector<vector<int>> v;

int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };

int dijkstra() {
	vector<vector<int>> dist(n, vector<int>(n, INF));
	priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

	dist[0][0] = 0;
	pq.push({ 0, 0, 0 });

	while (!pq.empty()) {

		int cost = get<0>(pq.top());
		int r = get<1>(pq.top());
		int c = get<2>(pq.top());
		pq.pop();

		if (cost > dist[r][c]) continue;

		for (int dir = 0; dir < 4; dir++) {

			int nr = r + dr[dir];
			int nc = c + dc[dir];

			if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;

			int newCost = cost + v[nr][nc];

			if (newCost < dist[nr][nc]) {
				dist[nr][nc] = newCost;
				pq.push({ newCost, nr, nc });
			}
		}
	}

	return dist[n - 1][n - 1];
}

int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n;
		v.assign(n, vector<int>(n));

		string str;
		for (int r = 0; r < n; r++) {
			cin >> str;
			for (int c = 0; c < n; c++) v[r][c] = str[c] - '0';
		}

		cout << "#" << tc << " " << dijkstra() << "\n";
	}

	return 0;
}