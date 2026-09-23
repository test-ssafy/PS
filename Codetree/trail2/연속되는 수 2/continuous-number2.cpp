#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int v[1000]{0};
    for (int i=0; i<n; i++) cin >> v[i];

    int ans = 1, cnt = 1;

    for (int i=1; i<n; i++) {
        if (v[i] == v[i-1]) cnt++;
        else {
            ans = max(ans, cnt);
            cnt = 1;
        }
    }

    ans = max(ans, cnt);

    cout << ans;

    return 0;
}