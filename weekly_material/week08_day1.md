# Week 08, Day 1 (October 13, 2026)

## Today

Today we conduct an intensive problem-solving session focusing on three core problem categories:
1. **String, Array, and Hash Map Fundamentals:** Frequency counting, invariant checking, and canonical grouping via [Valid Anagram](https://leetcode.com/problems/valid-anagram/) ([LeetCode 242](https://leetcode.com/problems/valid-anagram/)) and [Group Anagrams](https://leetcode.com/problems/group-anagrams/) ([LeetCode 49](https://leetcode.com/problems/group-anagrams/)).
2. **Backtracking with Invariant Pruning:** Decision trees with validity constraints via [Generate Parentheses](https://leetcode.com/problems/generate-parentheses/) ([LeetCode 22](https://leetcode.com/problems/generate-parentheses/)).
3. **2D Grid Dynamic Programming:** Coordinate navigation, obstacle avoidance, and 1D space optimization via [Unique Paths](https://leetcode.com/problems/unique-paths/) ([LeetCode 62](https://leetcode.com/problems/unique-paths/)) and [Unique Paths II](https://leetcode.com/problems/unique-paths-ii/) ([LeetCode 63](https://leetcode.com/problems/unique-paths-ii/)).

---

<details>
<summary>1. Strings, Arrays, and Hash Tables: Valid Anagram (LeetCode 242)</summary>

### Problem

Given two strings `s` and `t`, return `true` if `t` is an anagram of `s`, and `false` otherwise. An anagram is formed by rearranging the letters of a word, using all original letters exactly once.

[LeetCode 242: Valid Anagram](https://leetcode.com/problems/valid-anagram/)

### By-Hand Tracing: Array Frequency Counters

Trace two strings on paper: `s = "anagram"`, `t = "nagaram"`.

1. Check lengths: `len(s) == len(t) == 7`. If lengths differ, return `false` immediately.
2. Initialize an integer array of size 26 with all zeros, indexed by `ord(c) - ord('a')`.
3. Process characters in lockstep:
   - For `s`: increment `counts[ord(c) - ord('a')] += 1`.
   - For `t`: decrement `counts[ord(c) - ord('a')] -= 1`.
4. Inspect the table at termination:
   - `a`: $+3 - 3 = 0$
   - `g`: $+1 - 1 = 0$
   - `m`: $+1 - 1 = 0$
   - `n`: $+1 - 1 = 0$
   - `r`: $+1 - 1 = 0$
   All 26 buckets are 0, so the result is `true`.

### Starter Code

```python
class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        # Your code here
        pass
```

### Hints

<details>
<summary>Hints</summary>

1. If `len(s) != len(t)`, can `t` possibly be an anagram of `s`?
2. Sorting both strings takes $O(n \log n)$ time. Can you do it in $O(n)$ time using character frequency counts?
3. With lowercase English letters, a fixed-size array of 26 integers provides $O(1)$ auxiliary memory.
4. Increment counts for characters in `s` and decrement for characters in `t`. Check if every count equals 0 at the end.

</details>

### Correctness

- **Claim:** The frequency counter contains all zeros if and only if `s` and `t` have identical character multiset distributions.
- **Initialization:** An array of 26 zeros correctly represents empty strings.
- **Maintenance:** For each index $i$, adding 1 for `s[i]` and subtracting 1 for `t[i]` maintains the net difference of occurrences for each character.
- **Termination:** At index $n$, `counts[c] == 0` for all characters $c$ if and only if the total count of $c$ in `s` equals its total count in `t`.

### Code Links

- [Problem Description and Complexity Analysis](../problem_solutions/valid-anagram/README.md)
- [Python Solution](../problem_solutions/valid-anagram/solution.py)
- [C++ Solution](../problem_solutions/valid-anagram/solution.cpp)

</details>

---

<details>
<summary>2. Canonical Signatures: Group Anagrams (LeetCode 49)</summary>

### Problem

Given an array of strings `strs`, group the anagrams together. You can return the answer in any order.

[LeetCode 49: Group Anagrams](https://leetcode.com/problems/group-anagrams/)

### By-Hand Tracing: Canonical Signature Map

Consider `strs = ["eat", "tea", "tan", "ate", "nat", "bat"]`.

To group anagrams into common buckets, every anagram must map to a unique canonical signature:
- Approach 1 (Sorted String Key):
  - `"eat"`, `"tea"`, `"ate"` sorted become `"aet"`.
  - `"tan"`, `"nat"` sorted become `"ant"`.
  - `"bat"` sorted becomes `"abt"`.
- Approach 2 (Character Count Tuple Key):
  - `"eat"` count signature: `(1, 0, ..., 1, ..., 1, ...)` (one 'a', one 'e', one 't').
  - Both `"tea"` and `"ate"` generate this exact tuple.

Hash table mapping:
```text
"aet" -> ["eat", "tea", "ate"]
"ant" -> ["tan", "nat"]
"abt" -> ["bat"]
```
Output the values of the hash map as a list of lists.

### Starter Code

```python
class Solution:
    def groupAnagrams(self, strs: list[str]) -> list[list[str]]:
        # Your code here
        pass
```

### Hints

<details>
<summary>Hints</summary>

1. Two strings belong to the same group if and only if they share an identical character count.
2. In Python, lists cannot be dictionary keys because they are mutable, but tuples can.
3. Count frequencies into an array of size 26 and convert to `tuple(counts)` for an $O(n \cdot k)$ runtime, where $k$ is word length.
4. In C++, sorting each word to create a string key is simple and fast, running in $O(n \cdot k \log k)$ time.

</details>

### Correctness

- **Claim:** All strings assigned to the same hash table bucket are mutual anagrams, and no two anagrams are assigned to different buckets.
- **Signature Invariance:** Any two strings $s_1$ and $s_2$ are anagrams if and only if their character multiset counts are identical. Sorting characters or computing character counts yields an identical key for $s_1$ and $s_2$.
- **Mapping:** Inserting each string into `groups[signature]` guarantees that every bucket contains precisely the anagrams for that specific signature. Collecting all bucket values produces a valid partition.

### Code Links

- [Problem Description and Complexity Analysis](../problem_solutions/group-anagrams/README.md)
- [Python Solution](../problem_solutions/group-anagrams/solution.py)
- [C++ Solution](../problem_solutions/group-anagrams/solution.cpp)

</details>

---

<details>
<summary>3. Backtracking with Pruning: Generate Parentheses (LeetCode 22)</summary>

### Problem

Given `n` pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

[LeetCode 22: Generate Parentheses](https://leetcode.com/problems/generate-parentheses/)

### By-Hand Tracing: Recursion Tree for n = 2

A brute force approach generates all $2^{2n} = 2^4 = 16$ possible strings of length 4, then discards invalid ones.
With backtracking, we track `open_count` and `close_count` and only branch into valid choices:
1. We can append `'('` only if `open_count < n`.
2. We can append `')'` only if `close_count < open_count`.

Tracing tree on paper for $n = 2$:
```text
                     "" (open=0, close=0)
                              |
                            "(" (1, 0)
                           /          \
                     "((" (2, 0)     "()" (1, 1)
                          |               |
                    "(()" (2, 1)     "()(" (2, 1)
                          |               |
                   "(())" (2, 2)    "()()" (2, 2)
```

Notice that starting with `")"` is pruned immediately because `close_count (0) < open_count (0)` is false. Every leaf reached in this tree is guaranteed to be a valid combination.

### Starter Code

```python
class Solution:
    def generateParenthesis(self, n: int) -> list[str]:
        # Your code here
        pass
```

### Hints

<details>
<summary>Hints</summary>

1. What condition allows placing an open parenthesis `'('`? You have up to `n` open parentheses available: `open_count < n`.
2. What condition allows placing a close parenthesis `')'`? You can only close a parenthesis that has already been opened: `close_count < open_count`.
3. What is the base case? When the length of the current string reaches `2 * n`.
4. Remember the backtracking pattern: choose, recurse, unchoose (pop).

</details>

### Correctness

- **Claim:** Every string added to `result` is well-formed, and all well-formed strings of length $2n$ are generated exactly once.
- **Base case:** When `len(current) == 2 * n`, because `open_count <= n` and `close_count <= open_count`, we must have `open_count == close_count == n`. Since every prefix satisfied `close_count <= open_count`, the sequence is balanced.
- **Assume:** At depth $k < 2n$, `current` is a valid prefix with `close_count <= open_count <= n`.
- **Show:** The algorithm branches on all possible valid next characters:
  - If `open_count < n`, placing `'('` produces a valid prefix with `open_count + 1`.
  - If `close_count < open_count`, placing `')'` produces a valid prefix with `close_count + 1`.
  Every valid branch is explored and no invalid sequences are visited.

### Code Links

- [Problem Description and Complexity Analysis](../problem_solutions/generate-parentheses/README.md)
- [Python Solution](../problem_solutions/generate-parentheses/solution.py)
- [C++ Solution](../problem_solutions/generate-parentheses/solution.cpp)

</details>

---

<details>
<summary>4. 2D Grid Dynamic Programming: Unique Paths (LeetCode 62)</summary>

### Problem

There is a robot on an $m \times n$ grid. The robot is initially located at the top-left corner `(0, 0)` and wants to reach the bottom-right corner `(m - 1, n - 1)`. The robot can only move either down or right at any point in time. Given $m$ and $n$, return the number of possible unique paths.

[LeetCode 62: Unique Paths](https://leetcode.com/problems/unique-paths/)

### By-Hand Tracing: 3 x 3 Grid

Draw a $3 \times 3$ grid on paper.
- The top-left cell starts with 1 path.
- The entire first row and first column have only 1 way to be reached:
```text
Row 0:  1   1   1
Row 1:  1   ?   ?
Row 2:  1   ?   ?
```
- For any cell `(r, c)`: `dp[r][c] = dp[r - 1][c] + dp[r][c - 1]`.
- Fill cell `(1, 1)`: $1 + 1 = 2$.
- Fill cell `(1, 2)`: $2 + 1 = 3$.
- Fill cell `(2, 1)`: $1 + 2 = 3$.
- Fill cell `(2, 2)`: $3 + 3 = 6$.
Final table:
```text
Row 0:  1   1   1
Row 1:  1   2   3
Row 2:  1   3   6
```

### Space Optimization: Shrinking from 2D to 1D

Notice that `dp[r][c]` only needs:
1. `dp[r - 1][c]` (the value from the previous row at the same column).
2. `dp[r][c - 1]` (the newly calculated value to the left in the current row).

We can maintain a single 1D array `dp` of size $n$, initialized to all 1s.
For each row from 1 to $m - 1$:
```python
for col in range(1, n):
    dp[col] += dp[col - 1]
```
Space drops from $O(m \cdot n)$ to $O(n)$.

### Starter Code

```python
class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        # Your code here
        pass
```

### Hints

<details>
<summary>Hints</summary>

1. What moves can the robot make? Only down or right.
2. Where could the robot have come from to arrive at cell `(r, c)`? From `(r - 1, c)` or `(r, c - 1)`.
3. Base cases: what are the values along `r = 0` and `c = 0`?
4. Can you update a single 1D array in place as you sweep through rows?

</details>

### Correctness

- **Claim:** At the completion of outer loop iteration `row`, `dp[col]` stores the number of unique paths from `(0, 0)` to `(row, col)`.
- **Initialization:** For `row = 0`, `dp[col] = 1` for all `col`, matching the single horizontal route along the first row.
- **Maintenance:** In iteration `row`, before updating `dp[col]`, its value represents paths from above (`row - 1, col`). Adding `dp[col - 1]` (paths from the left cell in `row`) accounts for all disjoint arrival paths.
- **Termination:** When loops finish, `dp[n - 1]` holds the paths to `(m - 1, n - 1)`.

### Code Links

- [Problem Description and Complexity Analysis](../problem_solutions/unique-paths/README.md)
- [Python Solution](../problem_solutions/unique-paths/solution.py)
- [C++ Solution](../problem_solutions/unique-paths/solution.cpp)

</details>

---

<details>
<summary>5. Grid DP with Obstacles: Unique Paths II (LeetCode 63)</summary>

### Problem

You are given an $m \times n$ integer array `obstacleGrid`. There is a robot initially located at `(0, 0)` trying to reach `(m - 1, n - 1)`. The robot can only move down or right. An obstacle is marked as `1` and empty space is marked as `0`. A path cannot pass through any square with an obstacle. Return the number of unique paths.

[LeetCode 63: Unique Paths II](https://leetcode.com/problems/unique-paths-ii/)

### By-Hand Tracing: Obstacle Grid

Consider the grid with an obstacle at center `(1, 1)`:
```text
Grid:
0   0   0
0   1   0
0   0   0
```

Trace step-by-step:
1. If cell `(r, c)` is an obstacle, no path can enter or pass through it: `dp[r][c] = 0`.
2. Otherwise: `dp[r][c] = dp[r - 1][c] + dp[r][c - 1]`.

Fill row-by-row on paper:
```text
Row 0:  1   1   1
Row 1:  1   0   1   (obstacle at (1, 1) zeros the cell; (1, 2) = dp[0][2] + dp[1][1] = 1 + 0 = 1)
Row 2:  1   1   2   ((2, 1) = dp[1][1] + dp[2][0] = 0 + 1 = 1; (2, 2) = dp[1][2] + dp[2][1] = 1 + 1 = 2)
```
Output: 2 unique paths.

### Starter Code

```python
class Solution:
    def uniquePathsWithObstacles(self, obstacleGrid: list[list[int]]) -> int:
        # Your code here
        pass
```

### Hints

<details>
<summary>Hints</summary>

1. What if `obstacleGrid[0][0] == 1` or `obstacleGrid[m - 1][n - 1] == 1`? Return 0 immediately.
2. If cell `(r, c)` contains an obstacle, `dp[r][c] = 0`.
3. In a 1D DP array of size $n$, whenever `obstacleGrid[row][col] == 1`, set `dp[col] = 0`.
4. Otherwise, if `col > 0`, perform `dp[col] += dp[col - 1]`.

</details>

### Correctness

- **Claim:** At the completion of outer loop iteration `row`, `dp[col]` stores the number of obstacle-free paths from `(0, 0)` to `(row, col)`.
- **Initialization:** `dp` starts with size $n$, all 0s except `dp[0] = 1`. If `(0, 0)` is an obstacle, `dp[0]` is zeroed out immediately during the first step.
- **Maintenance:** If `obstacleGrid[row][col] == 1`, `dp[col] = 0` correctly reflects that zero paths can pass through an obstacle. If clear, adding `dp[col - 1]` to `dp[col]` sums paths arriving from top and left.
- **Termination:** `dp[n - 1]` contains the total paths reaching `(m - 1, n - 1)`.

### Code Links

- [Problem Description and Complexity Analysis](../problem_solutions/unique-paths-ii/README.md)
- [Python Solution](../problem_solutions/unique-paths-ii/solution.py)
- [C++ Solution](../problem_solutions/unique-paths-ii/solution.cpp)

</details>
