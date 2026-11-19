# Week 01, Day 2 (August 27, 2026)

## Today

Today we'll explore the topic of [recursion](https://en.wikipedia.org/wiki/Recursion_(computer_science)),
solve a couple of easy problems, and touch the surface of divide and conquer with a fun problem,
going from there.

Feel free to use any IDE of your choice, and any language you're comfortable with.

<details>
<summary>1. Factorial</summary>

Defined purely in math terms:

```
0! = 1
n! = n × (n - 1)!,  for n > 0
```

Examples: `5! = 5 × 4 × 3 × 2 × 1 = 120`, `3! = 3 × 2 × 1 = 6`, `0! = 1`.

**Your turn, iteratively:** write a function `factorial(n)` that computes n! using a loop.

<details>
<summary>Iterative solution</summary>

```python
def factorial(n):
    result = 1
    for i in range(2, n + 1):
        result *= i
    return result
```

</details>

**Your turn, recursively:** now write the same function using the definition directly, as a
function that calls itself.

<details>
<summary>Recursive solution</summary>

```python
def factorial(n):
    if n == 0:
        return 1
    return n * factorial(n - 1)
```

</details>

</details>

<details>
<summary>2. Set up LeetCode</summary>

- Sign up, or log in if you already have an account: https://leetcode.com
- Open any problem and submit a solution, just to confirm everything works.

</details>

<details>
<summary>3. Fibonacci</summary>

LeetCode 509, Fibonacci Number: https://leetcode.com/problems/fibonacci-number/

Defined purely in math terms:

```
F(0) = 0
F(1) = 1
F(n) = F(n - 1) + F(n - 2),  for n > 1
```

**Try it yourself:** write a function `fib(n)` that returns `F(n)`. Solve it however makes sense
to you first, no hints yet.

**Hints, iterative:**
1. You don't need to remember every value of F, only enough to compute the next one. How many
   previous values does the definition actually depend on?
2. Try tracking just the last two values in two variables, updating them as you count up from 0
   to n.

Check the problem solution(s) here:
[`iterative_solution.cpp`](../problem_solutions/fibonacci-number/iterative_solution.cpp),
[`iterative_solution.py`](../problem_solutions/fibonacci-number/iterative_solution.py)

**Now, try it recursively.** Once your iterative solution works, solve the same problem again
using recursion.
1. Look at the math definition again: `F(n) = F(n-1) + F(n-2)` already describes F in terms of
   itself. What would it look like to write that directly as a function that calls itself?
2. What are the base cases: the values of n where you already know the answer without computing
   anything?
3. Write `fib(n)` so it returns immediately on the base cases, and otherwise returns
   `fib(n - 1) + fib(n - 2)`.

Check the problem solution(s) here:
[`recursive_solution.cpp`](../problem_solutions/fibonacci-number/recursive_solution.cpp),
[`recursive_solution.py`](../problem_solutions/fibonacci-number/recursive_solution.py)

Full write-up, including complexity discussion:
[`problem_solutions/fibonacci-number/README.md`](../problem_solutions/fibonacci-number/README.md)

</details>

<details>
<summary>4. Longest Nice Substring</summary>

LeetCode 1763, Longest Nice Substring: https://leetcode.com/problems/longest-nice-substring/description/

A substring is "nice" if every letter appearing in it shows up in both uppercase and lowercase.
Given a string, find its longest nice substring.

Example: for `s = "YazaAay"`, `"aAa"` is nice, and it's the longest one in `s`.

**Try it yourself.** If a character in the string shows up in only one case, no letter, upper or
lower, matching it in the other case, no nice substring can contain that character at all. What
does that tell you about where you could split the string, and about what to do with each half?

Check the problem solution(s) here:
[`solution.cpp`](../problem_solutions/longest-nice-substring/solution.cpp),
[`solution.py`](../problem_solutions/longest-nice-substring/solution.py)

Full write-up, including complexity discussion:
[`problem_solutions/longest-nice-substring/README.md`](../problem_solutions/longest-nice-substring/README.md)

</details>

<details>
<summary>5. Recap</summary>

- Compare the two factorial solutions: which one reads closer to the math definition itself?
- Trace `fib(5)` by hand for the recursive version; notice `fib(3)` gets computed more than
  once. What does that suggest about how this scales as n grows?
- In Longest Nice Substring, the split point isn't the middle of the string, it's wherever a
  "bad" character turns up. Recursion doesn't require splitting evenly.

We won't resolve the repeated-computation question today; that's the seed for memoization/DP,
and the uneven split is a first taste of divide and conquer, both coming later in the semester.

</details>
