
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    unordered_map<string, int> strToNum;
    unordered_map<int, string> numToStr;

    for (int i = 1; i <= n; i++) {
        string str;
        cin >> str;

        strToNum[str] = i;
        numToStr[i] = str;
    }

    for (int i = 0; i < m; i++) {
        string str;
        cin >> str;

        if (isdigit(str[0])) {
            int num = stoi(str);
            cout << numToStr[num] << "\n";
        }
        else {
            cout << strToNum[str] << "\n";
        }
    }

    return 0;
}
