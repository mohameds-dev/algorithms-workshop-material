# Subsets

LeetCode 78: https://leetcode.com/problems/subsets/

- Difficulty: Medium
- Topics: Array, Backtracking, Bit Manipulation
- Discussed: [Week 5, Day 1](../../weekly_material/week05_day1.md)

## Summary

Given an array `nums` of unique integers, return every possible subset (the power set), in any
order.

## Hints

`nums` has `n` unique elements, so it has `2^n` subsets: each element is independently in or out.
Walk the elements one at a time and, at each one, explore both choices before moving on.

## Solution

[`solution.py`](solution.py) / [`solution.cpp`](solution.cpp): backtracking, one include/exclude
decision per index.

`backtrack(nums, index, chosen, subsets)` decides `nums[index]`'s fate. If `index` has walked past
the end of `nums`, `chosen` is a complete subset, so a copy of it is recorded. Otherwise, it
explores leaving `nums[index]` out first (recurse on `index + 1` with `chosen` unchanged), then
explores putting it in (append it to `chosen`, recurse on `index + 1`, then pop it back off before
returning). The pop is what makes this backtracking: it undoes the choice so the next branch
starts from the same `chosen` the previous one did.

## Correctness

Proved in [Week 5, Day 1](../../weekly_material/week05_day1.md).

## Complexity

The recursion tree has exactly `2^n` leaves, one per subset, since every one of the `n` elements
doubles the leaf count. Each leaf pays `O(n)` to copy `chosen`. Time: `O(n * 2^n)`. Space: `O(n)`
for the recursion stack and the in-progress `chosen`, not counting the `O(n * 2^n)` output itself.
