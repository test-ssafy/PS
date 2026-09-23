#include <iostream>
using namespace std;

int month[13]{0,31,28,31,30,31,30,31,31,30,31,30,31};
string ans[7]{"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

int main() {
    int m1,d1,m2,d2;
    cin >> m1 >> d1 >> m2 >> d2;

    int day1 = 0, day2 = 0;
    for (int i=1; i<m1; i++) day1 += month[i];
    day1 += d1;
    for (int i=1; i<m2; i++) day2 += month[i];
    day2 += d2;

    int days = (day2 - day1) % 7;
    if (days < 0) days += 7;
    cout << ans[days];

    return 0;
}