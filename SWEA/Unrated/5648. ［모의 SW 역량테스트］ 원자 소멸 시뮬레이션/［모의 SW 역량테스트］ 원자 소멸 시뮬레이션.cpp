#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define SIZE 4001
#define OUT -2

struct Node {
	int r, c;
	int dir, k;
	bool alive;
};

int n, ans;
// 0.5 초에 만날 수 있으니 2배로 설정
int v[SIZE][SIZE]{ 0 };
// 좌표계와 배열의 방향은 다름 -> 상:r++, 하:r--
//int dr[4]{ -1,1,0,0 };
//int dc[4]{ 0,0,-1,1 };
int dr[4]{ 1,-1,0,0 };
int dc[4]{ 0,0,-1,1 };

void simulate(vector<Node>& nodes) {

	int aliveCnt = n;

	for (int t = 0; t < 4000 && aliveCnt > 1; t++) {

		vector<pair<int, int>> touched;
		touched.reserve(aliveCnt);

		for (int i = 0; i < n; i++) {
			if (!nodes[i].alive) continue;

			int nr = nodes[i].r + dr[nodes[i].dir];
			int nc = nodes[i].c + dc[nodes[i].dir];

			if (nr < 0 || nc < 0 || nr >= SIZE || nc >= SIZE) {
				nodes[i].alive = false;
				aliveCnt--;
				continue;
			}

			nodes[i].r = nr;
			nodes[i].c = nc;

			int cell = v[nr][nc];
			// 혼자일때
			if (cell == -1) {
				v[nr][nc] = i;
				touched.push_back({ nr, nc });
			}
			// 3개 이상이 부딪히는 경우
			else if (cell == OUT) {
				ans += nodes[i].k;
				nodes[i].alive = false;
				aliveCnt--;
			}
			// 2개가 충돌하는 경우
			else {
				int other = v[nr][nc];
				ans += nodes[i].k;
				ans += nodes[other].k;
				nodes[i].alive = false;
				nodes[other].alive = false;
				aliveCnt -= 2;

				v[nr][nc] = OUT;
			}
		}

		// 현재 부딪힌 애들 초기화
		for (auto p : touched) v[p.first][p.second] = -1;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	memset(v, -1, sizeof(v));

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n;
		vector<Node> nodes(n);
		for (int i = 0; i < n; i++) {
			int x, y, dir, k;
			cin >> x >> y >> dir >> k;
			nodes[i] = { (y + 1000) * 2,(x + 1000) * 2,dir,k,true };
		}
		
		ans = 0;

		simulate(nodes);

		cout << "#" << tc << " " << ans << "\n";
	}

	return 0;
}