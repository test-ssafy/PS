#include <iostream>
#include <deque>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	//cin >> t;

	for (int tc = 1; tc <= 10; tc++) {
		cin >> t;
		deque<int> deq;

		for (int i = 0; i < 8; i++) {
			int a;
			cin >> a;
			deq.push_back(a);
		}

		int idx = 1;
		while (deq.front() > 0) {
			if (idx > 5) idx = 1;

			int cur = deq.front();
			cur -= idx;

			if (cur <= 0) cur = 0;
			deq.pop_front();
			deq.push_back(cur);

			if (cur == 0) break;
			idx++;
		}
	
		cout << "#" << tc << " ";
		while (!deq.empty()) {
			cout << deq.front() << " ";
			deq.pop_front();
		}
		cout << "\n";
	}
	
	return 0;
}