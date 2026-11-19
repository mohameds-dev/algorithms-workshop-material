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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int num_cities, num_flights;
    if (!(cin >> num_cities >> num_flights)) {
        return 0;
    }

    vector<vector<Edge>> adj(num_cities + 1);
    for (int i = 0; i < num_flights; ++i) {
        int src, dst;
        long long cost;
        cin >> src >> dst >> cost;
        adj[src].push_back({dst, cost});
    }

    vector<long long> dist(num_cities + 1, INF);
    priority_queue<Edge> pq;

    dist[1] = 0;
    pq.push({1, 0});

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

    for (int city = 1; city <= num_cities; ++city) {
        cout << dist[city] << (city == num_cities ? "" : " ");
    }
    cout << "\n";

    return 0;
}
