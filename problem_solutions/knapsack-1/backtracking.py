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
