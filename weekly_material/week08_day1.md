# Week 08, Day 1 (October 13, 2026)

## Today

Today we conduct an intensive problem-solving session focusing on two core problem categories:
1. **String, Array, and Hash Map Fundamentals:** Frequency counting and invariant checking via [Valid Anagram](https://leetcode.com/problems/valid-anagram/) ([LeetCode 242](https://leetcode.com/problems/valid-anagram/)).
2. **Backtracking with Invariant Pruning:** Decision trees with validity constraints via [Generate Parentheses](https://leetcode.com/problems/generate-parentheses/) ([LeetCode 22](https://leetcode.com/problems/generate-parentheses/)).

> [!NOTE]
> Group Anagrams (LeetCode 49), Unique Paths (LeetCode 62), and Unique Paths II (LeetCode 63) were moved to [Week 08, Day 2](week08_day2.md).

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
<summary>2. Backtracking with Pruning: Generate Parentheses (LeetCode 22)</summary>

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
