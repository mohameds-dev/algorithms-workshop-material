#include <bits/stdc++.h>
#include <cassert>

using namespace std;

long long minRepairCost(int n, vector<tuple<int, int, int>> edges) {
    vector<int> parent(n + 1);
    iota(parent.begin(), parent.end(), 0);
    vector<int> rank(n + 1, 0);

    auto find_root = [&](auto& self, int i) -> int {
        if (parent[i] == i) return i;
        return parent[i] = self(self, parent[i]);
    };

    auto union_sets = [&](int u, int v) -> bool {
        int root_u = find_root(find_root, u);
        int root_v = find_root(find_root, v);

        if (root_u == root_v) return false;

        if (rank[root_u] < rank[root_v]) swap(root_u, root_v);
        parent[root_v] = root_u;
        if (rank[root_u] == rank[root_v]) rank[root_u]++;
        return true;
    };

    // Sort edges by cost (tuple: u, v, cost)
    sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {
        return get<2>(a) < get<2>(b);
    });

    long long total_cost = 0;
    int edges_added = 0;

    for (const auto& [u, v, cost] : edges) {
        if (union_sets(u, v)) {
            total_cost += cost;
            edges_added++;
            if (edges_added == n - 1) break;
        }
    }

    return (edges_added == n - 1) ? total_cost : -1;
}

void test_solution() {
    vector<tuple<int, int, int>> edges = {
        {1, 2, 3}, {2, 3, 5}, {2, 4, 2}, {3, 4, 8}, {5, 1, 7}, {5, 4, 4}
    };
    assert(minRepairCost(5, edges) == 14);
    assert(minRepairCost(3, {{1, 2, 10}}) == -1);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    /*
    int n, m;
    if (cin >> n >> m) {
        vector<tuple<int, int, int>> edges(m);
        for (int i = 0; i < m; ++i) {
            int u, v, cost;
            cin >> u >> v >> cost;
            edges[i] = {u, v, cost};
        }
        long long ans = minRepairCost(n, edges);
        if (ans == -1) cout << "IMPOSSIBLE\n";
        else cout << ans << "\n";
    }
    */
    return 0;
}
