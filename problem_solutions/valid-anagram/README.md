# Valid Anagram

LeetCode 242: https://leetcode.com/problems/valid-anagram/

- Difficulty: Easy
- Topics: Hash Table, String, Sorting
- Discussed: [Week 8, Day 1](../../weekly_material/week08_day1.md)

## Summary

Given two strings `s` and `t`, return `true` if `t` is an anagram of `s`, and `false` otherwise. An anagram is a word formed by rearranging the letters of a different word, using all original letters exactly once.

## Hints

<details>
<summary>Hints</summary>

1. If `len(s) != len(t)`, can `t` possibly be an anagram of `s`?
2. If two words are anagrams, what can you say about the frequency of each character in both words?
3. Instead of sorting (which costs $O(n \log n)$ time), can you count character occurrences in $O(n)$ time using an array of size 26 or a hash map?
4. You can increment character counts for `s` and decrement for `t` in a single pass. If all counts end at zero, the strings are anagrams.

</details>

## Solution

[`solution.py`](solution.py) / [`solution.cpp`](solution.cpp): single-pass frequency array of size 26.

We first check if `s` and `t` have identical lengths; if not, return `false` immediately. We maintain a frequency array of 26 integers representing lowercase English letters. As we iterate through both strings in lockstep, we increment the counter for each character in `s` and decrement the counter for each character in `t`. Finally, we check if all 26 counters equal zero.

## Correctness

- **Claim:** The frequency counter ends with all zeros if and only if `s` and `t` contain identical character multiset distributions.
- **Initialization:** An array of 26 zeros correctly represents empty strings.
- **Maintenance:** For each index `i`, incrementing `counts[s[i] - 'a']` and decrementing `counts[t[i] - 'a']` maintains the invariant that `counts[c]` equals the net difference between occurrences of character `c` in `s[0..i]` and `t[0..i]`.
- **Termination:** After all characters are processed, `counts[c] == 0` for every `c` if and only if the total count of character `c` in `s` equals its total count in `t`.

## Complexity

- **Time:** $O(n)$, where $n$ is the length of `s`. We scan each string once and inspect 26 constant buckets.
- **Space:** $O(1)$ auxiliary space, since the frequency table has a fixed size of 26 regardless of input size $n$.
