def solve_knapsack(weights: list[int], values: list[int], capacity: int) -> int:
    n = len(weights)
    dp = [[0] * (capacity + 1) for _ in range(n + 1)]

    for i in range(1, n + 1):
        for w in range(capacity + 1):
            dp[i][w] = dp[i - 1][w]
            if weights[i - 1] <= w:
                dp[i][w] = max(dp[i][w], values[i - 1] + dp[i - 1][w - weights[i - 1]])

    return dp[n][capacity]


def test_solution():
    assert solve_knapsack([3, 4, 5], [30, 50, 60], 8) == 90
    assert solve_knapsack([1], [10], 1) == 10
    assert solve_knapsack([5], [10], 3) == 0


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
