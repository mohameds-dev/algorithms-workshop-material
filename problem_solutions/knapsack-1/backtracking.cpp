#include <vector>
#include <algorithm>

using namespace std;

long long solve_knapsack(const vector<int>& weights, const vector<int>& values, int capacity) {
    int n = weights.size();

    auto solve = [&](auto& self, int i, int remaining) -> long long {
        if (i == n) {
            return 0;
        }

        long long ans = self(self, i + 1, remaining);
        if (weights[i] <= remaining) {
            ans = max(ans, (long long)values[i] + self(self, i + 1, remaining - weights[i]));
        }

        return ans;
    };

    return solve(solve, 0, capacity);
}
