# Unique Paths

LeetCode 62: https://leetcode.com/problems/unique-paths/

- Difficulty: Medium
- Topics: Math, Dynamic Programming, Combinatorics
- Discussed: [Week 8, Day 1](../../weekly_material/week08_day1.md)

## Summary

There is a robot on an $m \times n$ grid. The robot is initially located at the top-left corner `(0, 0)` and wants to reach the bottom-right corner `(m - 1, n - 1)`. The robot can only move either down or right at any point in time. Given $m$ and $n$, return the number of possible unique paths to reach the target.

## Hints

<details>
<summary>Hints</summary>

1. Draw a small $3 \times 3$ grid on paper. How many ways can the robot reach cell `(r, c)`?
2. To land on `(r, c)`, the robot must come from either directly above (`(r - 1, c)`) or directly to the left (`(r, c - 1)`).
3. What are the base cases? The first row (`r = 0`) and the first column (`c = 0`) can only be reached in 1 way (moving straight right or straight down).
4. Do you need the entire 2D table in memory, or does each row only depend on the current row and the row immediately above it?

</details>

## Solution

[`solution.py`](solution.py) / [`solution.cpp`](solution.cpp): Dynamic Programming with 1D row space optimization.

- **2D Formulation:**
  Let `dp[r][c]` be the number of paths from `(0, 0)` to `(r, c)`.
  - Base cases: `dp[r][0] = 1` for all $r$, and `dp[0][c] = 1` for all $c$.
  - Recurrence: `dp[r][c] = dp[r - 1][c] + dp[r][c - 1]`.
- **1D Space Optimization:**
  Notice that `dp[r][c]` only requires the value directly above it (`dp[r - 1][c]`, which is the old value currently stored in `dp[col]`) and the value to its left (`dp[r][c - 1]`, which is `dp[col - 1]`).
  We initialize a single array `dp` of size $n$ filled with 1s. For each row from 1 to $m - 1$, we update:
  ```python
  dp[col] += dp[col - 1]
  ```

## Correctness

- **Claim:** At the completion of outer loop iteration `row`, `dp[col]` stores the number of unique paths from `(0, 0)` to `(row, col)`.
- **Initialization:** For `row = 0`, `dp[col] = 1` for all `col`, which is correct because the robot can only move right along the first row.
- **Maintenance:** In iteration `row`, before updating `dp[col]`, its value represents the paths to `(row - 1, col)` (from above). Adding `dp[col - 1]` (the newly computed paths to `(row, col - 1)` from the left) correctly sums both disjoint arrival paths according to the addition rule of counting.
- **Termination:** When the loops finish, `dp[n - 1]` holds the paths to `(m - 1, n - 1)`.

## Complexity

- **Time:** $O(m \cdot n)$. We visit each cell in the $m \times n$ grid once and do $O(1)$ addition per cell.
- **Space:** $O(n)$ auxiliary space for the 1D DP row array (or $O(\min(m, n))$ if we choose the smaller dimension).
