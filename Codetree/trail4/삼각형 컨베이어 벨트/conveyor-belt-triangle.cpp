#include <iostream>
#include <vector>
using namespace std;

int main() {

    int n, t;
    cin >> n >> t;

    int size = 3*n;
    vector<int> v(size, 0);

    for (int i=0; i<size; i++) cin >> v[i];
    while(t--) {
        int tmp = v[size-1];
        for (int i=size-1; i>0; i--) v[i] = v[i-1];
        v[0] = tmp;
    }

    for (int i=0; i<n; i++) cout << v[i] << " ";
    cout << "\n";
    for (int i=n; i<2*n; i++) cout << v[i] << " ";
    cout << "\n";
    for (int i=2*n; i<size; i++) cout << v[i] << " ";

    return 0;
}