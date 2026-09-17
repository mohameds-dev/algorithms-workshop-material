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
means something stronger than "each row is sorted": read the matrix left to right, top to
bottom, and the values you see never go down. What does that make the matrix, if you squint?

## Solution

[`solution.py`](solution.py) / [`solution.cpp`](solution.cpp): the same iterative binary search
from [Week 4, Day 2](../../weekly_material/week04_day2.md), run over a virtual index range
`[0, rows * cols - 1]` instead of a real array. `mid` is turned into a cell with
`matrix[mid // cols][mid % cols]`, reading row by row; everything else, the `left`/`right`
narrowing and the three-way comparison against `target`, is unchanged.

## Correctness

Follows directly from binary search's correctness, proved in
[Week 4, Day 2](../../weekly_material/week04_day2.md). The only thing to add is that
`value(0), value(1), ..., value(rows * cols - 1)`, where `value(idx)` reads
`matrix[idx // cols][idx % cols]`, is nondecreasing: it's sorted within a row by the first part of
the problem's guarantee, and it doesn't drop across a row boundary by the second part. That makes
it exactly the sorted array binary search already runs on, just addressed through a row/column
mapping instead of held in one contiguous list.

## Complexity

`O(log(rows * cols))`, i.e. `O(log(rows) + log(cols))` time, `O(1)` space: one binary search over
`rows * cols` virtual elements, no extra memory beyond a few indices.
