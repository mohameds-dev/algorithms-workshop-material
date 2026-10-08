# Longest Increasing Subsequence

LeetCode 300: https://leetcode.com/problems/longest-increasing-subsequence/

- Difficulty: Medium
- Topics: Array, Binary Search, Dynamic Programming
- Discussed: [Week 7, Day 2](../../weekly_material/week07_day2.md)

## Summary

Given an integer array `nums`, return the length of the longest strictly increasing subsequence. A subsequence is derived from an array by deleting zero or more elements without changing the order of the remaining elements.

## Hints

1. A naive approach explores every subsequence by making an include or exclude choice at each index, running in $O(2^n)$ time.
2. What defines the state needed to decide if the next number can be added? You only need the current index and the index of the last element included.
3. In tabulation, redefine the subproblem: let `lis[i]` be the length of the longest increasing subsequence that ends strictly at index `i`. For each `i`, look back at all `j < i` where `nums[i] > nums[j]`.
4. Can we do better than $O(n^2)$? Maintain an array `tails` where `tails[k]` stores the smallest ending element of an increasing subsequence of length `k + 1`. Because `tails` remains sorted, binary search identifies the update position in $O(\log n)$ time per element.

## Solution

- [`backtracking.py`](backtracking.py) / [`backtracking.cpp`](backtracking.cpp): Pure recursive backtracking ($O(2^n)$ time). Tries both include and exclude branches at each element.
- [`memoization.py`](memoization.py) / [`memoization.cpp`](memoization.cpp): Top-down DP. Caches `(index, prev_index)` pairs in a 2D table to avoid recomputing identical recursive subtrees.
- [`tabulation.py`](tabulation.py) / [`tabulation.cpp`](tabulation.cpp): Bottom-up DP ($O(n^2)$ time, $O(n)$ space). Computes the longest increasing subsequence ending at each index using a 1D array.
- [`binary_search.py`](binary_search.py) / [`binary_search.cpp`](binary_search.cpp): Patience sorting with binary search ($O(n \log n)$ time, $O(n)$ space). Maintains the minimum tail for each subsequence length.

## Correctness

Proved in [Week 7, Day 2](../../weekly_material/week07_day2.md).

## Complexity

- **Backtracking:**
  - Time: $O(2^n)$ to explore every include or exclude combination.
  - Space: $O(n)$ for the recursive call stack depth.
- **Memoization:**
  - Time: $O(n^2)$ as there are $n \times (n + 1)$ unique states, each evaluated in $O(1)$ time.
  - Space: $O(n^2)$ for the 2D memoization table, plus $O(n)$ for recursion stack depth.
- **Tabulation:**
  - Time: $O(n^2)$ via nested loops checking all pairs $(i, j)$ with $0 \le j < i < n$.
  - Space: $O(n)$ for the 1D DP array.
- **Binary Search:**
  - Time: $O(n \log n)$ across $n$ elements, performing a binary search in $O(\log n)$ time for each element.
  - Space: $O(n)$ for the tails array.
