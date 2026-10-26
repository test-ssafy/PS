#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    int n;
    cin >> n;

    unordered_set<int> us;

    while(n--) {
        string cmd;
        int x;
        cin >> cmd >> x;

        if (cmd == "add") us.insert(x);
        else if (cmd == "remove") us.erase(x);
        else {
            cout << (us.find(x) != us.end() ? "true\n" : "false\n"); 
        }

    }
    return 0;
}