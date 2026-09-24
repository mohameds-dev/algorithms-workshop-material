# Counting Inversions

A classic divide and conquer counting problem, not on LeetCode as a standalone free problem.
[LeetCode 493, Reverse Pairs](https://leetcode.com/problems/reverse-pairs/) and
[LeetCode 315, Count of Smaller Numbers After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/)
are harder variants built on the same idea.

- Difficulty: Medium
- Topics: Array, Divide and Conquer, Merge Sort
- Discussed: [Week 5, Day 2](../../weekly_material/week05_day2.md)

## Summary

An inversion in an array `A[0:n]` is a pair of indices `(i, j)` with `i < j` and `A[i] > A[j]`.
Count the number of inversions in `A[0:n]` in `O(n log n)` time.

## Hints

Lay the counting on top of Merge Sort's own recursion: recursively count inversions in the left
half and the right half, then count cross inversions (one index in each half) while merging the
two sorted halves back together. A cross inversion shows up during the merge exactly when the
merge takes an element from the right half before the left half is exhausted: every element still
sitting in the left half beats it, so count that whole remaining stretch at once instead of one
pair at a time.

## Solution

[`solution.py`](solution.py) / [`solution.cpp`](solution.cpp): Merge Sort, modified to also
return an inversion count.

`merge_and_count(a, aux, lo, mid, hi)` is the usual merge step, plus a running `inversions`
counter: whenever it takes `aux[j]` from the right half before the left half (`aux[i:mid]`) is
exhausted, it adds `mid - i`, the number of elements still left in the left half, since each one
of them is bigger than `aux[j]` and appears earlier. `count_inversions(a, aux, lo, hi)` recurses
on both halves, sums their inversion counts, and adds the cross count from `merge_and_count`.

## Correctness

Proved in [Week 5, Day 2](../../weekly_material/week05_day2.md).

## Complexity

Same recurrence as Merge Sort, `T(n) = 2T(n/2) + O(n)`, so `T(n) = Θ(n log n)` by the Master
Theorem (Case 2). Space: `O(n)` for the auxiliary buffer, plus `O(log n)` for the recursion stack.
