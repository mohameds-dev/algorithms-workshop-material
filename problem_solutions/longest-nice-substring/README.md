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

[`solution.cpp`](solution.cpp): a divide and conquer approach.

`solve(l, r, s)` checks whether `s[l..r]` is nice by scanning for a character that doesn't
appear in both cases within that range. If it finds one at index `i`, the whole range can't be
nice, but a nice substring can't cross `i` either, so it recurses on the two halves on either
side, `[l, i - 1]` and `[i + 1, r]`, and stops scanning: no other split point in this range needs
checking, since one bad character is enough to guarantee non-niceness. If no such character is
found, `[l, r]` is nice, and it's compared against the best answer seen so far, kept as
`answer_l`/`answer_r`, preferring a longer substring, or, on a tie, the one that starts earlier.

This is the same "split at the point that breaks the property" idea from the hint, just made
concrete: the split point isn't the middle of the string, it's wherever a "bad" character turns
up.

**Complexity:** each call to `char_exists_in_both_cases` takes a substring and scans it, O(n)
where n is the length of the whole string, and `solve` calls it once per character in its range,
so a single `solve` call over a range of length k costs O(k * n). Across the recursion this
gives O(n^2) time in the worst case, with O(n) recursion depth.
