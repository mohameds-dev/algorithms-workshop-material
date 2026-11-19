def solve_knapsack(weights: list[int], values: list[int], capacity: int) -> int:
    n = len(weights)
    dp = [0] * (capacity + 1)

    for i in range(n):
        for w in range(capacity, weights[i] - 1, -1):
            dp[w] = max(dp[w], values[i] + dp[w - weights[i]])

    return dp[capacity]


def test_solution():
    assert solve_knapsack([3, 4, 5], [30, 50, 60], 8) == 90
    assert solve_knapsack([1], [10], 1) == 10
    assert solve_knapsack([5], [10], 3) == 0


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
