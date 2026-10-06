def solve_knapsack(weights: list[int], values: list[int], capacity: int) -> int:
    n = len(weights)
    memo = [[-1] * (capacity + 1) for _ in range(n)]

    def solve(i: int, remaining: int) -> int:
        if i == n:
            return 0
        if memo[i][remaining] != -1:
            return memo[i][remaining]
        
        ans = solve(i + 1, remaining)
        if weights[i] <= remaining:
            ans = max(ans, values[i] + solve(i + 1, remaining - weights[i]))
            
        memo[i][remaining] = ans
        return ans

    return solve(0, capacity)
