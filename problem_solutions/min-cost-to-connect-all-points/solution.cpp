#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<int> min_dist(n, 1e9);
        vector<bool> in_mst(n, false);

        min_dist[0] = 0;
        int total_cost = 0;

        for (int step = 0; step < n; ++step) {
            int u = -1;
            for (int i = 0; i < n; ++i) {
                if (!in_mst[i] && (u == -1 || min_dist[i] < min_dist[u])) {
                    u = i;
                }
            }

            in_mst[u] = true;
            total_cost += min_dist[u];

            for (int v = 0; v < n; ++v) {
                if (!in_mst[v]) {
                    int dist = abs(points[u][0] - points[v][0]) + abs(points[u][1] - points[v][1]);
                    if (dist < min_dist[v]) {
                        min_dist[v] = dist;
                    }
                }
            }
        }

        return total_cost;
    }
};
