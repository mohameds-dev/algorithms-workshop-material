#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const long long INF = 1e18;

struct Edge {
    int to;
    long long weight;

    // Custom comparator for min-heap: smaller weight/distance pops first
    bool operator<(const Edge& other) const {
        return weight > other.weight;
    }
};

vector<long long> dijkstra(int num_cities, const vector<vector<Edge>>& adj, int source = 1) {
    vector<long long> dist(num_cities + 1, INF);
    priority_queue<Edge> pq;

    dist[source] = 0;
    pq.push({source, 0});

    while (!pq.empty()) {
        auto [city, curr_dist] = pq.top();
        pq.pop();

        if (curr_dist > dist[city]) {
            continue;
        }

        for (const auto& edge : adj[city]) {
            if (dist[city] + edge.weight < dist[edge.to]) {
                dist[edge.to] = dist[city] + edge.weight;
                pq.push({edge.to, dist[edge.to]});
            }
        }
    }

    return dist;
}

void test_solution() {
    // CSES 1671 sample test case:
    // 3 cities, 3 flights: 1->2 (cost 6), 1->3 (cost 2), 3->2 (cost 1)
    int num_cities = 3;
    vector<vector<Edge>> adj(num_cities + 1);
    adj[1].push_back({2, 6});
    adj[1].push_back({3, 2});
    adj[3].push_back({2, 1});

    auto dist = dijkstra(num_cities, adj, 1);
    assert(dist[1] == 0);
    assert(dist[2] == 3);
    assert(dist[3] == 2);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
