# Knapsack 1

AtCoder DP Task D: https://atcoder.jp/contests/dp/tasks/dp_d

- Difficulty: Medium
- Topics: Dynamic Programming
- Discussed: [Week 7, Day 1](../../weekly_material/week07_day1.md)

## Summary

Given `n` items, each with a weight and a value, and a knapsack with capacity `capacity`, find the maximum total value of items that can be packed without exceeding `capacity`.

## Hints

1. Every item presents a choice: take it or leave it. This is similar to the Subsets problem, but with a weight constraint.
2. The state can be defined by the current item index and the remaining capacity.
3. The naive recursion visits the same state multiple times. Cache the states (Memoization).
4. The transition only relies on the previous item. The 2D DP array can be optimized to 1D if you iterate the capacity backwards.

## Solution

- [`backtracking.py`](backtracking.py) / [`backtracking.cpp`](backtracking.cpp): Pure recursive backtracking ($O(2^n)$ time). Exhaustively explores the leave/take decision tree.
- [`memoization.py`](memoization.py) / [`memoization.cpp`](memoization.cpp): Top-down DP. Adds a 2D array cache to the backtracking solution to skip redundant subproblem calculations.
- [`tabulation_2d.py`](tabulation_2d.py) / [`tabulation_2d.cpp`](tabulation_2d.cpp): Bottom-up DP. Eliminates call stack overhead by iteratively filling a `dp[i][w]` table.
- [`tabulation_1d.py`](tabulation_1d.py) / [`tabulation_1d.cpp`](tabulation_1d.cpp): Bottom-up DP with dimension shrinking. Optimizes space to a 1D `dp[w]` array by iterating backwards.

## Correctness

Proved in [Week 7, Day 1](../../weekly_material/week07_day1.md).

## Complexity

- **Backtracking:**
  - Time: $O(2^n)$ to explore every leave/take choice.
  - Space: $O(n)$ for the recursion stack depth.
- **Memoization:**
  - Time: $O(n \cdot \text{capacity})$ bounded by the number of unique states.
  - Space: $O(n \cdot \text{capacity})$ for the cache, plus $O(n)$ for the recursion stack.
- **Tabulation (2D):**
  - Time: $O(n \cdot \text{capacity})$ to fill the table.
  - Space: $O(n \cdot \text{capacity})$ for the DP table. No recursion overhead.
- **Tabulation (1D):**
  - Time: $O(n \cdot \text{capacity})$ to fill the array.
  - Space: $O(\text{capacity})$ for the 1D DP array.
