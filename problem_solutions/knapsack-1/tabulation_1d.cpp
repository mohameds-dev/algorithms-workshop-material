#include <cassert>
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

#include <iostream>

void test_solution() {
    vector<int> weights = {3, 4, 5};
    vector<int> values = {30, 50, 60};
    assert(solve_knapsack(weights, values, 8) == 90);
    assert(solve_knapsack({1}, {10}, 1) == 10);
    assert(solve_knapsack({5}, {10}, 3) == 0);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
