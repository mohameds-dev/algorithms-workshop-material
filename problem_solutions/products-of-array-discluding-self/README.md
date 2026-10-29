# Products of Array Discluding Self

LeetCode 238: https://leetcode.com/problems/product-of-array-except-self/
NeetCode: https://neetcode.io/problems/products-of-array-discluding-self

- Difficulty: Medium
- Topics: Array, Prefix Sum
- Discussed: [Week 10, Day 1](../../weekly_material/week10_day1.md)

## Summary

Given an integer array `nums`, return an array `answer` such that `answer[i]` is equal to the product of all elements of `nums` except `nums[i]`. You must write an algorithm that runs in $O(n)$ time and without using the division operation.

## Hints

<details>
<summary>Hints</summary>

1. If division were allowed, you could compute the total product of the array and divide by each element. But division is explicitly forbidden (and division fails when zeroes are present!).
2. For any index `i`, what elements make up the product? Everything strictly to the left of `i` (`0` to `i - 1`), multiplied by everything strictly to the right of `i` (`i + 1` to `n - 1`).
3. Can you precompute the running product from the left (a prefix product array)?
4. Can you precompute the running product from the right (a suffix product array)?
5. How can you combine `prefix[i - 1]` and `suffix[i + 1]` to find `answer[i]`? Watch out for the boundary elements `i == 0` and `i == n - 1`.

</details>

## Solution



[`solution.py`](solution.py) / [`solution.cpp`](solution.cpp): Prefix and suffix product arrays.


1. Build a `prefix` array where `prefix[i]` is the cumulative product of `nums[0]` through `nums[i]`.
2. Build a `suffix` array where `suffix[i]` is the cumulative product of `nums[n - 1]` down to `nums[i]`.
3. For each index `i`:
   - If `i == 0`, no elements exist to the left, so `answer[0] = suffix[1]`.
   - If `i == n - 1`, no elements exist to the right, so `answer[n - 1] = prefix[n - 2]`.
   - Otherwise, `answer[i] = prefix[i - 1] * suffix[i + 1]`.

## Correctness

- **Claim:** For every index $i \in [0, n - 1]$, `answer[i]` equals $\prod_{j \ne i} nums[j]$.
- **Prefix Invariant:** For each index $k$, `prefix[k]` equals $\prod_{j=0}^{k} nums[j]$. Therefore `prefix[i - 1]` contains the product of all elements strictly to the left of $i$.
- **Suffix Invariant:** For each index $k$, `suffix[k]` equals $\prod_{j=k}^{n-1} nums[j]$. Therefore `suffix[i + 1]` contains the product of all elements strictly to the right of $i$.
- **Combination:** Multiplying `prefix[i - 1] * suffix[i + 1]` covers all indices $j \in [0, i - 1] \cup [i + 1, n - 1]$ without including index $i$, and without using division.

## Complexity

- **Time:** $O(n)$, three independent passes of length $n$ across the array.
- **Space:** $O(n)$ auxiliary space to store the prefix and suffix arrays.
