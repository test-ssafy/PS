#include <iostream>
using namespace std;

int main() {
    int a,b,c,d;
    cin >> a >> b >> c >> d;

    int ans = (c*60 + d) - (a*60 + b);
    cout << ans;

    return 0;
}