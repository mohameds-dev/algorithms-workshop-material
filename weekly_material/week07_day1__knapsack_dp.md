# Week 07, Day 1 (October 6, 2026)

## Today

Today we continue our exploration of **Dynamic Programming (DP)**.
We will introduce DP as a method for solving optimization problems (minimizing or maximizing a value) and counting problems, where we break down a problem into overlapping subproblems at different "states".

We will solve the classic **Knapsack 1** problem using a progression of three techniques:
1. **Memoization (Top-Down):** Adding a cache to the naive $O(2^n)$ recursive backtracking solution to bring it down to $O(n \cdot \text{capacity})$.
2. **Tabulation (Bottom-Up 2D):** Eliminating the call stack overhead by iteratively filling a 2D array representing the state.
3. **Tabulation (Bottom-Up 1D):** Shrinking the DP dimensions by recognizing that each row only depends on the previous row, reducing auxiliary space to $O(\text{capacity})$.

<details>
<summary>1. Introduction to Dynamic Programming</summary>

Dynamic Programming is a powerful technique for solving optimization problems (finding the maximum or minimum) and counting problems (finding the number of ways to do something).

It is applicable when a problem has two key properties:
1. **Overlapping Subproblems:** The problem can be broken down into smaller subproblems which are solved multiple times.
2. **Optimal Substructure:** The optimal solution to the overall problem can be constructed from the optimal solutions to its subproblems.

By identifying the **state** (the variables that uniquely define a subproblem) and the **recurrence relation** (the formula to transition between states), we can solve each subproblem once and store its result, avoiding exponential redundant work.

</details>

<details>
<summary>2. Knapsack 1 (AtCoder DP Task D)</summary>

**Problem:** You are given `n` items, each with a weight `w_i` and a value `v_i`. You have a knapsack with a maximum capacity `capacity`. Find the maximum total value of items you can pack into the knapsack without exceeding its capacity.

[AtCoder DP Task D](https://atcoder.jp/contests/dp/tasks/dp_d)

### Starter Code

```python
def solve_knapsack(weights: list[int], values: list[int], capacity: int) -> int:
    # Your code here
    pass
```

### Hints

<details>
<summary>Hints</summary>

1. Just like the **Subsets** problem, for each item you have a binary choice: either include it in the knapsack (if it fits) or exclude it.
2. What defines the state of your search? It depends on which item you are currently considering, and how much weight capacity is remaining in the knapsack.
3. Try to write a recursive function `solve(index, remaining_weight)`. If you take the item, what are the new parameters? If you leave it?
4. A naive recursion will be $O(2^n)$ because we recompute the same `(index, remaining_weight)` states multiple times. Use a 2D array to cache results (memoization), or build it iteratively (tabulation).

</details>

### Approaches

#### 1. Memoization (Top-Down)

The naive recursive approach (backtracking all leave/take options) correctly explores the full decision tree. However, it takes $O(2^n)$ time. Since many branches lead to the exact same `(index, remaining_weight)` state, we can cache the result of each state in a 2D array.

**Correctness:**
- **Claim:** `solve(index, remaining)` returns the maximum value obtainable using a subset of items from `index` to `n - 1` with weight limit `remaining`.
- **Base case:** If `index == n`, return `0` (no items left).
- **Assume:** `solve(index + 1, w)` works correctly for all $w \le \text{capacity}$.
- **Show:** We take the maximum of excluding the current item (`solve(index + 1, remaining)`) and, if it fits, including it (`values[index] + solve(index + 1, remaining - weights[index])`). This covers all valid choices and selects the optimal one.

#### 2. Tabulation (Bottom-Up 2D)

We can translate the memoization state into a 2D array `dp[i][w]`, representing the maximum value using the first `i` items with a weight limit of `w`. This removes the recursive call stack overhead.

**Correctness:**
- **Claim:** `dp[i][w]` is the maximum value using a subset of the first `i` items with total weight at most `w`.
- **Initialization:** `dp[0][w] = 0` for all `w` (0 items give 0 value).
- **Maintenance:** For each item `i` and capacity `w`, `dp[i][w]` correctly considers the optimal choice of leaving item `i` (`dp[i - 1][w]`) or taking it (`values[i - 1] + dp[i - 1][w - weights[i - 1]]`).
- **Termination:** The final answer is in `dp[n][capacity]`.

#### 3. Tabulation (Bottom-Up 1D)

Notice that `dp[i][...]` only depends on `dp[i - 1][...]`. We can shrink the 2D array to a 1D array `dp[w]` representing the maximum value for capacity `w` using the current items considered so far. We must iterate `w` backward from `capacity` to `weights[i - 1]` so we don't accidentally use the same item multiple times in a single step.

**Correctness:**
- **Claim:** After processing the `i`-th item, `dp[w]` is the maximum value using a subset of the first `i` items with total weight at most `w`.
- **Initialization:** `dp[w] = 0` for all `w` (using 0 items).
- **Maintenance:** Iterating `w` backward from `capacity` to `weights[i - 1]` ensures that when calculating the new `dp[w]` (which considers taking the item), we use the `dp[w - weights[i - 1]]` from the *previous* item's state. This prevents taking the same item multiple times.
- **Termination:** The final answer is in `dp[capacity]`.

### Code Links

Review the progression of solutions and complexity analysis in the problem directory:
- [Problem Description and Analysis](../problem_solutions/knapsack-1/README.md)
- [Backtracking (Python)](../problem_solutions/knapsack-1/backtracking.py) / [C++](../problem_solutions/knapsack-1/backtracking.cpp): Naive $O(2^n)$ recursive tree without optimization.
- [Memoization (Python)](../problem_solutions/knapsack-1/memoization.py) / [C++](../problem_solutions/knapsack-1/memoization.cpp): Top-down caching to prevent duplicate branches.
- [Tabulation 2D (Python)](../problem_solutions/knapsack-1/tabulation_2d.py) / [C++](../problem_solutions/knapsack-1/tabulation_2d.cpp): Bottom-up iterative table to eliminate recursion overhead.
- [Tabulation 1D (Python)](../problem_solutions/knapsack-1/tabulation_1d.py) / [C++](../problem_solutions/knapsack-1/tabulation_1d.cpp): Space-optimized array utilizing backward traversal.

</details>
