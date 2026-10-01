#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> v(n,0);
    for (int i=0; i<n; i++) cin >> v[i];
    vector<int> tmp;
    vector<int> ans;

    int s1, e1, s2, e2;
    cin >> s1 >> e1;

    for (int i=s1-1; i<e1; i++) v[i] = 0;
    for (int i=0; i<n; i++) {
        if (v[i] == 0) continue;
        tmp.push_back(v[i]);
    }

    cin >> s2 >> e2;

    for (int i=s2-1; i<e2; i++) tmp[i] = 0;

    for (int i=0; i<tmp.size(); i++) {
        if (tmp[i] == 0) continue;
        ans.push_back(tmp[i]);
    }

    cout << ans.size() << "\n";
    for (int i : ans) cout << i << "\n";

    return 0;
}