#include <vector>
#include <algorithm>

using namespace std;

long long solve(int index, int remaining, const vector<int>& weights, const vector<int>& values) {
    if (index == (int)weights.size()) {
        return 0;
    }

    long long max_value = solve(index + 1, remaining, weights, values);
    if (weights[index] <= remaining) {
        max_value = max(max_value, (long long)values[index] + solve(index + 1, remaining - weights[index], weights, values));
    }

    return max_value;
}

long long solve_knapsack(const vector<int>& weights, const vector<int>& values, int capacity) {
    return solve(0, capacity, weights, values);
}
