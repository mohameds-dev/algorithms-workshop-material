# Group Anagrams

LeetCode 49: https://leetcode.com/problems/group-anagrams/

- Difficulty: Medium
- Topics: Array, Hash Table, String, Sorting
- Discussed: [Week 8, Day 1](../../weekly_material/week08_day1.md)

## Summary

Given an array of strings `strs`, group the anagrams together. You can return the answer in any order.

## Hints

<details>
<summary>Hints</summary>

1. Two strings are anagrams if and only if they share the same canonical signature.
2. What canonical signature can you use as a hash map key?
   - Option A: Sort the string alphabetically (e.g. `"eat"` becomes `"aet"`).
   - Option B: Count the frequency of each of the 26 characters (e.g. a tuple or formatted string of counts).
3. Use a hash map where each key is the canonical signature and each value is a list of strings that match that signature.
4. Extract all list values from the hash map to form the final grouped result.

</details>

## Solution

[`solution.py`](solution.py) / [`solution.cpp`](solution.cpp): hash map grouping by canonical signature.

- **Python approach:** We count character frequencies for each string into an array of size 26. We convert this count array to an immutable tuple `tuple(counts)` to serve as the dictionary key in a `defaultdict(list)`. This runs in $O(n \cdot k)$ time without sorting strings.
- **C++ approach:** For each string, we sort a copy to create the canonical string key (e.g. `"tea"` sorted becomes `"aet"`), and append the original string to `unordered_map<string, vector<string>>`. This avoids custom hash functions for vectors/tuples and runs in $O(n \cdot k \log k)$ time.

## Correctness

- **Claim:** All strings assigned to the same hash table bucket are mutual anagrams, and no two anagrams are assigned to different buckets.
- **Signature Invariance:** Any two strings $s_1$ and $s_2$ are anagrams if and only if their character multiset counts are identical. Sorting characters or computing character counts yields an identical key for $s_1$ and $s_2$.
- **Mapping:** Inserting each string into `groups[signature]` guarantees that every bucket contains precisely the anagrams for that specific signature. Collecting all bucket values produces a partition of the input strings into valid anagram groups.

## Complexity

Let $n$ be the number of strings and $k$ be the maximum length of a string:

- **Time:**
  - Python (character frequency tuple): $O(n \cdot k)$, since counting takes $O(k)$ per word and hashing a tuple of length 26 takes $O(1)$ time.
  - C++ (sorted string key): $O(n \cdot k \log k)$, since sorting each word takes $O(k \log k)$ time.
- **Space:** $O(n \cdot k)$ to store all strings and keys inside the hash map.
