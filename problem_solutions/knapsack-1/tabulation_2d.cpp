#include <vector>
#include <algorithm>

using namespace std;

long long solve_knapsack(const vector<int>& weights, const vector<int>& values, int capacity) {
    int n = weights.size();
    vector<vector<long long>> dp(n + 1, vector<long long>(capacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            dp[i][w] = dp[i - 1][w];
            if (weights[i - 1] <= w) {
                dp[i][w] = max(dp[i][w], (long long)values[i - 1] + dp[i - 1][w - weights[i - 1]]);
            }
        }
    }

    return dp[n][capacity];
}
