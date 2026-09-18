#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int V, E;
vector<int> adj[1001];
int inDegree[1001];

vector<int> topologySort() {
	vector<int> res;
	queue<int> q;

	for (int i = 1; i <= V; i++) {
		if (inDegree[i] == 0) q.push(i);
	}

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		res.push_back(cur);

		for (int next : adj[cur]) {
			inDegree[next]--;

			if (inDegree[next] == 0) q.push(next);
		}
	}

	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int t;
	// cin >> t;

	for (int tc = 1; tc <= 10; tc++) {
		cin >> V >> E;
		for (int i = 1; i <= V; i++) {
			adj[i].clear();
			inDegree[i] = 0;
		}

		for (int i = 0; i < E; i++) {
			int from, to;
			cin >> from >> to;

			adj[from].push_back(to);
			inDegree[to]++;
		}

		vector<int> res = topologySort();

		cout << "#" << tc << " ";
		for (int i : res) cout << i << " ";
		cout << "\n";
	}

	return 0;
}