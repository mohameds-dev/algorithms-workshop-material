#include <bits/stdc++.h>

using namespace std;

const int NODES = 2e5 + 5;

vector<int> adj_list[NODES];

int farthest_node = 0, max_distance = 0;

bool visited[NODES];

void dfs(int node, int distance) {
    visited[node] = true;

    if (distance > max_distance) {
        max_distance = distance;
        farthest_node = node;
    }

    for (int child : adj_list[node]) {
        if (!visited[child]) {
            dfs(child, distance + 1);
        }
    }
}

int main() {
    int n;
    cin >> n;

    int a, b;
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    dfs(1, 0);
    int first_farthest = farthest_node;
    memset(visited, 0, sizeof visited);

    dfs(first_farthest, 0);
    int diameter = max_distance;

    cout << diameter << endl;

    return 0;
}
