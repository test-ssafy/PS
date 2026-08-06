#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int n;
int dr[8]{ -1,-1,-1,0,0,1,1,1 };
int dc[8]{ -1,0,1,-1,1,-1,0,1 };
bool possible = false;

bool check(const vector<string>& v, int r, int c) {
	
	for (int i = 0; i < 8; i++) {
		int nr = r + dr[i];
		int nc = c + dc[i];

		int cnt = 1;

		while (nr >= 0 && nc >= 0 && nr < n && nc < n) {
			if (v[nr][nc] != 'o') {
				break;
			}

			cnt++;

			if (cnt >= 5) return true;

			nr += dr[i];
			nc += dc[i];
		}
	}

	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		possible = false;

		cin >> n;

		vector<string> v(n, "");
		for (int i = 0; i < n; i++) cin >> v[i];

		vector<pair<int, int>> position;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (v[i][j] == 'o') position.push_back({ i,j });
			}
		}

		for (auto p : position) {
			if (possible) break;
			possible = check(v, p.first, p.second);
		}

		cout << "#" << tc << " " << (possible ? "YES" : "NO") << '\n';
	}

	return 0;
}