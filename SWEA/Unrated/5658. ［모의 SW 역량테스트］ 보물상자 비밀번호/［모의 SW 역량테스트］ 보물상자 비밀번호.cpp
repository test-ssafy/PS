#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>

using namespace std;

int n, k;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {

		int ans = 0;

		cin >> n >> k;

		string str;
		cin >> str;
		      
		vector<char> c(n * 2);

		for (int i = 0; i < str.length(); i++) {
			c[i] = str[i];
			c[n + i] = str[i];
		}

		set<string, greater<string>> s;
		for (int plus = 0; plus < n / 4; plus++) {
			string tmp = "";
			for (int i = plus; i < n + plus; i++) {
				if ((i - plus) % (n / 4) == 0) {
					s.insert(tmp);
					tmp = "";
				}
				tmp += c[i];
			}
			s.insert(tmp);
		}

		int idx = 1;
		string curStr = "";
		for (auto i : s) {
			if (idx == k) {
				curStr = i;
				break;
			}
			idx++;
		}

		cout << "#" << tc << " " << stoi(curStr, nullptr, 16) << "\n";
	}
}