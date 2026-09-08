# Longest Nice Substring

LeetCode 1763: https://leetcode.com/problems/longest-nice-substring/description/

- Difficulty: Easy
- Topics: String, Divide and Conquer, Recursion
- Discussed: [Week 1, Day 2](../../weekly_material/week01_day2.md),
  [Week 2, Day 1](../../weekly_material/week02_day1.md) (idea and proof),
  [Week 2, Day 2](../../weekly_material/week02_day2.md) (built function by function),
  [Week 3, Day 1](../../weekly_material/week03_day1.md) (complexity and the hash table version)

## Summary

A substring is "nice" if every letter appearing in it shows up in both uppercase and lowercase.
Given a string, find its longest nice substring. If there are multiple of the same maximum
length, return the first one that occurs. If there is none, return an empty string.

Example: for `s = "YazaAay"`, `"aAa"` is nice, and it's the longest one in `s`.

## Hints

If a character in the string shows up in only one case, no letter, upper or lower, matching it
in the other case, no nice substring can contain that character at all. What does that tell you
about where you could split the string, and about what to do with each half?

## Solution

[`solution.cpp`](solution.cpp) / [`solution.py`](solution.py): a divide and conquer approach.

`solve(s)` scans `s` for a character that doesn't appear in both cases. If it finds one at index
`i`, `s` itself can't be nice, but a nice substring can't cross `i` either (it would still
contain the offending character), so the answer must lie entirely to the left or entirely to the
right of `i`. The function recurses on both halves, `s.substr(0, i)` and
`s.substr(i + 1, n - i - 1)`, and returns whichever comes back longer, preferring the left one on
a tie since it starts earlier in the original string. If no such character is found, `s` is
already nice, and is returned as is: the base case.

This is the same "split at the point that breaks the property" idea from the hint, just made
concrete: the split point isn't the middle of the string, it's wherever a "bad" character turns
up. Compared to tracking the best range seen so far with index bookkeeping, returning the
winning substring directly from each call keeps the recursion doing one job: answer the question
for this piece of the string, and let the return value carry the answer back up.

### Correctness

Proved by induction in [Week 2, Day 1](../../weekly_material/week02_day1.md), and again in
[Week 3, Day 1](../../weekly_material/week03_day1.md) one question at a time. The short version:
the base case is the `return s` line (no bad character means `s` is nice, and a string is its own
longest nice substring), and the inductive step is the split, which loses nothing because no nice
substring can contain a character that fails the both-cases check in `s`.

## Optimized solution

[`optimized_solution.cpp`](optimized_solution.cpp) /
[`optimized_solution.py`](optimized_solution.py): the same algorithm with one change. The check
`c.upper() in s` scans the whole piece, and the loop repeats that scan for every character even
though the piece never changes. Building a hash table of the characters in the piece once, up
front, turns each check into a lookup: `O(m)` to build, `O(1)` per check, instead of `O(m)` per
check.

The recursion, the base case, and the proof are untouched, since none of them depend on how
`char_exists_in_both_cases` answers, only on what it answers.

## Complexity

Take one call on a piece of length `m`, counting only what that call does itself:

| | Original | Optimized |
|---|---|---|
| One both-cases check | `O(m)`, two scans of the piece | `O(1)`, two hash lookups |
| The scan loop, up to `m` checks | `O(m^2)` | `O(m)` |
| Building the two pieces | `O(m)` | `O(m)` |
| **One call** | **`O(m^2)`** | **`O(m)`** |

There are `O(n)` calls in total: each call that splits permanently consumes the bad character at
index `i` and hands the rest to two calls whose pieces are disjoint, so there are at most `n`
splitting calls and at most `2n + 1` calls overall.

Multiplying the two gives `O(n^3)` worst case for the original and `O(n^2)` for the optimized
version. When the bad character lands near the middle of each piece, the recurrences are
`T(n) = 2T(n/2) + n^2` and `T(n) = 2T(n/2) + n`, which the Master Theorem solves as `O(n^2)`
(case 3) and `O(n log n)` (case 2, the Merge Sort recurrence).

Space is `O(n)` for the recursion depth, times the `O(m)` copy each call makes of its own pieces,
so up to `O(n^2)` characters alive at once in the worst case and `O(n)` when the splits are even.
Passing `start` and `end` indices instead of copying substrings would make it `O(n)` in every
case. The hash table adds nothing asymptotically: at most 52 entries per call.
