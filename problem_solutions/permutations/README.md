# Permutations

LeetCode 46: https://leetcode.com/problems/permutations/

- Difficulty: Medium
- Topics: Array, Backtracking
- Discussed: [Week 5, Day 1](../../weekly_material/week05_day1.md)

## Summary

Given an array `nums` of `n` distinct integers, return every possible ordering (permutation) of
them, in any order.

## Hints

There are `n!` permutations: `n` choices for the first slot, `n - 1` for the second (whatever's
left), and so on. Track which elements are still unused and, at each step, try every one of them
next.

## Solution

[`solution.py`](solution.py) / [`solution.cpp`](solution.cpp): backtracking, choose the next
element from whatever's left.

`backtrack(nums, used, chosen, permutations)` builds one ordering at a time. If `chosen` already
holds every element, it's a complete permutation, so a copy is recorded. Otherwise, for each index
`i` not yet marked `used`, it marks it, appends `nums[i]` to `chosen`, recurses, then undoes both
(pops `chosen`, clears `used[i]`) before trying the next `i`. Undoing after each recursive call is
what lets the same `used` array and `chosen` list get reused across every branch of the loop
instead of needing a fresh copy per branch.

## Correctness

Proved in [Week 5, Day 1](../../weekly_material/week05_day1.md).

## Complexity

The recursion tree has exactly `n!` leaves, one per permutation, since the branching factor is
`n`, then `n - 1`, then `n - 2`, and so on down to `1`. Each leaf sits at depth `n` and pays `O(n)`
to copy `chosen`. Time: `O(n * n!)`. Space: `O(n)` for the recursion stack, `chosen`, and `used`,
not counting the `O(n * n!)` output itself.
