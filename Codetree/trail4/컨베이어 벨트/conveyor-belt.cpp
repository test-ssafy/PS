#include <iostream>
using namespace std;

int main() {
    int n, t;
    cin >> n >> t;

    int v[500];
    int size = n*2;
    for (int i=0; i<size; i++) cin >> v[i];

    while(t--) {
        int tmp = v[size-1];
        for (int i=size-1; i>0; i--) v[i] = v[i-1];
        v[0] = tmp;
    }

    for (int i=0; i<n; i++) cout << v[i] << " ";
    cout << "\n";
    for (int i=n; i<size; i++) cout << v[i] << " ";

    return 0;
}