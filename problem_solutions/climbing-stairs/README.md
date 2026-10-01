# Climbing Stairs

LeetCode 70: https://leetcode.com/problems/climbing-stairs/

- Difficulty: Easy
- Topics: Dynamic Programming, Math, Memoization
- Discussed: [Week 6, Day 2](../../weekly_material/week06_day2.md)

## Summary

You are climbing a staircase. It takes `n` steps to reach the top. Each time you can either
climb 1 or 2 steps. In how many distinct ways can you climb to the top?

## Hints

1. To reach step `n`, your very last jump must have been either a 1-step jump from step `n - 1`
   or a 2-step jump from step `n - 2`.
2. Notice how this recurrence matches the Fibonacci sequence, but with shifted base cases:
   `ways(0) = 1` (1 way to stay at the ground), `ways(1) = 1` (one 1-step jump), `ways(2) = 2`.
3. In Dynamic Programming, transitions can be written in two equivalent directions:
   - **Pull DP:** At step `i`, look backward and gather values from previous states.
   - **Push DP:** At step `i`, look forward and distribute ways to reachable future states.

## Solution

Two distinct tabular perspectives are provided:

- **Pull DP (Lookback / Gathering):**
  [`pull_solution.py`](pull_solution.py) / [`pull_solution.cpp`](pull_solution.cpp)
  Focuses on the destination state: "Where could I have come from to land on step `i`?"
  Incoming transitions come from step `i - 1` (a 1-step jump) and step `i - 2` (a 2-step jump).
  ```python
  mem[i] = mem[i - 1] + mem[i - 2]
  ```

- **Push DP (Forward Dispatching / Forward Relaxation):**
  [`push_solution.py`](push_solution.py) / [`push_solution.cpp`](push_solution.cpp)
  Focuses on the source state: "Where can I go from step `i`?"
  From step `i`, we can take 1 step to land on `i + 1` or 2 steps to land on `i + 2`.
  We push the ways to reach step `i` forward to both target states:
  ```python
  mem[i + 1] += mem[i]
  mem[i + 2] += mem[i]
  ```

- **Combined Reference:**
  [`solution.py`](solution.py) / [`solution.cpp`](solution.cpp) exposes both methods.

## Pull vs Push Comparison

| Concept | Pull DP (Gathering) | Push DP (Dispatching) |
|---|---|---|
| Question asked | "Where did I come from?" | "Where can I go from here?" |
| State role | `mem[i]` is updated by pulling from earlier states | `mem[i]` is already finalized; pushes to future states |
| Transition | `mem[i] = mem[i - 1] + mem[i - 2]` | `mem[i + 1] += mem[i]`; `mem[i + 2] += mem[i]` |
| Loop range | `i` runs from `2` to `n` | `i` runs from `0` to `n - 1` |
| Base cases | `mem[0] = 1`, `mem[1] = 1` | `mem[0] = 1` |
| Array sizing | Size `n + 2` handles small `n` without bounds checks | Size `n + 2` prevents out-of-bounds on `i + 2` when `i = n - 1` |

## Complexity

- **Time:** $O(n)$. Both formulations use a single loop with $O(1)$ operations per step.
- **Space:** $O(n)$ for the `mem` array of size $n + 2$. Can be reduced to $O(1)$ auxiliary space
  by keeping only the last two values in rolling variables.
