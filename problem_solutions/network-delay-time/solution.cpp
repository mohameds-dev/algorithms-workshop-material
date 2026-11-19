#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
    int to;
    int weight;

    // Custom comparator for min-heap: smaller weight/distance pops first
    bool operator<(const Edge& other) const {
        return weight > other.weight;
    }
};

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        int num_nodes = n;
        int source = k;

        vector<vector<Edge>> adj(num_nodes + 1);
        for (const auto& edge : times) {
            int src = edge[0];
            int dst = edge[1];
            int travel_time = edge[2];
            adj[src].push_back({dst, travel_time});
        }

        const int INF = 1e9;
        vector<int> dist(num_nodes + 1, INF);
        priority_queue<Edge> pq;

        dist[source] = 0;
        pq.push({source, 0});

        while (!pq.empty()) {
            auto [node, curr_dist] = pq.top();
            pq.pop();

            if (curr_dist > dist[node]) {
                continue;
            }

            for (const auto& edge : adj[node]) {
                if (dist[node] + edge.weight < dist[edge.to]) {
                    dist[edge.to] = dist[node] + edge.weight;
                    pq.push({edge.to, dist[edge.to]});
                }
            }
        }

        int max_time = 0;
        for (int node = 1; node <= num_nodes; ++node) {
            if (dist[node] == INF) {
                return -1;
            }
            max_time = max(max_time, dist[node]);
        }

        return max_time;
    }
};

void test_solution() {
    Solution sol;
    // Test case 1: Standard reachable network
    vector<vector<int>> times1 = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    assert(sol.networkDelayTime(times1, 4, 2) == 2);

    // Test case 2: Single directed edge with unreachable destination
    vector<vector<int>> times2 = {{1, 2, 1}};
    assert(sol.networkDelayTime(times2, 2, 2) == -1);

    // Test case 3: Single directed edge reachable
    assert(sol.networkDelayTime(times2, 2, 1) == 1);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
