#include <bits/stdc++.h>
#include <cassert>

using namespace std;

vector<int> findOrder(int n, const vector<pair<int, int>>& prerequisites) {
    vector<int> in_degree(n + 1, 0);
    vector<vector<int>> adj_list(n + 1);

    for (const auto& [a, b] : prerequisites) {
        adj_list[a].push_back(b);
        in_degree[b]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> top_sorted;
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
        return {};
    }
    return top_sorted;
}

void test_solution() {
    vector<int> expected1 = {1, 2, 3, 4};
    assert(findOrder(4, {{1, 2}, {2, 3}, {3, 4}}) == expected1);
    assert(findOrder(2, {{1, 2}, {2, 1}}).empty());
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    /*
    int n, m;
    if (cin >> n >> m) {
        vector<pair<int, int>> prerequisites(m);
        for (int i = 0; i < m; i++) {
            cin >> prerequisites[i].first >> prerequisites[i].second;
        }
        vector<int> order = findOrder(n, prerequisites);
        if (order.empty()) {
            cout << "IMPOSSIBLE\n";
        } else {
            for (int node : order) cout << node << " ";
            cout << "\n";
        }
    }
    */
    return 0;
}
