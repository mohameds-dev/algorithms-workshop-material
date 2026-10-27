# Longest Consecutive Sequence

LeetCode 128: https://leetcode.com/problems/longest-consecutive-sequence/
NeetCode: https://neetcode.io/problems/longest-consecutive-sequence/

- Difficulty: Medium
- Topics: Array, Hash Table, Union Find
- Discussed: [Week 10, Day 2](../../weekly_material/week10_day2.md)

## Summary

Given an unsorted array of integers `nums`, return the length of the longest consecutive elements sequence. You must write an algorithm that runs in $O(n)$ time.

## Hints

<details>
<summary>Hints</summary>

1. Sorting the array takes $O(n \log n)$ time, which violates the strict $O(n)$ requirement. What data structure allows $O(1)$ average time lookups?
2. If you insert all numbers into a hash set, you can check whether any number `x` exists in $O(1)$ time.
3. How do you know if a number `x` is the **start** of a consecutive sequence?
4. If `x - 1` is in the set, then `x` cannot be the start of the sequence. Some smaller number already began this chain, so you should skip `x`.
5. Only when `x - 1` is not in the set do you start a while loop counting `x + 1`, `x + 2`, and so forth.
6. Why is this overall runtime $O(n)$ instead of $O(n^2)$?

</details>

## Solution

[`solution.py`](solution.py) / [`solution.cpp`](solution.cpp): Hash Set with sequence start detection.


1. Convert `nums` into an unordered hash set for $O(1)$ average lookups.
2. Iterate through each `num` in `nums`:
   - Check if `num - 1` is in the set. If it is, `num` is part of an ongoing chain, so skip it immediately.
   - If `num - 1` is not in the set, `num` is the first element of a potential longest sequence.
   - Use a while loop to check for consecutive neighbors: `num + 1`, `num + 2`, etc., keeping a running count `i`.
   - Update `answer = max(answer, i)`.
3. Return `answer`.

## Correctness

- **Claim:** The algorithm checks every maximal consecutive sequence and returns the length of the longest sequence in $O(n)$ time.
- **Maximal Sequence Identification:** Every contiguous sequence of consecutive numbers $[a, a + 1, \dots, a + k - 1]$ has a unique minimum element $a$. For this element, $a - 1$ is not in the set. For every other element $y \in [a + 1, a + k - 1]$, $y - 1$ is in the set, so the inner while loop never starts from $y$.
- **Amortized Linear Work:** Each number in `nums` enters the inner while loop condition at most once across the entire algorithm execution. Therefore, the total number of hash set lookups is bounded by $2n$, yielding $O(n)$ time.

## Complexity

- **Time:** $O(n)$, inserting elements into the hash set takes $O(n)$ time, and each number is visited at most twice during sequence expansion.
- **Space:** $O(n)$ auxiliary space to store unique numbers in the hash set.
