# Unique Paths II

LeetCode 63: https://leetcode.com/problems/unique-paths-ii/

- Difficulty: Medium
- Topics: Array, Dynamic Programming, Matrix
- Discussed: [Week 8, Day 1](../../weekly_material/week08_day1.md)

## Summary

You are given an $m \times n$ integer array `obstacleGrid`. There is a robot initially located at the top-left corner `(0, 0)`. The robot tries to move to the bottom-right corner `(m - 1, n - 1)`. The robot can only move either down or right at any point in time.

An obstacle and empty space are marked as `1` or `0` respectively. A path cannot pass through any cell that contains an obstacle. Return the number of unique paths to reach the destination.

## Hints

<details>
<summary>Hints</summary>

1. If the starting square `obstacleGrid[0][0] == 1` or destination `obstacleGrid[m - 1][n - 1] == 1`, can any path exist?
2. If cell `(r, c)` contains an obstacle, how many paths can pass through it? Exactly 0.
3. How does this modify the transition from Unique Paths I?
   - If `obstacleGrid[r][c] == 1`, set `dp[r][c] = 0`.
   - Otherwise, `dp[r][c] = dp[r - 1][c] + dp[r][c - 1]`.
4. In the 1D space-optimized version, whenever `obstacleGrid[row][col] == 1`, reset `dp[col] = 0`.

</details>

## Solution

[`solution.py`](solution.py) / [`solution.cpp`](solution.cpp): Dynamic Programming with obstacle reset and 1D space optimization.

We maintain a 1D array `dp` of size $n$, initialized to 0 with `dp[0] = 1`. For each row and column:
- If `obstacleGrid[row][col] == 1`, we set `dp[col] = 0`, because no path can proceed through an obstacle.
- Otherwise, if `col > 0`, we add the paths coming from the left cell: `dp[col] += dp[col - 1]`.
- Notice that if `col == 0`, `dp[0]` naturally carries forward its value from the cell directly above in the previous row, unless blocked by an obstacle.

## Correctness

- **Claim:** At the completion of outer loop iteration `row`, `dp[col]` stores the number of obstacle-free paths from `(0, 0)` to `(row, col)`.
- **Initialization:** `dp` has size $n$ with `dp[0] = 1` and all other entries 0. If `(0, 0)` contains an obstacle, `dp[0]` is immediately zeroed out during the first iteration.
- **Maintenance:** For any cell `(row, col)`:
  - If it contains an obstacle, no valid path can enter it, so setting `dp[col] = 0` is correct.
  - If it is clear, paths entering it must come from `(row - 1, col)` (stored in `dp[col]` from the previous row) or from `(row, col - 1)` (stored in `dp[col - 1]` from the current row). Summing them accounts for all obstacle-free arrivals.
- **Termination:** When both loops complete, `dp[n - 1]` contains the total paths reaching `(m - 1, n - 1)`.

## Complexity

- **Time:** $O(m \cdot n)$. Every cell in the grid is visited once.
- **Space:** $O(n)$ auxiliary space for the single 1D DP row array.
