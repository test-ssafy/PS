#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

struct Node {
	int r, c, k, dir;
};

int sum[100][100];
int maxK[100][100];
int maxDir[100][100];

int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		int N, M, K;
		cin >> N >> M >> K;

		vector<Node> nodes;

		for (int i = 0; i < K; i++) {
			int r, c, k, dir;
			cin >> r >> c >> k >> dir;

			nodes.push_back({ r, c, k, dir - 1 });
		}

		while (M--) {
			vector<Node> nextNodes;

			memset(sum, 0, sizeof(sum));
			memset(maxK, 0, sizeof(maxK));

			for (Node cur : nodes) {

				cur.r += dr[cur.dir];
				cur.c += dc[cur.dir];

				if (cur.r == 0 || cur.r == N - 1 || cur.c == 0 || cur.c == N - 1) {
					cur.k /= 2;
					cur.dir ^= 1;
				}

				if (cur.k == 0) continue;

				sum[cur.r][cur.c] += cur.k;

				if (cur.k > maxK[cur.r][cur.c]) {
					maxK[cur.r][cur.c] = cur.k;
					maxDir[cur.r][cur.c] = cur.dir;
				}
			}

			for (int r = 0; r < N; r++) {
				for (int c = 0; c < N; c++) {
					if (sum[r][c] == 0) continue;

					nextNodes.push_back({ r,c,sum[r][c],maxDir[r][c] });
				}
			}

			nodes = nextNodes;
		}

		int ans = 0;

		for (Node node : nodes) ans += node.k;

		cout << "#" << tc << " " << ans << '\n';
	}

	return 0;
}