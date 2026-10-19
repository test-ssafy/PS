#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int n, m, cnt;
vector<int> parent[501];
vector<int> child[501];

bool visited[501];

void dfs(int cur, vector<int> graph[]) {
	visited[cur] = true;

	for (int next : graph[cur]) {
		if (!visited[next]) {
			cnt++;
			dfs(next, graph);
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++) {
			parent[i].clear();
			child[i].clear();
		}

		for (int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;

			parent[a].push_back(b);
			child[b].push_back(a);
		}

		int ans = 0;

		for (int i = 1; i <= n; i++) {
			cnt = 0;
			memset(visited, false, sizeof(visited));
			dfs(i, child);
			int smaller = cnt;

			cnt = 0;
			memset(visited, false, sizeof(visited));
			dfs(i, parent);
			int bigger = cnt;

			if (smaller + bigger == n - 1) ans++;
		}

		cout << "#" << tc << " " << ans << '\n';
	}

	return 0;
}