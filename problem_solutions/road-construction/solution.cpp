#include <bits/stdc++.h>
#include <cassert>

using namespace std;

vector<pair<int, int>> processRoads(int n, const vector<pair<int, int>>& roads) {
    vector<int> parent_node(n + 1);
    iota(parent_node.begin(), parent_node.end(), 0);
    vector<int> component_size(n + 1, 1);

    int total_components = n;
    int max_component_size = 1;

    auto find_root = [&](auto& self, int node) -> int {
        if (parent_node[node] == node) return node;
        return parent_node[node] = self(self, parent_node[node]);
    };

    auto union_sets = [&](int u, int v) -> bool {
        int root_u = find_root(find_root, u);
        int root_v = find_root(find_root, v);

        if (root_u == root_v) return false;

        if (component_size[root_u] < component_size[root_v]) {
            swap(root_u, root_v);
        }

        parent_node[root_v] = root_u;
        component_size[root_u] += component_size[root_v];
        max_component_size = max(max_component_size, component_size[root_u]);
        total_components--;
        return true;
    };

    vector<pair<int, int>> result;
    for (const auto& [a, b] : roads) {
        union_sets(a, b);
        result.push_back({total_components, max_component_size});
    }

    return result;
}

void test_solution() {
    vector<pair<int, int>> roads = {{1, 2}, {3, 4}, {2, 3}};
    vector<pair<int, int>> expected = {{3, 2}, {2, 2}, {1, 4}};
    assert(processRoads(4, roads) == expected);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    /*
    int n, m;
    if (cin >> n >> m) {
        vector<pair<int, int>> roads(m);
        for (int i = 0; i < m; ++i) cin >> roads[i].first >> roads[i].second;
        for (const auto& [comps, max_sz] : processRoads(n, roads)) {
            cout << comps << " " << max_sz << "\n";
        }
    }
    */
    return 0;
}
