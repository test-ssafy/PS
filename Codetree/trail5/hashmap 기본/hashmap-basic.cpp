#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    unordered_map<int, int> m;

    int t;
    cin >> t;
    while(t--) {
        string cmd;
        int k, v;
        cin >> cmd >> k;
        if (cmd == "add") {
            cin >> v;
            m[k] = v;
        }
        else if (cmd == "find") {
            if (m.find(k) != m.end()) cout << m[k] << "\n";
            else cout << "None" << "\n";
        }
        else if (cmd == "remove") {
            m.erase(k);
        }
    }

    return 0;
}