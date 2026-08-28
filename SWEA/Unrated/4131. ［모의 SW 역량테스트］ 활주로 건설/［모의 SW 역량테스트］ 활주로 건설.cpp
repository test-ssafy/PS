#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int n, x;
int v[20][20]{ 0 };

int check(int r, int c, int dr, int dc) {
	int height = v[r][c];
	int len = 1;

	for (int i = 1; i < n; i++) {
		int nr = r + dr * i;
		int nc = c + dc * i;

		int curH = v[nr][nc];

		if (abs(height - curH) > 1) return 0;

		if (height == curH) len++;
		else if (height < curH) {
			if (len < x) return 0;

			height = curH;
			len = 1;
		}
		else {
			if (i + x > n) return 0;

			// 현재 칸부터 X칸이 모두 낮은 높이인지
			for (int j = 0; j < x; j++) {
				int rr = r + (i + j) * dr;
				int cc = c + (i + j) * dc;

				if (v[rr][cc] != curH) return 0;
			}

			height = curH;
			// 경사로에 사용한 칸은 건너뜀
			len = 0;
			i += x - 1;
		}
	}

	return 1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n >> x;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) cin >> v[i][j];
		}

		int ans = 0;

		for (int r = 0; r < n; r++) ans += check(r, 0, 0, 1);
		for (int c = 0; c < n; c++) ans += check(0, c, 1, 0);

		cout << "#" << tc << " " << ans << '\n';
	}

	return 0;
}