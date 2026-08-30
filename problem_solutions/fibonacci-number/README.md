# Fibonacci Number

LeetCode 509: https://leetcode.com/problems/fibonacci-number/

- Difficulty: Easy
- Topics: Recursion, Dynamic Programming, Math
- Discussed: [Week 1, Day 2](../../weekly_material/week01_day2.md)

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
2. For an iterative approach, you don't need to remember every value of `F`, only enough to
   compute the next one. How many previous values does the definition actually depend on? Try
   tracking just the last two values, updating them as you count up from 0 to `n`.

## Solution

Two approaches, each provided in C++ and Python, both O(n) auxiliary space (see the note on the
recursive version's actual space use below):

- [`recursive_solution.cpp`](recursive_solution.cpp) /
  [`recursive_solution.py`](recursive_solution.py): translates the math definition directly.
  `fib(n)` returns immediately on the base cases (`n == 0`, `n == 1`) and otherwise returns
  `fib(n - 1) + fib(n - 2)`. Simple and reads like the definition, but recomputes the same
  subproblems repeatedly (e.g. `fib(3)` is computed multiple times while evaluating `fib(5)`),
  giving O(2^n) time and O(n) space from the call stack depth.
- [`iterative_solution.cpp`](iterative_solution.cpp) /
  [`iterative_solution.py`](iterative_solution.py): builds up the sequence from the base cases
  in a loop, storing each value as it goes. O(n) time and O(n) space (a fixed-size array here;
  this could be reduced to O(1) space by keeping only the last two values, as hinted above).

The repeated work in the recursive version is the seed for memoization and dynamic programming,
covered later in the semester.
