#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool rowCheck(vector<string>& v, int r, int start, int len) {
	int left = start;
	int right = start + len - 1;

	while (left < right) {
		if (v[r][left] != v[r][right]) return false;
		left++;
		right--;
	}

	return true;
}

bool colCheck(vector<string>& v, int c, int start, int len) {
	int left = start;
	int right = start + len - 1;

	while (left < right) {
		if (v[left][c] != v[right][c]) return false;
		left++;
		right--;
	}

	return true;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	//int t;
	//cin >> t;

	for (int tc = 1; tc <= 10; tc++) {
		int ans = 0;
		int t;
		cin >> t;

		vector<string> v(100);

		for (int i = 0; i < 100; i++) cin >> v[i];

		bool found = false;
		for (int len = 100; len >= 1 && !found; len--) {
			
			// 가로 판단
			for (int r = 0; r < 100 && !found; r++) {
				for (int start = 0; start < 100 - len + 1; start++) {
					if (rowCheck(v, r, start, len)) {
						found = true;
						ans = len;
						break;
					}
				}
			}
			 
			// 세로 판단
			for (int c = 0; c < 100 & !found; c++) {
				for (int start = 0; start < 100 - len + 1; start++) {
					if (colCheck(v, c, start, len)) {
						found = true;
						ans = len;
						break;
					}
				}
			}
		}

		cout << "#" << t << " " << ans << "\n";
	}
}