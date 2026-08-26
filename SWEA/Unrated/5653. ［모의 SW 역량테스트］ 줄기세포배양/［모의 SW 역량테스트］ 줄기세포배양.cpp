#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

struct Node {
	int r, c;
};

int n, m, k, ans;
int v[650][650]{ 0 };
int timePass[650][650]{ 0 };
int dr[4]{ -1,1,0,0 };
int dc[4]{ 0,0,-1,1 };
queue<Node> actQ;
queue<Node> inActQ;

void inActive(int size) {
	while (size--) {
		int r = inActQ.front().r;
		int c = inActQ.front().c;
		inActQ.pop();
		timePass[r][c]++;
		
		if (timePass[r][c] == v[r][c]) actQ.push({ r,c });
		else if (timePass[r][c] < v[r][c]) inActQ.push({ r,c });
	}
}

void active(int size) {
	while (size--) {
		int r = actQ.front().r;
		int c = actQ.front().c;
		actQ.pop();
		timePass[r][c]++;

		if (timePass[r][c] < v[r][c] * 2) actQ.push({ r,c });
	
		for (int i = 0; i < 4; i++) {
			int nr = r + dr[i];
			int nc = c + dc[i];

			if (v[nr][nc] == 0) {
				v[nr][nc] = v[r][c];
				inActQ.push({ nr,nc });
			}
			else if (v[nr][nc] > 0 && timePass[nr][nc] == 0) v[nr][nc] = max(v[nr][nc], v[r][c]);
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		memset(v, 0, sizeof(v));
		memset(timePass, 0, sizeof(timePass));
		while (!inActQ.empty()) inActQ.pop();
		while (!actQ.empty()) actQ.pop();

		cin >> n >> m >> k;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cin >> v[i + k][j + k];
				if (v[i + k][j + k] != 0) inActQ.push({ i + k, j + k });
			}
		}

		for (int time = 1; time <= k; time++) {
			int inActSize = inActQ.size();
			int actSize = actQ.size();

			inActive(inActSize);
			active(actSize);
		}

		int ans = 0;

		cout << "#" << tc << " " << inActQ.size() + actQ.size() << "\n";
	}

	return 0;
}