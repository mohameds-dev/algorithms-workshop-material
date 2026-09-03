# Longest Nice Substring

LeetCode 1763: https://leetcode.com/problems/longest-nice-substring/description/

- Difficulty: Easy
- Topics: String, Divide and Conquer, Recursion
- Discussed: [Week 1, Day 2](../../weekly_material/week01_day2.md)

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

### Complexity

Each call scans its substring for a bad character and, in the worst case, builds
two new substrings from it, both O(n) where n is the length of the piece being examined. Across
the recursion this gives O(n^2) time in the worst case, with O(n) recursion depth.
