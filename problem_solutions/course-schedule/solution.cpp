#include <bits/stdc++.h>

using namespace std;

const int NODES = 1e5 + 5;
const int EDGES = 2e5 + 5;

int in_degree[NODES] = {};
vector<int> adj_list[NODES];

int main() {
    int n, m;
    cin >> n >> m;

    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        adj_list[a].push_back(b);
        in_degree[b] += 1;
    }

    vector<int> top_sorted;

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        top_sorted.push_back(current);

        for (int child : adj_list[current]) {
            in_degree[child]--;

            if (in_degree[child] == 0) {
                q.push(child);
            }
        }
    }

    if ((int)top_sorted.size() < n) {
        cout << "IMPOSSIBLE";
    } else {
        for (int node : top_sorted) {
            cout << node << " ";
        }
    }
    cout << endl;

    return 0;
}
