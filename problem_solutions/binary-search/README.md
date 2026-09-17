# Binary Search

LeetCode 704: https://leetcode.com/problems/binary-search/description/

- Difficulty: Easy
- Topics: Array, Binary Search
- Discussed: [Week 4, Day 1](../../weekly_material/week04_day1.md)

## Summary

Given an array of integers `nums`, sorted in ascending order, and a `target`, return the index of
`target` in `nums`, or `-1` if it isn't there. `nums` has distinct values. Must run in `O(log n)`.

## Hints

`nums` is sorted, so comparing `target` against the two endpoints answers "could this even be in
here" in `O(1)`. Past that, split the range at some middle point: which half could still contain
`target`, and which one definitely can't?

## Solution

[`solution.py`](solution.py) / [`solution.cpp`](solution.cpp): divide and conquer on the index
range.

`search_recursive(nums, target, left, right)` works on the range `nums[left..right]`. If the
range is empty (`left > right`) or down to one element (`left == right`), it answers directly.
Otherwise it picks `mid = (left + right) // 2` and asks whether `target` falls inside the value
range covered by the left half, `nums[left]` through `nums[mid]`. If so, the answer, if it exists
at all, has to be in `nums[left..mid]`, so it recurses there; otherwise it recurses on
`nums[mid+1..right]`.

## Correctness

Proved in [Week 4, Day 1](../../weekly_material/week04_day1.md).

## Complexity

Each call does `O(1)` work and recurses on a range at most half the size of the one it was given,
so `T(n) = T(n/2) + O(1)`, which the Master Theorem solves as `O(log n)` time. Space is `O(log n)`
for the recursion stack, since nothing is copied, only `left`/`right`/`target` are passed down.
