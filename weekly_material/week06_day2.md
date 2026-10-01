# Week 06, Day 2 (October 1, 2026)

## Today

Today we conclude our backtracking unit by consolidating the complexity models across all four
backtracking benchmarks we have studied (Subsets, Permutations, Social Permutations, and N-Queens).
We then pivot to **Dynamic Programming (DP)**: examining why backtracking is required when every
configuration is distinct, and how problems with overlapping subproblems and optimal substructure
can be optimized from exponential time down to polynomial time.

We study this transition using [LeetCode 509, Fibonacci Number](https://leetcode.com/problems/fibonacci-number/) and [LeetCode 70, Climbing Stairs](https://leetcode.com/problems/climbing-stairs/):
1. Analyze the naive recursive tree and quantify the cost of duplicate subproblems ($O(2^n)$ time).
2. Apply **top-down Dynamic Programming (Memoization)** to prune duplicate subtrees ($O(n)$ time).
3. Convert to **bottom-up Dynamic Programming (Tabulation)** to eliminate recursive stack overhead ($O(n)$ time).
4. Apply state compression to achieve $O(1)$ auxiliary space.
5. Contrast tabular traversal mindsets: **Pull DP** (lookback) vs **Push DP** (forward dispatching).
6. Compare the complexity profiles, execution trade-offs, and design patterns across all approaches.

<details>
<summary>1. Backtracking review and complexity models</summary>

Over the last two weeks, we developed four distinct backtracking structures. Review the
individual solutions and proofs in their respective session notes:

- **Subsets:** [Week 5, Day 1](week05_day1.md) and [`problem_solutions/subsets/`](../problem_solutions/subsets/)
- **Permutations:** [Week 5, Day 1](week05_day1.md) and [`problem_solutions/permutations/`](../problem_solutions/permutations/)
- **Social Permutations:** [Week 5, Day 2](week05_day2.md) and [`problem_solutions/social-permutations/`](../problem_solutions/social-permutations/)
- **N-Queens:** [Week 6, Day 1](week06_day1.md) and [`problem_solutions/n-queens/`](../problem_solutions/n-queens/)

### Comparing the four decision models

| Problem | Decision per step | Branching factor | Tree leaves | Time complexity | Working space | Pruning mechanism |
|---|---|---|---|---|---|---|
| Subsets | Include or exclude element | 2 (fixed) | `2^n` | `O(n * 2^n)` | `O(n)` | None (full power set) |
| Permutations | Pick next unused element | `n - level` (shrinking) | `n!` | `O(n * n!)` | `O(n)` | None (all orderings) |
| Social Permutations | Pick unused element without conflict | `<= n - level` (pruned) | `< n!` | `O(n * n!)` bound | `O(n)` | Backward checks: no self-gift, no mutual gift |
| N-Queens | Pick unused column and safe diagonals | `<= n - level` (heavily pruned) | Valid boards $S \ll n!$ | `O(n!)` bound | `O(n^2)` or `O(n)` | $O(1)$ lookups for columns and both diagonals |

### Four structural observations

1. **Fixed vs shrinking branching factor:** Subsets makes a binary decision at each index, yielding
   a full binary recursion tree of depth `n` with $2^n$ leaves. Permutations selects an unused
   element, starting with `n` branches, then `n - 1`, down to `1`, producing $n!$ leaves.
2. **Copying dominates leaf cost:** Both Subsets and Permutations perform $O(1)$ work at internal
   nodes (excluding loop setup), but pay $O(n)$ at each leaf to copy the accumulated solution
   into the results array. For N-Queens, copying the formatted board of $n$ strings of length $n$
   takes $O(n^2)$ time per valid solution.
3. **Pruning avoids entire subtrees:** Social Permutations and N-Queens use the exact same skeleton as
   Permutations, but verify constraints before recursing. An invalid choice is pruned immediately,
   preventing the recursion from expanding subtrees that cannot lead to valid outputs.
4. **Working space is linear:** Backtracking traverses depth-first (DFS). Because we only maintain
   the current path on the call stack and undo changes when returning, auxiliary working space
   is $O(n)$ (or $O(n^2)$ for the board representation in N-Queens), excluding the output container.

<details>
<summary>Question: When should we use include/exclude vs next-element choice?</summary>

Use **include/exclude** when each item has an independent binary state (present or absent), and
ordering does not matter. The search tree depth is fixed to the number of items, and the branching
factor is always 2.

Use **next-element choice** when placing items into sequential slots or orderings. The choices at
each step depend on which elements remain available, producing a shrinking branching factor.

</details>

<details>
<summary>Question: Why can't we use memoization on Subsets or Permutations?</summary>

Every leaf in Subsets and Permutations represents a distinct combinatorial configuration that must
appear in the final output. There are no "duplicate" answers to cache or reuse; the search path
itself is the result.

</details>

</details>

<details>
<summary>2. The pivot to Dynamic Programming</summary>

Backtracking is mandatory when we need to generate or list every distinct valid state. But what
happens when a problem asks for a single aggregate value (e.g. the $n$-th number, the maximum
profit, the minimum coins, or the count of valid ways)?

When an algorithm breaks a problem into subproblems, three distinct paradigms emerge:

1. **Divide and Conquer:** Subproblems are independent and non-overlapping.
   - Example: Merge Sort splits an array into completely disjoint left and right halves. Neither
     half solves problems needed by the other.
2. **Backtracking:** Search space contains distinct configurations; paths must be exhaustively explored.
   - Example: Permutations and N-Queens generate unique permutations and board placements.
3. **Dynamic Programming:** Subproblems are **overlapping** and have **optimal substructure**.
   - **Overlapping subproblems:** The recursive formulation calls the exact same subproblem
     repeatedly with the exact same arguments.
   - **Optimal substructure:** An optimal solution to the overall problem can be constructed from
     optimal solutions to its subproblems.

Instead of recomputing the same subproblem exponentially many times, Dynamic Programming solves
each subproblem once, saves the result, and looks it up in subsequent encounters.

</details>

<details>
<summary>3. Fibonacci: naive recursion and overlapping work</summary>

[LeetCode 509, Fibonacci Number](https://leetcode.com/problems/fibonacci-number/):
The Fibonacci sequence is defined by the mathematical recurrence:

```
F(0) = 0
F(1) = 1
F(n) = F(n - 1) + F(n - 2),  for n > 1
```

Recall our initial encounter in [Week 1, Day 2](week01_day2.md).
Translating the math definition directly into code yields naive recursion:

- Python: [`recursive_solution.py`](../problem_solutions/fibonacci-number/recursive_solution.py)
- C++: [`recursive_solution.cpp`](../problem_solutions/fibonacci-number/recursive_solution.cpp)
- Writeup: [`problem_solutions/fibonacci-number/README.md`](../problem_solutions/fibonacci-number/README.md)

```python
def fib(n: int) -> int:
    if n == 0:
        return 0
    if n == 1:
        return 1
    return fib(n - 1) + fib(n - 2)
```

### Visualizing the redundant work

Tracing the call tree for `fib(5)`:

```
                       fib(5)
                    /          \
             fib(4)              fib(3)
            /      \            /      \
        fib(3)    fib(2)      fib(2)   fib(1)
       /     \    /    \      /    \
    fib(2) fib(1) fib(1) fib(0) fib(1) fib(0)
    /    \
  fib(1) fib(0)
```

Count how many times each subproblem is evaluated while computing `fib(5)`:
- `fib(5)`: 1 time
- `fib(4)`: 1 time
- `fib(3)`: 2 times
- `fib(2)`: 3 times
- `fib(1)`: 5 times
- `fib(0)`: 3 times

Total function calls: 15 calls to compute a value that depends on only 6 distinct inputs ($0$ to $5$).

### Complexity of naive recursion

**Time:** The recurrence is $T(n) = T(n - 1) + T(n - 2) + O(1)$.
This recurrence is proportional to the Fibonacci numbers themselves: the total number of operations
is $2 \cdot F(n + 1) - 1 = \Theta(\phi^n)$, where $\phi = \frac{1 + \sqrt{5}}{2} \approx 1.618$ (the golden ratio).
Upper bounded by **$O(2^n)$**.

**Space:** The maximum depth of the call stack is $n$ frames (from the leftmost chain `fib(n) -> fib(n-1) -> ... -> fib(0)`).
Auxiliary space is **$O(n)$**.

For $n = 50$, $2^{50} \approx 1.13 \times 10^{15}$ operations, requiring days of compute. Yet there are
only 51 distinct subproblems ($F(0)$ through $F(50)$). All redundant calls compute the exact same
outputs from the exact same inputs.

</details>

<details>
<summary>4. Top-down Dynamic Programming: Memoization</summary>

### The core idea

If we compute `fib(3)` once, write the answer into a table (cache). The next time any recursive
branch requests `fib(3)`, return the cached value in $O(1)$ time instead of re-evaluating its
entire subtree.

This is called **top-down Dynamic Programming** or **memoization**:
- "Top-down" because we start at the original problem target $n$ and recursively break it down.
- "Memoization" from Latin *memorandum* ("to be remembered").

### Pruning the recursion tree

```
                       fib(5)
                    /          \
             fib(4)              fib(3) --> [CACHE HIT! Returns in O(1)]
            /      \
        fib(3)    fib(2) --> [CACHE HIT! Returns in O(1)]
       /     \
    fib(2) fib(1)
    /    \
  fib(1) fib(0)
```

The entire right subtree of `fib(5)` collapses into an immediate $O(1)$ cache lookup. Every subproblem
is evaluated recursively exactly once.

### Implementation

- Python: [`memoized_solution.py`](../problem_solutions/fibonacci-number/memoized_solution.py)
- C++: [`memoized_solution.cpp`](../problem_solutions/fibonacci-number/memoized_solution.cpp)

<details>
<summary>Starting snippet (Python)</summary>

```python
class Solution:
    def fib(self, n: int) -> int:
        memo: dict[int, int] = {}

        def helper(k: int) -> int:
            if k == 0:
                return 0
            if k == 1:
                return 1
            if k in memo:
                return memo[k]

            memo[k] = helper(k - 1) + helper(k - 2)
            return memo[k]

        return helper(n)


if __name__ == "__main__":
    sol = Solution()
    print(sol.fib(7))  # 13
```

</details>

<details>
<summary>Starting snippet (C++)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    vector<int> memo;

    int helper(int k) {
        if (k == 0) return 0;
        if (k == 1) return 1;
        if (memo[k] != -1) return memo[k];

        memo[k] = helper(k - 1) + helper(k - 2);
        return memo[k];
    }

public:
    int fib(int n) {
        memo.assign(n + 2, -1);
        return helper(n);
    }
};

int main() {
    Solution sol;
    cout << sol.fib(7) << "\n";  // 13
    return 0;
}
```

</details>

<details>
<summary>Correctness</summary>

**Claim:** For every non-negative integer $k$, calling `helper(k)` returns $F(k)$ and ensures
`memo[k] = F(k)`.

**Base case:** $k = 0$ returns 0, and $k = 1$ returns 1. Both match the math definition $F(0) = 0$ and $F(1) = 1$.

**Assume:** For all $m < k$, `helper(m)` correctly returns $F(m)$.

**Show:** For $k \ge 2$:
- If `k in memo` (`memo[k] != -1`), the value was recorded by a prior call that computed $F(k)$, so
  returning `memo[k]` is correct.
- If `k` is not yet in `memo`: the algorithm evaluates `helper(k - 1) + helper(k - 2)`. By **Assume**,
  these evaluate to $F(k - 1)$ and $F(k - 2)$ respectively. Their sum is $F(k - 1) + F(k - 2) = F(k)$.
  The algorithm assigns `memo[k] = F(k)` and returns it.

In both branches, `helper(k)` returns $F(k)$. By mathematical induction, the initial call
`helper(n)` returns $F(n)$.

</details>

<details>
<summary>Complexity</summary>

**Time:** Exactly $n + 1$ unique subproblems ($k = 0, 1, \dots, n$).
- Uncached calls: each subproblem is computed from scratch exactly once, doing $O(1)$ work (one addition and one cache write).
- Cached calls: subsequent requests for an already computed subproblem return in $O(1)$ lookup time.
- Total time: $(n + 1) \times O(1) =$ **$O(n)$**.

**Space:**
- Cache storage: `memo` holds $n + 1$ integers, taking $O(n)$ memory.
- Call stack: the recursion depth reaches at most $n$ frames.
- Total auxiliary space: **$O(n)$**.

</details>

</details>

<details>
<summary>5. Bottom-up Dynamic Programming: Tabulation</summary>

### Inverting the control flow

Memoization is demand-driven: we ask for $F(n)$, which asks for $F(n - 1)$ and $F(n - 2)$, descending
to the base cases.

Notice the dependency direction: $F(i)$ depends strictly on smaller indices ($i - 1$ and $i - 2$).
Instead of starting at $n$ and recursing downward, we can invert the flow:
1. Start directly at the base cases: $F(0) = 0$ and $F(1) = 1$.
2. Iteratively compute $F(2), F(3), \dots, F(n)$ in increasing order using a loop.
3. Store the values in an array (`dp` table).

This is called **bottom-up Dynamic Programming** or **tabulation**.

### Visualizing the table fill

```
Index i:    0    1    2    3    4    5   ...   n
dp[i]:     [0]  [1]  [1]  [2]  [3]  [5]  ...  F(n)
            ^    ^    ^
            Base |    dp[2] = dp[1] + dp[0]
            cases
```

- Python: [`iterative_solution.py`](../problem_solutions/fibonacci-number/iterative_solution.py)
- C++: [`iterative_solution.cpp`](../problem_solutions/fibonacci-number/iterative_solution.cpp)

<details>
<summary>Starting snippet (Python)</summary>

```python
class Solution:
    def fib(self, n: int) -> int:
        if n == 0:
            return 0
        if n == 1:
            return 1

        dp = [0] * (n + 1)
        dp[0] = 0
        dp[1] = 1

        for i in range(2, n + 1):
            dp[i] = dp[i - 1] + dp[i - 2]

        return dp[n]


if __name__ == "__main__":
    sol = Solution()
    print(sol.fib(7))  # 13
```

</details>

<details>
<summary>Starting snippet (C++)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int fib(int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;

        vector<int> dp(n + 1, 0);
        dp[0] = 0;
        dp[1] = 1;

        for (int i = 2; i <= n; ++i) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        return dp[n];
    }
};

int main() {
    Solution sol;
    cout << sol.fib(7) << "\n";  // 13
    return 0;
}
```

</details>

<details>
<summary>Correctness (Loop Invariant)</summary>

**Claim:** At the start of iteration `i` (for $2 \le i \le n + 1$), the array slice `dp[0:i]` contains
the exact Fibonacci numbers $F(0), F(1), \dots, F(i - 1)$.

**Initialization:** Prior to the first iteration ($i = 2$), `dp[0] = 0 = F(0)` and `dp[1] = 1 = F(1)`.
The slice `dp[0:2]` matches $F(0)$ and $F(1)$. The invariant holds.

**Maintenance:** Assume the invariant holds at the start of iteration $i$. The loop executes:
`dp[i] = dp[i - 1] + dp[i - 2]`. By the invariant, `dp[i - 1] = F(i - 1)` and `dp[i - 2] = F(i - 2)`.
By definition of the Fibonacci recurrence, $F(i) = F(i - 1) + F(i - 2)$. Thus, `dp[i] = F(i)`.
When the loop advances to $i + 1$, the slice `dp[0:i+1]` contains $F(0), \dots, F(i)$. The invariant
is maintained.

**Termination:** The loop terminates when $i = n + 1$. By the invariant, `dp[0:n+1]` contains
$F(0), \dots, F(n)$. Specifically, `dp[n] = F(n)`. The function returns `dp[n]`, which is correct.

</details>

<details>
<summary>Complexity</summary>

**Time:** The loop runs from $i = 2$ to $n$ ($n - 1$ iterations). Each iteration performs one addition
and one array assignment ($O(1)$ work). Total time is **$O(n)$**.

**Space:** The array `dp` has size $n + 1$, requiring **$O(n)$** auxiliary space. Crucially, there is
no recursion, so the call stack uses $O(1)$ extra space.

</details>

### State compression: O(1) space optimization

Look closely at the transition in iteration $i$:
`dp[i] = dp[i - 1] + dp[i - 2]`

To compute the current value, do we need the entire history `dp[0], dp[1], ..., dp[i - 3]`?
No. Once `dp[i - 1]` and `dp[i - 2]` are known, all earlier values are never referenced again.
We can replace the entire array with just two variables:

```python
def fib(n: int) -> int:
    if n == 0:
        return 0
    if n == 1:
        return 1

    prev2, prev1 = 0, 1
    for _ in range(2, n + 1):
        curr = prev1 + prev2
        prev2 = prev1
        prev1 = curr

    return prev1
```

**Complexity of space-optimized tabulation:**
- **Time:** $O(n)$ (same single loop of $n - 1$ steps).
- **Space:** **$O(1)$** auxiliary space (only 3 integer variables: `prev2`, `prev1`, `curr`).

</details>

<details>
<summary>6. Climbing Stairs: Pull DP vs Push DP</summary>

[LeetCode 70, Climbing Stairs](https://leetcode.com/problems/climbing-stairs/):
You are climbing a staircase with `n` steps. Each time you can either climb 1 or 2 steps.
In how many distinct ways can you climb to the top?

- Python solutions: [`problem_solutions/climbing-stairs/solution.py`](../problem_solutions/climbing-stairs/solution.py), [`pull_solution.py`](../problem_solutions/climbing-stairs/pull_solution.py), [`push_solution.py`](../problem_solutions/climbing-stairs/push_solution.py)
- C++ solutions: [`problem_solutions/climbing-stairs/solution.cpp`](../problem_solutions/climbing-stairs/solution.cpp), [`pull_solution.cpp`](../problem_solutions/climbing-stairs/pull_solution.cpp), [`push_solution.cpp`](../problem_solutions/climbing-stairs/push_solution.cpp)
- Writeup: [`problem_solutions/climbing-stairs/README.md`](../problem_solutions/climbing-stairs/README.md)

### Mathematical formulation

To land on step `i`, your very last jump must have been either:
- A 1-step jump from step `i - 1`, or
- A 2-step jump from step `i - 2`.

This yields the familiar recurrence:
`ways(i) = ways(i - 1) + ways(i - 2)`

With base cases:
- `ways(0) = 1`: Exactly 1 way to stand at ground level (do nothing).
- `ways(1) = 1`: Exactly 1 way to reach step 1 (single 1-step jump).

While this recurrence is mathematically isomorphic to Fibonacci, writing iterative DP loops
reveals two fundamentally different ways to process state transitions: **Pull DP** and **Push DP**.

### Pull DP (Lookback / Gathering)

In **Pull DP**, you stand at destination state `i` and look backward into the past:
*"Where could I have arrived from to land on step `i`?"*

You pull or accumulate values from already-computed earlier states into the current state:

```python
class Solution:
    def climbStairs(self, n: int) -> int:
        mem = [0 for i in range(n + 2)]
        mem[0] = 1
        mem[1] = 1
        for i in range(2, n + 1):
            mem[i] = mem[i - 1] + mem[i - 2]

        return mem[n]
```

- **Loop range:** `i` advances from `2` up to `n`.
- **Precondition:** `mem[i - 1]` and `mem[i - 2]` must already be computed before calculating `mem[i]`.
- **Mental model:** Destination-oriented. We aggregate incoming transitions (`mem[i] = incoming_1 + incoming_2`).

### Push DP (Forward Dispatching / Relaxation)

In **Push DP**, you stand at current state `i` and look forward into the future:
*"Where can I go from step `i`?"*

Once state `i` is resolved, you push or distribute its count forward to all valid reachable states:

```python
class Solution:
    def climbStairs(self, n: int) -> int:
        mem = [0 for i in range(n + 2)]
        mem[0] = 1

        for i in range(0, n):
            mem[i + 1] += mem[i]
            mem[i + 2] += mem[i]

        return mem[n]
```

- **Loop range:** `i` advances from `0` up to `n - 1`.
- **Precondition:** `mem[i]` must be fully settled and finalized before we loop through it to push its value forward.
- **Mental model:** Source-oriented. We propagate outgoing transitions from the current state to its successors (`mem[next] += current`).
- **Array sizing:** Sized to `n + 2` because when `i = n - 1`, pushing two steps forward targets index `(n - 1) + 2 = n + 1`. An array of size `n + 1` would cause an out-of-bounds error.

### Pull DP vs Push DP comparison

| Dimension | Pull DP (Gathering) | Push DP (Dispatching) |
|---|---|---|
| Core question | "Where did I come from?" | "Where can I go from here?" |
| State role | Destination: `mem[i]` receives inputs | Source: `mem[i]` distributes outputs |
| Transition style | `mem[i] = mem[i - 1] + mem[i - 2]` | `mem[i + 1] += mem[i]`; `mem[i + 2] += mem[i]` |
| Loop bounds | `i` from `2` to `n` | `i` from `0` to `n - 1` |
| Base cases | `mem[0] = 1`, `mem[1] = 1` | `mem[0] = 1` |
| When to prefer | When incoming edges/predecessors are easy to list | When outgoing edges/successors are easy to generate, or in shortest-path DP (Dijkstra/Bellman-Ford) |

</details>

<details>
<summary>7. Comparing the complexities and approaches</summary>

### Side-by-side comparison

| Approach | Time | Space | Call stack depth | Order of evaluation | Overhead and limits |
|---|---|---|---|---|---|
| **Naive Recursion** | $O(2^n)$ | $O(n)$ | $n$ | Top-down (all paths) | Recomputes identical subtrees exponentially; unusable for $n > 40$ |
| **Memoization (Top-Down DP)** | $O(n)$ | $O(n)$ | $n$ | Top-down (on-demand) | Function call overhead; risk of recursion limit / stack overflow for large $n$ |
| **Tabulation (Bottom-Up DP)** | $O(n)$ | $O(n)$ | $0$ (iterative) | Bottom-up (topological order) | Allocates table of size $n$; sequential array access gives great cache locality |
| **Space-Optimized Tabulation** | $O(n)$ | $O(1)$ | $0$ (iterative) | Bottom-up (sliding window) | Minimal memory footprint; cannot reconstruct full history if requested |

### When to prefer Top-Down (Memoization) vs Bottom-Up (Tabulation)

1. **Subproblem sparsity:**
   - If the recurrence only visits a small fraction of all possible states in the state space,
     **memoization** only computes states that are actually reached.
   - Tabulation typically fills the table uniformly, potentially computing states that are never
     needed.
2. **Call stack limits and overhead:**
   - In Python, recursion depth is bounded (default limit 1,000). A call to `fib(2000)` with
     memoization triggers `RecursionError: maximum recursion depth exceeded`.
   - In C++, deep recursion can exhaust stack memory and segfault.
   - **Tabulation** uses iterative loops, completely avoiding stack overflow risks.
3. **Cache locality:**
   - Tabulation iterates through contiguous memory (`vector` or list), maximizing CPU L1/L2 cache
     hits. Memoization jumps across recursive call stack frames and hash map buckets.
4. **Reconstructing the solution path:**
   - If a problem asks not just for the optimal value, but also for the exact sequence of choices
     (e.g. printing the chosen items in Knapsack), retaining the full `dp` table or decision
     pointers is required. State compression to $O(1)$ discards history and prevents path
     reconstruction.

</details>

<details>
<summary>8. Recap</summary>

- **Backtracking vs Dynamic Programming:**
  - Backtracking explores combinatorial trees where every leaf is a distinct configuration to report
    ($O(n \cdot 2^n)$ or $O(n \cdot n!)$).
  - Dynamic Programming applies when subproblems overlap and have optimal substructure, caching or
    tabulating solutions to collapse exponential trees into polynomial time.
- **The DP Progression:**
  1. *Mathematical recurrence:* Formulate state and base cases ($F(n) = F(n-1) + F(n-2)$).
  2. *Naive recursion:* $O(2^n)$ time due to repeated subproblem evaluation.
  3. *Top-Down DP (Memoization):* Cache subproblem answers on first encounter; drops time to $O(n)$
     with $O(n)$ stack and memory.
  4. *Bottom-Up DP (Tabulation):* Fill table iteratively in dependency order; drops call stack to $O(1)$,
     keeping $O(n)$ table.
  5. *Pull vs Push Tabulation:* Pull gathers backward from predecessors (`mem[i] = mem[i-1] + mem[i-2]`);
     Push distributes forward to successors (`mem[i+1] += mem[i]`, `mem[i+2] += mem[i]`).
  6. *State Compression:* When transitions only look back a constant number of steps, reduce table to
     $O(1)$ auxiliary variables.
- **Looking ahead:** Next session we apply this exact progression to problems with choices and
  optimization: [LeetCode 322, Coin Change](https://leetcode.com/problems/coin-change/).

</details>

<details>
<summary>Hints</summary>

1. **Memoization table initialization:**
   - In Python, a dictionary `memo = {}` allows checking `if k in memo:` in $O(1)$ average time.
   - In C++, a `vector<int> memo(n + 1, -1)` provides $O(1)$ direct indexing, using `-1` as a sentinel
     meaning "not yet calculated" (valid since Fibonacci values are non-negative).
2. **Base case handling:**
   - When tabulating, handle $n = 0$ and $n = 1$ before allocating arrays of size $n + 1$ to avoid
     out-of-bounds indexing when $n = 0$.
3. **Space optimization invariant:**
   - When updating rolling variables (`prev2 = prev1; prev1 = curr;`), be careful with the update
     order so that `prev2` receives the old `prev1` before `prev1` is overwritten by `curr`.

</details>

<details>
<summary>References</summary>

- LeetCode 509: [Fibonacci Number](https://leetcode.com/problems/fibonacci-number/)
- LeetCode 70: [Climbing Stairs](https://leetcode.com/problems/climbing-stairs/) (identical recurrence structure)
- LeetCode 1137: [N-th Tribonacci Number](https://leetcode.com/problems/n-th-tribonacci-number/) (three-term recurrence)
- Cormen et al., *Introduction to Algorithms*, Chapter 15 "Dynamic Programming" (pp. 359-390)

</details>
