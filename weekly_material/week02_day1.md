# Week 02, Day 1 (September 1, 2026)

## Today

We left Longest Nice Substring as an open problem last time, with just a hint about splitting.
Today we'll follow that hint all the way to a working solution: find the idea, prove it's
correct, turn it into pseudocode, and then look at real code. Then we'll apply that same
find-it/prove-it/code-it process to Merge Sort, a classic divide and conquer algorithm that
splits an array right down the middle instead of at a special point.

<details>
<summary>1. Longest Nice Substring, revisited</summary>

LeetCode 1763, Longest Nice Substring: https://leetcode.com/problems/longest-nice-substring/description/

Recap: a substring is "nice" if every letter appearing in it shows up in both uppercase and
lowercase. Given a string, find its longest nice substring (if there's a tie, return the one
that occurs first; if there's none, return an empty string).

**Finding the splitting idea.**

<details>
<summary>Hints</summary>

1. If every character in a string appears in both upper and lower case somewhere in that same
   string, is the string nice or not?
2. Now suppose one character in the string never appears in the other case, anywhere in the
   string. Could any nice substring possibly contain that character?
3. If a nice substring can never contain that character, where in the string must every nice
   substring live, relative to that character's position?
4. You now have two shorter pieces of the original string, one on each side of that character.
   What have we been doing all week to solve a problem by solving smaller versions of itself?

</details>

<details>
<summary>Solution idea</summary>

Scan the string for a character that doesn't appear in both cases. If you find one at index `i`,
no nice substring can contain index `i`, so every nice substring lies entirely within
`s[0 .. i-1]` or entirely within `s[i+1 .. end]`. Recursively find the longest nice substring of
each half, and return the longer of the two, preferring the left one on a tie since it occurs
first. If you scan the whole string and never find such a character, the string is already nice,
so it's the answer.

</details>

**Proving it's correct.**

Proof by induction: show a claim directly for the smallest case (the base case), then show that
if it holds for everything smaller than `n`, it holds for `n` too (the inductive step).

<details>
<summary>Hints</summary>

1. What are you actually claiming? Try writing it as a precise statement about what `solve(s)`
   returns, for a string `s` of any length.
2. What's the smallest string you'd need to check directly, without relying on any assumption?
   What does `solve` do with it, and is that correct?
3. Assume `solve` is correct for every string shorter than `s`. When `s` has a character at index
   `i` that fails the both-cases check, are the two pieces you recurse on shorter than `s`? Which
   form of induction handles a claim depending on all smaller cases, not just the one immediately
   before it?
4. Why can't a nice substring of `s` contain index `i` at all? Go back to the definition of
   "nice" and argue it directly; it doesn't need induction.

</details>

<details>
<summary>Proof by induction</summary>

**Claim:** for every string `s`, `solve(s)` returns the longest nice substring of `s` (the
leftmost one, on a tie).

**Base case:** the loop finds no bad character. That covers the empty string (nothing to check)
and any already-nice string: both are trivially their own longest nice substring. This is the
`return s` line at the end of `solve`.

**Assume:** `solve(t)` is correct for every string `t` shorter than `s`.

**Show:** `s` has a character at index `i` that fails the both-cases check. First, no nice
substring of `s` can contain index `i`: every character of a nice substring, `s[i]` included,
must appear in both cases within that substring, and any occurrence inside a substring of `s` is
also an occurrence inside `s` itself, so `s[i]` failing the check in `s` means it fails inside any
substring containing it too, contradiction. So every nice substring of `s` lies entirely in
`s[0 .. i-1]` or entirely in `s[i+1 .. end]`, both shorter than `s`. By **Assume**, `solve` is
correct on both, so the longer of the two results (left first, on a tie) is the longest nice
substring of `s`. That's exactly the `left = solve(...)`, `right = solve(...)`, `return` block.

Base case and Show together cover every string, so the claim holds.

</details>

**From idea to pseudocode.** Now build the pseudocode, one piece at a time.

1. The both-cases check:

```
function existsInBothCases(c, s):
    return s.contains(uppercase(c)) and s.contains(lowercase(c))
```

2. The shape of the recursive function, leaving the base case for later:

```
function solve(s):
    // base case: TODO, come back to this once the rest is written

    for i from 0 to length(s) - 1:
        if not existsInBothCases(s[i], s):
            // TODO: split here
```

3. The loop body: split around the first bad character, recurse on both halves, keep the longer
   one. This is the **Show** step from the proof, turned into code:

```
function solve(s):
    // base case: TODO, come back to this once the rest is written

    for i from 0 to length(s) - 1:
        if not existsInBothCases(s[i], s):
            left = solve(s[0 .. i - 1])
            right = solve(s[i + 1 .. end])
            return left if length(left) >= length(right) else right
```

4. The base case: if the loop finishes without ever finding a bad character, `s` is already
   nice, and, being the whole string, it's trivially its own longest nice substring. This is the
   **Base case** from the proof:

```
function solve(s):
    for i from 0 to length(s) - 1:
        if not existsInBothCases(s[i], s):
            left = solve(s[0 .. i - 1])
            right = solve(s[i + 1 .. end])
            return left if length(left) >= length(right) else right

    return s  // base case: no bad character, s is already nice
```

**The real implementation.**

C++ solution: [`problem_solutions/longest-nice-substring/solution.cpp`](../problem_solutions/longest-nice-substring/solution.cpp)

Python solution: [`problem_solutions/longest-nice-substring/solution.py`](../problem_solutions/longest-nice-substring/solution.py)

Full write-up: [`problem_solutions/longest-nice-substring/README.md`](../problem_solutions/longest-nice-substring/README.md)

</details>

<details>
<summary>2. Merge Sort: sorting by divide and conquer</summary>

LeetCode 912, Sort an Array: https://leetcode.com/problems/sort-an-array/description/

Recap: given an array of `n` numbers, return it sorted in nondecreasing order.

Longest Nice Substring split the string at a point that broke a property, then recursed on the
two pieces. Merge Sort takes the split-and-recurse idea and applies it to the simplest possible
split: right down the middle, no matter what the data looks like.

**Finding the splitting idea.**

<details>
<summary>Hints</summary>

1. Suppose you're handed two arrays that are each already sorted. Can you combine them into one
   sorted array faster than dumping everything together and sorting from scratch?
2. Now suppose, instead of sorting the whole array at once, you split it into two roughly equal
   halves and could magically assume each half comes back to you already sorted. What would you
   do with the operation from hint 1 to finish the job?
3. How does each half actually become sorted in the first place? What have we been doing all
   week to solve a problem by solving smaller versions of itself?
4. What's the smallest array you wouldn't need to do any work on at all, the case where "already
   sorted" is true for free?

</details>

<details>
<summary>Solution idea</summary>

Split the array into a left half and a right half of (roughly) equal size. Recursively sort each
half. Then merge the two sorted halves into one sorted array: repeatedly compare the front of
each half, move the smaller one into the result, and repeat until one half is empty, then append
whatever's left of the other. If the array has 0 or 1 elements, it's already sorted; that's the
base case.

<details>
<summary>References</summary>

- Erickson, *Algorithms*, Ch. 1 "Recursion", §1.4 "Mergesort" (pp. 26-28): same idea, worked
  example included.
- Pandurangan, *Efficient Algorithms, Part 1: Fundamentals*, §4.1.2 "MergeSort" (p. 96): same
  idea, different write-up.

</details>

</details>

**Proving it's correct.**

<details>
<summary>Hints</summary>

1. What are you actually claiming? Try writing it as a precise statement about what
   `mergeSort(a)` returns, for an array `a` of any length.
2. What's the smallest array(s) you'd need to check directly, without relying on any assumption?
   What does `mergeSort` do with them, and is that correct?
3. Assume `mergeSort` is correct for every array shorter than `a`. When you split `a` into two
   roughly-equal halves, are both halves shorter than `a`, as long as `a` has more than one
   element? Which form of induction handles a claim depending on all smaller cases, not just the
   one immediately before it?
4. Why does combining two already-sorted halves the way described above actually produce a fully
   sorted array with exactly the right elements? At every step, where must the smallest element
   not yet placed be sitting?

</details>

<details>
<summary>Proof by induction</summary>

**Claim:** for every array `a` of length `n`, `mergeSort(a)` returns a sorted array with exactly
`a`'s elements.

**Base case:** `a` has 0 or 1 elements. There's no pair of elements that could be out of order,
so `a` is already sorted. This is the `if length(a) <= 1: return a` line.

**Assume:** `mergeSort(t)` is correct for every array `t` shorter than `a`.

**Show:** `a` has more than one element, so split it at the midpoint into `left` and `right`,
each strictly shorter than `a`. By **Assume**, `mergeSort(left)` and `mergeSort(right)` are both
correctly sorted. Merging them works because the smallest element not yet placed is always
sitting at the front of `left` or the front of `right` (both are sorted, so nothing smaller is
hiding further back in either one), so always taking the smaller of the two fronts builds the
result in order, using up every element exactly once. That's the `left = ...`, `right = ...`,
`return merge(left, right)` block.

Base case and Show together cover every array, so the claim holds.

*(Merging itself can be proved correct the same way, one level down, by induction on how many
elements are left to place, if you want to go that deep.)*

<details>
<summary>References</summary>

- Erickson, *Algorithms*, §1.4 "Correctness" (pp. 27-28): same two-part shape (why merging
  works, then why the recursion works), more formally.
- Pandurangan, *Efficient Algorithms, Part 1: Fundamentals*, §4.1.2, Theorem 4.4: the same
  claim. His Ch. 2 (p. 46) and Appendix A.2 (p. 339) cover strong induction itself, if hint 3
  felt shaky.

</details>

</details>

**From idea to pseudocode.** Now build the pseudocode, one piece at a time.

1. The merge step, combining two sorted arrays into one:

```
function merge(x, y):
    result = []
    i = 0; j = 0
    while i < length(x) and j < length(y):
        if x[i] <= y[j]:
            append x[i] to result; i = i + 1
        else:
            append y[j] to result; j = j + 1
    append the remaining elements of x (if any) to result
    append the remaining elements of y (if any) to result
    return result
```

2. The shape of the recursive function, leaving the base case for later:

```
function mergeSort(a):
    // base case: TODO, come back to this once the rest is written

    mid = length(a) / 2
    left = mergeSort(a[0 .. mid - 1])
    right = mergeSort(a[mid .. end])
    return merge(left, right)
```

This split-and-recurse block is the **Show** step from the proof, turned into code.

3. The base case: an array of length 0 or 1 needs no work, it's already sorted. This is the
   **Base case** from the proof:

```
function mergeSort(a):
    if length(a) <= 1:
        return a  // base case: 0 or 1 elements are already sorted

    mid = length(a) / 2
    left = mergeSort(a[0 .. mid - 1])
    right = mergeSort(a[mid .. end])
    return merge(left, right)
```

**The real implementation.**

C++ implementation: [`algorithm_implementation/merge-sort/solution.cpp`](../algorithm_implementation/merge-sort/solution.cpp)

Python implementation: [`algorithm_implementation/merge-sort/solution.py`](../algorithm_implementation/merge-sort/solution.py)

Full write-up, including a complexity discussion: [`algorithm_implementation/merge-sort/README.md`](../algorithm_implementation/merge-sort/README.md)

The real implementation sorts in place with a single reused scratch buffer instead of returning a
new array from every call, purely as a memory-management improvement; the divide and conquer
structure, base case, and merge step are unchanged from the pseudocode above.

</details>
