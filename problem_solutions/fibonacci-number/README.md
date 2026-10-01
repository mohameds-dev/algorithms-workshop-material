# Fibonacci Number

LeetCode 509: https://leetcode.com/problems/fibonacci-number/

- Difficulty: Easy
- Topics: Recursion, Dynamic Programming, Math
- Discussed: [Week 1, Day 2](../../weekly_material/week01_day2.md), [Week 6, Day 2](../../weekly_material/week06_day2.md)

## Summary

The Fibonacci numbers are defined by the recurrence:

```
F(0) = 0
F(1) = 1
F(n) = F(n - 1) + F(n - 2),  for n > 1
```

Given `n`, return `F(n)`.

## Hints

1. The definition is already recursive: `F(n)` is defined directly in terms of `F(n - 1)` and
   `F(n - 2)`. What are the base cases, the values of `n` where the answer is already known
   without computing anything?
2. When recursing, the tree branches into duplicate subproblems (e.g. `F(3)` is computed multiple
   times when calculating `F(5)`). Store each computed answer in a lookup table (memoization) so
   that each subproblem is solved only once.
3. For an iterative approach (tabulation), start from the base cases and build upwards to `n`.
   Notice that computing `F(i)` only requires `F(i - 1)` and `F(i - 2)`. You can track just the
   last two values in variables to achieve O(1) auxiliary space.

## Solution

Three approaches, each provided in C++ and Python:

- **Recursive (Naive):**
  [`recursive_solution.cpp`](recursive_solution.cpp) /
  [`recursive_solution.py`](recursive_solution.py)
  Translates the mathematical definition directly. Computes the same subproblems repeatedly,
  yielding O(2^n) time (strictly Θ(1.618^n)) and O(n) space from call stack frames.
- **Top-Down Dynamic Programming (Memoization):**
  [`memoized_solution.cpp`](memoized_solution.cpp) /
  [`memoized_solution.py`](memoized_solution.py)
  Caches the result of `fib(k)` upon first evaluation. Subsequent recursive calls for the same
  subproblem return in O(1) time. Runs in O(n) time and O(n) space (memo table and call stack).
- **Bottom-Up Dynamic Programming (Tabulation):**
  [`iterative_solution.cpp`](iterative_solution.cpp) /
  [`iterative_solution.py`](iterative_solution.py)
  Fills a table iteratively from `i = 2` to `n` in dependency order. Eliminates recursive call
  stack overhead. Runs in O(n) time and O(n) space (reducible to O(1) space with rolling variables).
