#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

#define ll long long

// 크루스칼
struct Edge {
	int from, to;
	ll cost;
};

int parent[1001];
int x[1001], y[1001];

ll Find(int x) {
	if (parent[x] == x) return x;

	return parent[x] = Find(parent[x]);
}

void Union(int a, int b) {
	a = Find(a);
	b = Find(b);

	if (a == b) return;

	parent[b] = a;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		int n;
		cin >> n;

		for (int i = 1; i <= n; i++) cin >> x[i];
		for (int i = 1; i <= n; i++) cin >> y[i];

		double E;
		cin >> E;

		vector<Edge> edges;

		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				ll dx = x[i] - x[j];
				ll dy = y[i] - y[j];

				ll cost = (dx * dx + dy * dy);

				edges.push_back({ i, j, cost });
			}
		}

		sort(edges.begin(), edges.end(), [&](Edge a, Edge b) {
			return a.cost < b.cost;
			});

		for (int i = 1; i <= n; i++) parent[i] = i;

		int cnt = 0;
		ll ans = 0;

		for (Edge e : edges) {
			if (Find(e.from) != Find(e.to)) {
				Union(e.from, e.to);

				ans += e.cost;
				cnt++;

				if (cnt == n - 1) break;
			}
		}

		cout << "#" << tc << " " << llround(ans * E) << "\n";
	}

}