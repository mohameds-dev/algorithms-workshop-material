# Generate Parentheses

LeetCode 22: https://leetcode.com/problems/generate-parentheses/

- Difficulty: Medium
- Topics: String, Dynamic Programming, Backtracking
- Discussed: [Week 8, Day 1](../../weekly_material/week08_day1.md)

## Summary

Given `n` pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

## Hints

<details>
<summary>Hints</summary>

1. A naive brute force generates all $2^{2n}$ sequences of `(` and `)` characters, then filters for valid ones. Can we prune invalid sequences during construction?
2. What makes a prefix of parentheses valid?
   - You can never add more than `n` opening parentheses: `open_count < n`.
   - You can never close a parenthesis that hasn't been opened: `close_count < open_count`.
3. If both invariants are preserved at every step, will every string that reaches length $2n$ be guaranteed well-formed?
4. Track `open_count` and `close_count` as recursion parameters.

</details>

## Solution

[`solution.py`](solution.py) / [`solution.cpp`](solution.cpp): recursive backtracking with balance pruning.

At each step in the recursion:
- If `open_count < n`, we can safely append `'('`, recurse with `open_count + 1`, and backtrack.
- If `close_count < open_count`, we can safely append `')'`, recurse with `close_count + 1`, and backtrack.
- Base case: when `len(current) == 2 * n`, record the string.

Because we never place a closing parenthesis without a matching opening parenthesis, every leaf reached in the recursion tree is guaranteed to be a valid combination.

## Correctness

- **Claim:** Every string added to `result` is well-formed, and all well-formed strings of length $2n$ are generated exactly once.
- **Base case:** When `len(current) == 2 * n`, because `open_count <= n` and `close_count <= open_count`, we must have `open_count == close_count == n`. Since every prefix satisfied `close_count <= open_count`, the sequence is valid.
- **Assume:** At depth $k < 2n$, `current` is a valid prefix with `close_count <= open_count <= n`.
- **Show:** The algorithm branches on all possible valid next characters:
  - If `open_count < n`, adding `'('` produces a valid prefix with `open_count + 1`.
  - If `close_count < open_count`, adding `')'` produces a valid prefix with `close_count + 1`.
  Since any valid continuation must either place `'('` or `')'`, no valid sequence is missed, and every branch explored remains valid.

## Complexity

- **Time:** $O\left(\frac{4^n}{\sqrt{n}}\right)$, or $O(C_n \cdot n)$, where $C_n = \frac{1}{n + 1}\binom{2n}{n}$ is the $n$-th Catalan number. Each valid sequence takes $O(n)$ time to copy into the result, and every tree branch leads to a valid leaf.
- **Space:** $O(n)$ auxiliary space for the recursion stack and the path buffer of length $2n$.
