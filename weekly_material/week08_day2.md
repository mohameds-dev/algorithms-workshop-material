# Week 08, Day 2 (October 15, 2026)

## Today

Today's session is split into two parts:
1. **Part 1: Dr. Leiss Material Review:** In-class review of old course material and exam concepts from Dr. Leiss's COSC 3320 section (not hosted in this repo).
2. **Part 2: Rollover Problems from Day 1:**
   - **Canonical Signatures:** [Group Anagrams](https://leetcode.com/problems/group-anagrams/) ([LeetCode 49](https://leetcode.com/problems/group-anagrams/)).
   - **2D Grid Dynamic Programming:** [Unique Paths](https://leetcode.com/problems/unique-paths/) ([LeetCode 62](https://leetcode.com/problems/unique-paths/)) and [Unique Paths II](https://leetcode.com/problems/unique-paths-ii/) ([LeetCode 63](https://leetcode.com/problems/unique-paths-ii/)).

---

<details>
<summary>Part 1: Dr. Leiss Material Review</summary>

Review of Dr. Leiss's COSC 3320 course concepts and past exam problems.

The primary handout and worksheet materials for this section are distributed directly in class and are not hosted in this repository.

Topics and key focus areas for the review:
- Recurrence relations and asymptotic bounding under Leiss analysis conventions.
- Graph models and constraints on recursive structures (such as Towers of Hanoi variants on arbitrary pole graphs).
- Algorithmic problem formulation and invariant analysis.

Students should reference their in-class handouts and lecture notes for the problem statements and discussion points.

</details>

---

<details>
<summary>Part 2, Problem 1: Canonical Signatures: Group Anagrams (LeetCode 49)</summary>

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
<summary>Part 2, Problem 2: 2D Grid Dynamic Programming: Unique Paths (LeetCode 62)</summary>

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
<summary>Part 2, Problem 3: Grid DP with Obstacles: Unique Paths II (LeetCode 63)</summary>

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
