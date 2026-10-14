#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> v;

bool isAns() {
    if (v.empty()) return true;

    int cnt = 1;
    if (cnt >= m) return false;

    for (int i = 1; i < v.size(); i++) {
        if (v[i] == v[i - 1]) cnt++;
        else cnt = 1;

        if (cnt >= m) return false;
    }

    return true;
}

int main() {
    cin >> n >> m;

    v.assign(n, 0);
    for (int i = 0; i < n; i++) cin >> v[i];

    while (!isAns()) {
        vector<int> tmp;

        int left = 0;

        while (left < v.size()) {
            int right = left + 1;

            while (right < v.size() && v[right] == v[left]) right++;

            int cnt = right - left;

            if (cnt < m) {
                for (int i = left; i < right; i++) tmp.push_back(v[i]);
            }

            left = right;
        }

        v = tmp;
    }

    cout << v.size() << "\n";
    for (int x : v) cout << x << "\n";

    return 0;
}