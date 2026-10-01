# N-th Tribonacci Number

LeetCode 1137: https://leetcode.com/problems/n-th-tribonacci-number/

- Difficulty: Easy
- Topics: Dynamic Programming, Math, Memoization
- Discussed: [Week 6, Day 2](../../weekly_material/week06_day2.md)

## Summary

The Tribonacci sequence $T_n$ is defined as follows:

```
T(0) = 0
T(1) = 1
T(2) = 1
T(n) = T(n - 1) + T(n - 2) + T(n - 3),  for n >= 3
```

Given `n`, return the value of $T(n)$.

## Hints

1. The problem is a direct 3-term generalization of Fibonacci numbers.
2. What are the base cases? $T(0) = 0$, $T(1) = 1$, and $T(2) = 1$.
3. For memoization, cache values in an array of size $n + 1$ initialized to `-1`.
4. For space-optimized tabulation, how many past values do you need to calculate the next state?
   Only three values: `a0`, `a1`, and `a2`. You can update them simultaneously in $O(1)$ space.

## Solution

Three approaches, each provided in C++ and Python:

- **Top-Down Dynamic Programming (Memoization):**
  [`memoized_solution.py`](memoized_solution.py) / [`memoized_solution.cpp`](memoized_solution.cpp)
  Recursively evaluates `solve(num)` and caches the result in `mem[num]`. Runs in $O(n)$ time and
  $O(n)$ space (recursion stack and cache).

- **Bottom-Up Dynamic Programming (Tabulation):**
  [`iterative_solution.py`](iterative_solution.py) / [`iterative_solution.cpp`](iterative_solution.cpp)
  Iteratively fills an array `trib` of size $n + 1$ from $i = 3$ to $n$. Runs in $O(n)$ time and
  $O(n)$ space.

- **Space-Optimized Tabulation:**
  [`optimized_iterative_solution.py`](optimized_iterative_solution.py) /
  [`optimized_iterative_solution.cpp`](optimized_iterative_solution.cpp)
  Maintains three rolling variables (`a0`, `a1`, `a2`) to compute the next sum in $O(1)$ space.

- **Combined Reference:**
  [`solution.py`](solution.py) / [`solution.cpp`](solution.cpp) exposes all methods.

## Complexity

| Approach | Time Complexity | Auxiliary Space | Recursion Stack |
|---|---|---|---|
| Memoization | $O(n)$ | $O(n)$ | $O(n)$ |
| Tabulation | $O(n)$ | $O(n)$ | $O(1)$ |
| Optimized Tabulation | $O(n)$ | $O(1)$ | $O(1)$ |
