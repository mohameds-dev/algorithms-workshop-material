#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

struct Edge {
    int u, v;
    long long cost;
};

const int NODES = 1e5 + 5;

int parent_node[NODES];
int rank_node[NODES];

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

    if (rank_node[root_u] < rank_node[root_v]) {
        swap(root_u, root_v);
    }
    parent_node[root_v] = root_u;
    if (rank_node[root_u] == rank_node[root_v]) {
        rank_node[root_u]++;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) {
        return 0;
    }

    for (int i = 1; i <= n; ++i) {
        parent_node[i] = i;
        rank_node[i] = 0;
    }

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].cost;
    }

    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.cost < b.cost;
    });

    long long total_cost = 0;
    int edges_added = 0;

    for (const auto& edge : edges) {
        if (union_sets(edge.u, edge.v)) {
            total_cost += edge.cost;
            edges_added++;
            if (edges_added == n - 1) {
                break;
            }
        }
    }

    if (edges_added == n - 1) {
        cout << total_cost << "\n";
    } else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}
