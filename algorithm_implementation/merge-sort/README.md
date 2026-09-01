# Merge Sort

A classic divide and conquer sorting algorithm: split the array into two halves, recursively
sort each half, then merge the two sorted halves back into one sorted array in linear time.

- Discussed: [Week 2, Day 1](../../weekly_material/week02_day1.md)
- Practice: [LeetCode 912, Sort an Array](https://leetcode.com/problems/sort-an-array/description/)

## Summary

Given an array of `n` numbers, return it sorted in nondecreasing order.

## Solution

[`solution.cpp`](solution.cpp) / [`solution.py`](solution.py): `mergeSort(a, aux, lo, hi)` sorts
the range `a[lo, hi)` in place. If the range holds 0 or 1 elements it's already sorted (the base
case). Otherwise it splits the range at the midpoint, recursively sorts each half, then calls
`merge` to combine the two sorted halves back into a single sorted range, using `aux` as scratch
space so the merge doesn't overwrite elements it still needs to read.

This implementation differs from the pseudocode walked through in the weekly write-up in one
practical way: instead of each recursive call allocating and returning a brand-new array (which
is easy to reason about but does a lot of avoidable copying), it sorts a shared array in place
and reuses a single auxiliary buffer across the whole recursion, passed down by reference. The
divide and conquer structure, the base case, and the merge step are exactly the same idea; only
the memory management changed.

## Complexity

Merging two sorted ranges of total size `k` takes `O(k)` time. Splitting a range of size `n` in
half and recursing on each half, then merging, gives the recurrence:

```
T(n) = 2T(n/2) + O(n)
```

which solves to `T(n) = O(n log n)` by the recursion tree (or Master Theorem). Space is `O(n)`
for the auxiliary buffer, plus `O(log n)` for the recursion stack.

Further reading: Leiss, *A Programmer's Companion to Algorithm Analysis*, Section 3.2.4,
"MergeSort" (pp. 59-60), walks through this same recurrence and complexity argument in detail,
and discusses why the `O(n)` auxiliary space is the usual reason MergeSort is passed over in
practice despite being comparison-optimal.
