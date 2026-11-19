#include <bits/stdc++.h>
#include <cassert>

using namespace std;

int findTreeDiameter(int n, const vector<pair<int, int>>& edges) {
    if (n <= 1) return 0;

    vector<vector<int>> adj_list(n + 1);
    for (const auto& [a, b] : edges) {
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    int farthest_node = 0;
    int max_distance = 0;
    vector<bool> visited(n + 1, false);

    auto dfs = [&](auto& self, int node, int distance) -> void {
        visited[node] = true;
        if (distance > max_distance) {
            max_distance = distance;
            farthest_node = node;
        }

        for (int child : adj_list[node]) {
            if (!visited[child]) {
                self(self, child, distance + 1);
            }
        }
    };

    dfs(dfs, 1, 0);

    visited.assign(n + 1, false);
    max_distance = 0;
    dfs(dfs, farthest_node, 0);

    return max_distance;
}

void test_solution() {
    assert(findTreeDiameter(5, {{1, 2}, {1, 3}, {3, 4}, {3, 5}}) == 3);
    assert(findTreeDiameter(1, {}) == 0);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    /*
    int n;
    if (cin >> n) {
        vector<pair<int, int>> edges(n - 1);
        for (int i = 0; i < n - 1; ++i) cin >> edges[i].first >> edges[i].second;
        cout << findTreeDiameter(n, edges) << "\n";
    }
    */
    return 0;
}
