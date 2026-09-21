# Search a 2D Matrix

LeetCode 74: https://leetcode.com/problems/search-a-2d-matrix/description/

- Difficulty: Medium
- Topics: Array, Binary Search, Matrix
- Discussed: [Week 4, Day 2](../../weekly_material/week04_day2.md)

## Summary

Given an `m x n` matrix where each row is sorted in ascending order, and the first integer of
each row is greater than the last integer of the previous row, return whether `target` is
anywhere in the matrix.

## Hints

That second property, first integer of a row bigger than the last integer of the row before it,
means the rows' own starting values are increasing too. Binary search over the rows for the last
one whose first entry is `<= target`. Can any row after it contain `target`? Any row before it?

## Solution

[`solution.py`](solution.py) / [`solution.cpp`](solution.cpp): two binary searches, one after the
other.

`find_row(matrix, target)` binary searches over the rows themselves, comparing only
`matrix[mid][0]` against `target`, and keeps track of the largest row index seen whose first
entry is `<= target`. That's the one and only row that could possibly contain `target`; every
earlier row's values are all smaller, every later row's values are all bigger.

`search_row(row, target)` is then exactly the iterative `binary_search` from
[Week 4, Day 2](../../weekly_material/week04_day2.md), unchanged, run on that single row: it
returns `target`'s index in `row`, or `-1`, the same as `binary_search` returns for `nums`.
`searchMatrix` only needs whether `target` was found, so it turns that index into a bool with
`!= -1`.

## Correctness

Two things to establish, both in [Week 4, Day 2](../../weekly_material/week04_day2.md):

1. `find_row` returns the unique row that could contain `target` (or `-1` if none does), by a
   loop invariant on the sequence of row-starting values, the same shape as `binary_search`'s but
   for "find the last index where a monotonic condition holds" instead of "find an equal value".
2. `search_row` on that row is exactly `binary_search`, whose correctness is already proved, so
   `search_row(matrix[row], target) != -1` is true exactly when `target` is in that row.

## Complexity

`O(log(rows))` for `find_row`, plus `O(log(cols))` for `search_row`: `O(log(rows) + log(cols))`,
i.e. `O(log(rows * cols))` time, `O(1)` space, two sequential binary searches, no extra memory
beyond a few indices.
