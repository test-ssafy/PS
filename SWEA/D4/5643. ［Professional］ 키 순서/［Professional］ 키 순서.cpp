#include <iostream>
#include <vector>
using namespace std;

int t, n, m;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> t;

    for (int tc = 1; tc <= t; tc++) {
        cin >> n >> m;

        vector<vector<int>> graph(n + 1);
        vector<vector<int>> reverseGraph(n + 1);

        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;

            graph[a].push_back(b);
            reverseGraph[b].push_back(a);
        }

        int ans = 0;

        for (int i = 1; i <= n; i++) {
            vector<bool> visited(n + 1, false);
            vector<int> st;
            int cnt = 0;

            st.push_back(i);
            visited[i] = true;

            while (!st.empty()) {
                int cur = st.back();
                st.pop_back();

                for (int next : graph[cur]) {
                    if (!visited[next]) {
                        visited[next] = true;
                        st.push_back(next);
                        cnt++;
                    }
                }
            }

            fill(visited.begin(), visited.end(), false);
            st.clear();

            st.push_back(i);
            visited[i] = true;

            while (!st.empty()) {
                int cur = st.back();
                st.pop_back();

                for (int next : reverseGraph[cur]) {
                    if (!visited[next]) {
                        visited[next] = true;
                        st.push_back(next);
                        cnt++;
                    }
                }
            }

            if (cnt == n - 1) ans++;
        }

        cout << "#" << tc << " " << ans << '\n';
    }

    return 0;
}