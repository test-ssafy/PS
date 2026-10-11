#include <iostream>
#include <unordered_map>
using namespace std;

int main() {

    int n;
    cin >> n;
    unordered_map<string, int> m;

    for (int i=0; i<n; i++) {
        string str;
        cin >> str;
        m[str]++;
    }

    int maxCnt = 0;
    string ans = "";
    for (auto [k, v] : m) {
        if (maxCnt < v) {
            maxCnt = v;
            ans = k;
        }
    }

    cout << maxCnt;
    
    return 0;
}