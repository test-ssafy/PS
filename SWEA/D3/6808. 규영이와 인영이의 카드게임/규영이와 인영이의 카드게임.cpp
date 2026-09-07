#include <iostream>
using namespace std;

int gyu[9];
int iny[9];

int memo[1 << 9][172];
int visited[1 << 9][172];

int fact[10];

int dfs(int bits, int depth, int gyuScore, int inyScore, int tc) {

	if (visited[bits][gyuScore] == tc) return memo[bits][gyuScore];

	if (gyuScore > 85) {
		visited[bits][gyuScore] = tc;
		memo[bits][gyuScore] = fact[9 - depth];

		return memo[bits][gyuScore];
	}

	if (inyScore > 85) {
		visited[bits][gyuScore] = tc;
		memo[bits][gyuScore] = 0;

		return 0;
	}

	if (depth == 9) {
		visited[bits][gyuScore] = tc;

		if (gyuScore > inyScore) memo[bits][gyuScore] = 1;
		else memo[bits][gyuScore] = 0;

		return memo[bits][gyuScore];
	}

	int result = 0;

	for (int i = 0; i < 9; i++) {

		if (bits & (1 << i)) continue;

		int nextBits = bits | (1 << i);
		int score = gyu[depth] + iny[i];

		if (iny[i] < gyu[depth]) result += dfs(nextBits, depth + 1, gyuScore + score, inyScore, tc);
		else result += dfs(nextBits, depth + 1, gyuScore, inyScore + score, tc);
	}

	visited[bits][gyuScore] = tc;
	memo[bits][gyuScore] = result;

	return result;
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(0);

	fact[0] = 1;

	for (int i = 1; i <= 9; i++) fact[i] = fact[i - 1] * i;

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {

		bool used[19] = { false };

		for (int i = 0; i < 9; i++) {
			cin >> gyu[i];
			used[gyu[i]] = true;
		}

		int idx = 0;

		for (int i = 1; i <= 18; i++) {
			if (!used[i]) iny[idx++] = i;
		}

		int win = dfs(0, 0, 0, 0, tc);
		int lose = fact[9] - win;

		cout << "#" << tc << " " << win << " " << lose << '\n';
	}

	return 0;
}