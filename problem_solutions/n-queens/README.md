# N-Queens

LeetCode 51: https://leetcode.com/problems/n-queens/

- Difficulty: Hard
- Topics: Array, Backtracking
- Discussed: [Week 6, Day 1](../../weekly_material/week06_day1.md)

## Summary

The **n-queens** puzzle asks for all distinct ways to place `n` queens on an `n x n` chessboard
such that no two queens attack each other. No two queens may share the same row, column, or
diagonal. Return each distinct board configuration, where `'Q'` indicates a queen and `'.'`
indicates an empty square.

## Pedagogical Progression

This problem is presented in three iterative steps:

1. [`verbose_inefficient_solution.py`](verbose_inefficient_solution.py): intuitive baseline testing
   rows, columns, and all four diagonal directions via ray-casting.
2. [`fair_solution.py`](fair_solution.py): honors the row-by-row recursion invariant (dropping
   redundant row checks and downward diagonal checks) and uses `col_reserved` for $O(1)$ column checks.
3. [`solution.py`](solution.py) / [`solution.cpp`](solution.cpp): optimal solution replacing
   diagonal ray-casting with $O(1)$ mathematical index lookups (`main_diagonal_reserved` and
   `anti_diagonal_reserved`).

## Hints

1. Since no two queens can share the same row, every row `0` to `n - 1` must contain exactly one
   queen. Place queens row by row.
2. For row `row`, choose a column `col` that does not conflict with any queen placed in rows `0` to
   `row - 1`. Because column indices must also be distinct, this is a permutation of
   `[0, ..., n - 1]` with diagonal constraints.
3. Test column conflicts in $O(1)$ with a boolean array `col_reserved` of size `n`.
4. Test diagonal conflicts in $O(1)$ using the geometry of chessboard diagonals:
   - Main diagonals (`\`): squares `(r, c)` have constant `r - c`. Since `r - c` ranges from
     `-(n - 1)` to `n - 1`, index into an array `main_diagonal_reserved` of size `2n - 1` using
     `r - c + n - 1`.
   - Anti-diagonals (`/`): squares `(r, c)` have constant `r + c`, ranging from `0` to `2n - 2`,
     indexing into an array `anti_diagonal_reserved` of size `2n - 1`.

## Solution

[`solution.py`](solution.py) / [`solution.cpp`](solution.cpp): inner recursive backtracking row by row,
with $O(1)$ column and diagonal pruning checks.

`backtrack(current_row)` places a queen in `current_row`:
- If `current_row == n`, all `n` rows are safely filled. Convert the `board` into strings and
  append to `answer`.
- Otherwise, try each column `col` from `0` to `n - 1`. Check `is_attacked(current_row, col)`:
  if `col_reserved[col]`, `main_diagonal_reserved[current_row - col + n - 1]`, or
  `anti_diagonal_reserved[current_row + col]` is true, skip it.
- For each valid `col`, place `'Q'`, mark `col_reserved`, `main_diagonal_reserved`, and
  `anti_diagonal_reserved` as true, recurse on `current_row + 1`, and unmark all three upon return
  before testing the next column.

## Correctness

Proved in [Week 6, Day 1](../../weekly_material/week06_day1.md).

## Complexity

- **Time:** bounded above by Permutations' `O(n!)`, since row `0` has `n` choices, row `1` has at
  most `n - 1`, row `2` at most `n - 2`, and so on. Diagonal pruning removes the vast majority of
  branches early (for `n = 8`, only 2,057 nodes are visited out of `8! = 40,320` full permutations).
  Constructing each valid `n x n` board takes `O(n^2)` time. Total time: `O(n!)` (more precisely,
  `O(S * n^2)` where `S` is the number of solutions, bounded by `O(n!)`).
- **Space:** `O(n)` working space for the recursion stack (depth `n`), `board` of size `n x n`,
  `col_reserved` array of size `n`, and diagonal tracking arrays of size `2n - 1`.
  (Excluding the `O(S * n^2)` space required to store all solutions).
