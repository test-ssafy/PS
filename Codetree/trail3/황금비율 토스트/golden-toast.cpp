#include <iostream>
#include <list>
using namespace std;

int main() {
    int n,m;
    cin >> n >> m;

    list<char> l;

    list<char>::iterator it;
    it = l.begin();

    while (n--) {
        char c;
        cin >> c;
        l.push_back(c);
    }

    while(m--) {
        char cmd;
        cin >> cmd;

        if (cmd == 'L') {
            if (it == l.begin()) continue;
            it--;
        }
        else if (cmd == 'R') {
            if (it == l.end()) continue;
            it++;
        }
        else if (cmd == 'D') {
            if (it == l.end()) continue;
            it = l.erase(it);
        }
        else if (cmd == 'P') {
            char c;
            cin >> c;
            l.insert(it, c);
        }
    }

    for (auto i : l) cout << i;

    return 0;
}