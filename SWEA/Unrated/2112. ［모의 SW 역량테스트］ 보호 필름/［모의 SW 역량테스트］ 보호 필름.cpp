#include <iostream>
using namespace std;

int d, w, k, ans;
int v[13][20];

bool check() {
	for (int c = 0; c < w; c++) {
		int cnt = 1;
		bool pass = false;

		for (int r = 1; r < d; r++) {
			if (v[r][c] == v[r - 1][c]) cnt++;
			else cnt = 1;

			if (cnt >= k) {
				pass = true;
				break;
			}
		}

		if (!pass) return false;
	}

	return true;
}

void dfs(int row, int cnt) {

	if (ans <= cnt) return;

	if (row == d) {
		if (check()) ans = cnt;
		return;
	}

	// 선택 X
	dfs(row + 1, cnt);

	int tmp[20];
	for (int i = 0; i < w; i++) tmp[i] = v[row][i];

	// 0 선택
	for (int i = 0; i < w; i++) v[row][i] = 0;
	dfs(row + 1, cnt + 1);

	// 1 선택
	for (int i = 0; i < w; i++) v[row][i] = 1;
	dfs(row + 1, cnt + 1);

	// 복구
	for (int i = 0; i < w; i++) v[row][i] = tmp[i];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;


	for (int tc = 1; tc <= t; tc++) {
		cin >> d >> w >> k;
		ans = d;

		for (int i = 0; i < d; i++) {
			for (int j = 0; j < w; j++) cin >> v[i][j];
		}

		dfs(0, 0);
 
		cout << "#" << tc << " " << ans << "\n";
	}

	return 0;
}