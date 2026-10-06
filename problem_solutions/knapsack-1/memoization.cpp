#include <vector>
#include <algorithm>

using namespace std;

long long solve_knapsack(const vector<int>& weights, const vector<int>& values, int capacity) {
    int n = weights.size();
    vector<vector<long long>> memo(n, vector<long long>(capacity + 1, -1));

    auto solve = [&](auto& self, int i, int remaining) -> long long {
        if (i == n) {
            return 0;
        }
        if (memo[i][remaining] != -1) {
            return memo[i][remaining];
        }

        long long ans = self(self, i + 1, remaining);
        if (weights[i] <= remaining) {
            ans = max(ans, (long long)values[i] + self(self, i + 1, remaining - weights[i]));
        }

        return memo[i][remaining] = ans;
    };

    return solve(solve, 0, capacity);
}
