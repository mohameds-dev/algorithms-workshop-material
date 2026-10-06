#include <vector>
#include <algorithm>

using namespace std;

long long solve_knapsack(const vector<int>& weights, const vector<int>& values, int capacity) {
    int n = weights.size();
    vector<long long> dp(capacity + 1, 0);

    for (int i = 0; i < n; ++i) {
        for (int w = capacity; w >= weights[i]; --w) {
            dp[w] = max(dp[w], (long long)values[i] + dp[w - weights[i]]);
        }
    }

    return dp[capacity];
}
