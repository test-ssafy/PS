#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m, ans;
vector<int> adj[101];
int inDegree[101]{ 0 };
bool used[101]{ false };

void bfs(int num) {
	if (used[num]) return;
	
	queue<int> q;
	q.push(num);
	used[num] = true;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (int next : adj[cur]) {
			if (!used[next]) {
				used[next] = true;
				q.push(next);
			}
		}
	}

	ans++;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		ans = 0;
		cin >> n >> m;

		for (int i = 1; i <= n; i++) {
			adj[i].clear();
			inDegree[i] = 0;
			used[i] = false;
		}

		for (int i = 0; i < m; i++) {
			int u, v;
			cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
			inDegree[u]++;
			inDegree[v]++;
		}

		for (int i = 1; i <= n; i++) {
			if (inDegree[i] == 0) {
				ans++;
				used[i] = true;
			}
		}

		for (int i = 1; i <= n; i++) bfs(i);

		cout << "#" << tc << " " << ans << "\n";
	}

	return 0;
}