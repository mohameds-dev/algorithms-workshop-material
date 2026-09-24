# Social Permutations

A backtracking-with-pruning problem building on [Permutations](../permutations/), not on
LeetCode. The closest relatives are [LeetCode 51, N-Queens](https://leetcode.com/problems/n-queens/)
and [LeetCode 47, Permutations II](https://leetcode.com/problems/permutations-ii/), both
backtracking with a pruning rule instead of accepting every candidate.

- Difficulty: Medium
- Topics: Backtracking, Recursion
- Discussed: [Week 5, Day 2](../../weekly_material/week05_day2.md)

## Summary

`N` people, labeled `0` through `N - 1`, each give exactly one gift and receive exactly one gift:
a permutation `p`, where `p[i]` is who person `i` gives to. `p` is **social** if `p[i] != i` for
every `i` (no self-gift) and there's no pair `i, j` with `p[i] = j` and `p[j] = i` (no mutual
gift). Print every social permutation for a given `N`, using no more than `O(n)` memory.

## Hints

Start from [Permutations](../permutations/)' skeleton: build the permutation one position at a
time, tracking which values are already used. Add a check before recursing into each candidate
value, rejecting it if it's a self-gift or if it would complete a mutual pair with a position
already filled. That mutual-gift check only ever needs to look backward, at positions already
decided; a forward conflict gets caught later, symmetrically, when the recursion reaches that
later position.

## Solution

[`solution.py`](solution.py) / [`solution.cpp`](solution.cpp): backtracking, one position at a
time, with two pruning checks per candidate instead of accepting every unused value.

`backtrack(n, index, p, used)` fills `p[index]` next. If `index == n`, `p` is a complete social
permutation, so it's printed directly (no output list, unlike Permutations, since the problem only
asks to print). Otherwise, for each value `v` not yet `used`: skip it if `v == index` (self-gift)
or if `v < index and p[v] == index` (setting `p[index] = v` here would make `p` and `v` a mutual
pair, since `p[v]` already equals `index`). For every `v` that survives, set `p[index] = v`, mark
`used[v]`, recurse, then undo `used[v]` before trying the next candidate.

## Correctness

Proved in [Week 5, Day 2](../../weekly_material/week05_day2.md).

## Complexity

Time is bounded above by Permutations' `O(n * n!)` (pruning only ever skips work), though the real
leaf count is smaller since every permutation with a self-gift or a mutual pair is pruned out.
Space: `O(n)`, since `p` and `used` are both size `n` and, unlike Permutations, nothing is copied
into an output list; the recursion stack goes `n` frames deep.
