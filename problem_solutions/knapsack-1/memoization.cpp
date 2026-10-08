#include <vector>
#include <algorithm>

using namespace std;

long long solve(int index, int remaining, const vector<int>& weights, const vector<int>& values, vector<vector<long long>>& memo) {
    if (index == (int)weights.size()) {
        return 0;
    }
    if (memo[index][remaining] != -1) {
        return memo[index][remaining];
    }

    long long max_value = solve(index + 1, remaining, weights, values, memo);
    if (weights[index] <= remaining) {
        max_value = max(max_value, (long long)values[index] + solve(index + 1, remaining - weights[index], weights, values, memo));
    }

    return memo[index][remaining] = max_value;
}

long long solve_knapsack(const vector<int>& weights, const vector<int>& values, int capacity) {
    int n = weights.size();
    vector<vector<long long>> memo(n, vector<long long>(capacity + 1, -1));
    return solve(0, capacity, weights, values, memo);
}
