#include <bits/stdc++.h>

using namespace std;

const int NODES = 1e5 + 5;

int parent_node[NODES];
int component_size[NODES];
int total_components;
int max_component_size = 1;

int find_root(int node) {
    if (parent_node[node] == node) {
        return node;
    }
    return parent_node[node] = find_root(parent_node[node]);
}

bool union_sets(int u, int v) {
    int root_u = find_root(u);
    int root_v = find_root(v);

    if (root_u == root_v) {
        return false;
    }

    if (component_size[root_u] < component_size[root_v]) {
        swap(root_u, root_v);
    }

    parent_node[root_v] = root_u;
    component_size[root_u] += component_size[root_v];
    max_component_size = max(max_component_size, component_size[root_u]);
    total_components--;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) {
        return 0;
    }

    total_components = n;
    for (int i = 1; i <= n; ++i) {
        parent_node[i] = i;
        component_size[i] = 1;
    }

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        union_sets(a, b);
        cout << total_components << " " << max_component_size << "\n";
    }

    return 0;
}
