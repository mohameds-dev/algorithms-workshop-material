# Week 07, Day 2 (October 8, 2026)

## Today

Today we continue our study of Dynamic Programming by analyzing **Longest Increasing Subsequence (LIS)** ([LeetCode 300](https://leetcode.com/problems/longest-increasing-subsequence/)).

Building on our Knapsack work from Day 1, we study how subproblem formulation dictates both time and memory efficiency. We progress through four distinct models:
1. **Backtracking (Top-Down Naive):** Decision tree trying include and exclude choices for each element ($O(2^n)$ time).
2. **Memoization (Top-Down DP):** Caching the pair `(current_index, prev_index)` in a 2D table ($O(n^2)$ time, $O(n^2)$ space).
3. **Tabulation (Bottom-Up DP):** Reformulating the subproblem as "the longest increasing subsequence ending strictly at index $i$" ($O(n^2)$ time, $O(n)$ space).
4. **Patience Sorting with Binary Search:** Maintaining the minimal tail values for each subsequence length, leveraging Week 4 binary search techniques ($O(n \log n)$ time, $O(n)$ space).

<details>
<summary>1. Subsequences, Greedy Limitations, and State Formulation</summary>

### Subarray vs Subsequence

- **Subarray:** A contiguous slice of an array. The order is preserved and elements must be physically adjacent in memory.
- **Subsequence:** A sequence derived by deleting zero or more elements without changing the relative order of the remaining elements.

### Why Simple Greedy Fails

A greedy approach makes an irrevocable choice using only local criteria. In LIS, every choice balances two competing goals:
1. **Keeping values small:** leaving room for future numbers to be greater.
2. **Staying far left in index:** leaving as many remaining elements as possible to pick from.

No single local heuristic balances both goals across all inputs:

#### Counterexample 1: Greedily picking the *first* greater element
- Array: `nums = [1, 100, 2, 3, 4]`
- Greedy choice: From `1`, take the immediate next greater element `100`. No remaining elements exceed `100`, giving `[1, 100]` (length 2).
- Optimal choice: Skip `100` to pick `[1, 2, 3, 4]` (length 4).
- Flaw: Jumping to a value that is too large locks out the rest of the array.

#### Counterexample 2: Greedily picking the *smallest* available greater element
- Array: `nums = [2, 6, 7, 8, 3, 4]`
- Greedy choice: From `2`, the smallest valid number to the right is `3` (at index 4). Jumping to `3` leaves only `4`, yielding `[2, 3, 4]` (length 3).
- Optimal choice: Take `[2, 6, 7, 8]` (length 4).
- Flaw: The smallest value was located near the end of the array, so jumping to it sacrificed a longer valid sequence of slightly larger numbers earlier in the array.

Because local rules cannot predict which trade-off is globally optimal, we must evaluate multiple candidate choices, which leads directly to **Dynamic Programming**.

### Identifying the Minimal State

To decide whether `nums[i]` can extend an existing increasing subsequence:
- We do not need the full history of all preceding elements in the subsequence.
- We only need to know the **last element** included so far.
- If `nums[i] > last_element`, then `nums[i]` can extend that subsequence.

</details>

<details>
<summary>2. Longest Increasing Subsequence (LeetCode 300)</summary>

**Problem:** Given an integer array `nums`, return the length of the longest strictly increasing subsequence.

[LeetCode 300: Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/)

### Starter Code

```python
class Solution:
    def lengthOfLIS(self, nums: list[int]) -> int:
        # Your code here
        pass
```

### Hints

<details>
<summary>Hints</summary>

1. Start by thinking about an include or exclude decision at each index `i`. What information does the recursive function need to know about past choices?
2. If we track the index of the previous included element, `prev_index`, our recursive state is `(index, prev_index)`. How many such states exist?
3. In bottom-up DP, can we eliminate one dimension? Instead of asking "what is the best subsequence from index `i` onward given `prev_index`", ask: "what is the length of the longest increasing subsequence that ends at `nums[i]`?"
4. If `lis[i]` stores the LIS ending at `nums[i]`, then for every `j < i` where `nums[i] > nums[j]`, `nums[i]` can extend the subsequence ending at `j`.
5. As a follow-up, can we achieve $O(n \log n)$? Maintain an array `tails` where `tails[k]` stores the smallest ending element among all increasing subsequences of length `k + 1`. Notice that `tails` is always sorted, which allows binary search.

</details>

### Approaches

#### 1. Backtracking (Top-Down Naive)

At each element `nums[index]`, we branch into two options:
- Exclude `nums[index]`: move to `index + 1` with `prev_index` unchanged.
- Include `nums[index]` (only if `prev_index == -1` or `nums[index] > nums[prev_index]`): move to `index + 1` with `prev_index = index`.

**Correctness:**
- **Claim:** `solve(index, prev_index)` returns the maximum length of an increasing subsequence from `nums[index:]` whose elements are all strictly greater than `nums[prev_index]`.
- **Base case:** If `index == n`, no elements remain, so the function returns `0`.
- **Assume:** `solve(index + 1, p)` correctly computes the optimal length for all valid previous indices `p`.
- **Show:** The optimal subsequence either omits `nums[index]` or includes it (if valid). Taking the maximum of `solve(index + 1, prev_index)` and `1 + solve(index + 1, index)` exhaustively covers all legal decisions from `index` onward.

#### 2. Memoization (Top-Down DP)

Because `index` ranges from `0` to `n` and `prev_index` ranges from `-1` to `n - 1`, there are only $n \times (n + 1)$ distinct parameter pairs. We cache results in a 2D table `memo[index][prev_index + 1]`.

- Time complexity drops from $O(2^n)$ to $O(n^2)$.
- Space complexity is $O(n^2)$ for the table plus $O(n)$ for the call stack.

#### 3. Tabulation (Bottom-Up DP)

We reformulate the state: let `lis[i]` be the length of the longest strictly increasing subsequence that ends strictly at `nums[i]`.

For each `i` from `0` to `n - 1`, we check all previous indices `j < i`:
- If `nums[i] > nums[j]`, we can append `nums[i]` to any subsequence ending at `j`.
- Recurrence: `lis[i] = max(lis[i], lis[j] + 1)`.
- Base case: `lis[i] = 1` for all `i` (every single element forms a valid subsequence of length 1).
- Result: $\max_{0 \le i < n} \text{lis}[i]$.

**Correctness:**
- **Claim:** At the completion of outer loop iteration `i`, `lis[i]` holds the length of the longest increasing subsequence ending at `nums[i]`.
- **Initialization:** `lis[i] = 1` for each index, which is correct because the single element `[nums[i]]` is an increasing subsequence of length 1.
- **Maintenance:** For each `j < i` where `nums[i] > nums[j]`, appending `nums[i]` to the optimal subsequence ending at `nums[j]` yields a valid increasing subsequence of length `lis[j] + 1`. Taking the maximum over all such `j` guarantees that `lis[i]` is optimal.
- **Termination:** When the outer loop reaches `n`, every `lis[i]` has been computed. The longest increasing subsequence overall must end at some index $i \in [0, n - 1]$, so taking $\max(\text{lis})$ yields the global maximum.

#### 4. Patience Sorting with Binary Search ($O(n \log n)$)

To improve beyond $O(n^2)$, we construct an auxiliary array `tails`, where `tails[k]` stores the smallest tail element of all increasing subsequences of length `k + 1` found so far.

For each `x` in `nums`:
- Use binary search (`bisect_left` in Python, `std::lower_bound` in C++) to find the first index `idx` such that `tails[idx] >= x`.
- If `idx == len(tails)`, `x` is strictly greater than all recorded tails, so append `x` to `tails` (creating a new longest subsequence).
- Otherwise, set `tails[idx] = x`. A smaller tail allows future numbers more opportunities to extend this subsequence.
- Return `len(tails)`.

**Correctness:**
- **Claim:** Throughout the execution, `tails` is strictly increasing, and `len(tails)` equals the length of the longest increasing subsequence of the prefix processed so far.
- **Initialization:** Before processing any elements, `tails` is empty, which trivially represents an LIS of length 0.
- **Maintenance:** For each element `x`, binary search finds the smallest index `idx` where `tails[idx] >= x`. If `idx == len(tails)`, `x` extends the longest known subsequence of length `len(tails)`, making a new valid sequence of length `len(tails) + 1`. If `idx < len(tails)`, replacing `tails[idx]` with `x` preserves the strictly increasing order of `tails` while lowering the tail boundary for subsequences of length `idx + 1`.
- **Termination:** After all $n$ elements are examined, `len(tails)` corresponds to the length of the longest strictly increasing subsequence in the entire array.

### Code Links

Review the progression of solutions and complexity analysis in the problem directory:
- [Problem Description and Analysis](../problem_solutions/longest-increasing-subsequence/README.md)
- [Backtracking (Python)](../problem_solutions/longest-increasing-subsequence/backtracking.py) / [C++](../problem_solutions/longest-increasing-subsequence/backtracking.cpp): Naive $O(2^n)$ recursive tree without optimization.
- [Memoization (Python)](../problem_solutions/longest-increasing-subsequence/memoization.py) / [C++](../problem_solutions/longest-increasing-subsequence/memoization.cpp): Top-down caching to prevent duplicate branches ($O(n^2)$ time, $O(n^2)$ space).
- [Tabulation (Python)](../problem_solutions/longest-increasing-subsequence/tabulation.py) / [C++](../problem_solutions/longest-increasing-subsequence/tabulation.cpp): Bottom-up iterative table tracking LIS ending at index $i$ ($O(n^2)$ time, $O(n)$ space).
- [Binary Search (Python)](../problem_solutions/longest-increasing-subsequence/binary_search.py) / [C++](../problem_solutions/longest-increasing-subsequence/binary_search.cpp): Optimal patience sorting with binary search ($O(n \log n)$ time, $O(n)$ space).

</details>
