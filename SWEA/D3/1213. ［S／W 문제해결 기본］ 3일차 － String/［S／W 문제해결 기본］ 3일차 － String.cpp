#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t;
	// cin >> t;

	for (int tc = 1; tc <= 10; tc++) {
		cin >> t;
		int ans = 0;

		string found = "";
		string str = "";
		
		cin >> found;
		cin >> str;

		for (int i = 0; i <= str.length() - found.length() + 1; i++) {
			if (str[i] == found[0]) {
				bool check = true;
				for (int j = 1; j < found.length(); j++) {
					if (str[i + j] != found[j]) {
						check = false;
						break;
					}
				}
				if (check) ans++;
			}
		}

		cout << "#" << t << " " << ans << '\n';
	}

	return 0;
}