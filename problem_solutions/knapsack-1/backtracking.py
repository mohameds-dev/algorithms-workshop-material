def solve_knapsack(weights: list[int], values: list[int], capacity: int) -> int:
    n = len(weights)

    def solve(i: int, remaining: int) -> int:
        if i == n:
            return 0
        
        ans = solve(i + 1, remaining)
        if weights[i] <= remaining:
            ans = max(ans, values[i] + solve(i + 1, remaining - weights[i]))
            
        return ans

    return solve(0, capacity)


def test_solution():
    assert solve_knapsack([3, 4, 5], [30, 50, 60], 8) == 90
    assert solve_knapsack([1], [10], 1) == 10
    assert solve_knapsack([5], [10], 3) == 0


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
