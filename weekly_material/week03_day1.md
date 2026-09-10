# Week 03, Day 1 (September 8, 2026)

## Today

Last time we finished building Longest Nice Substring, one small function at a time. It passes
the tests. That leaves the two questions we ask about every solution:

1. **Is it correct?** Not "did my tests pass", but "does it give the right answer for every
   possible input".
2. **How slow is it?** And once we know that, can we make it faster?

Today is those two questions, start to finish, on the solution you already have.

<details>
<summary>1. The solution we're analyzing</summary>

The four functions we built last session, in one file:
[Python](../misc_references/longest-nice-substring.py),
[C++](../misc_references/longest-nice-substring.cpp).

**Open one and keep it on screen.** Everything today is about those lines:

Here is a summary of what each function does:

- `both_cases_exist(c, s)`: does `c` appear in `s` in both cases?
- `first_single_case_char(s)`: index of the first character that fails that check, or `-1`
- `split_around_index(s, i)`: the two pieces of `s` on either side of index `i`
- `longest_nice_substring(s)`: returns `s` when there is no bad character, otherwise splits at it
  and recurses on both pieces, keeping the longer result

</details>

<details>
<summary>2. Is it correct? (why testing is not enough)</summary>

We ran it on 5 strings and got 5 right answers.

**Question for the class:** how many strings of length 20 are there, using only English letters?
And how many of them did we test?

<details>
<summary>Answer</summary>

52 choices per position, 20 positions: 52^20 strings, about 10^34. We tested 5.

Testing shows the presence of bugs, never their absence. To claim the function is right for
**every** input, we need a proof. The tool for proving things about recursive functions is
**mathematical induction**.

</details>

**Question for the class:** you have infinitely many dominoes in a line. What two facts are
enough to conclude that all of them fall?

<details>
<summary>Answer: induction in one box</summary>

1. The first one falls. (**base case**)
2. Whenever a domino falls, it knocks over the next one. (**inductive step**)

Together: all of them fall. You never check them one by one.

Induction on code works the same way:

| Induction | Recursive function |
|---|---|
| Base case: prove the claim for the smallest input directly | The `return` that does not recurse |
| Inductive step: assume it for smaller inputs, prove it for this one | The branch that calls itself |

The proof and the code have the same shape. If your function has a base case and a recursive
case, your proof has a base case and an inductive step, and they line up line by line.

</details>

</details>

<details>
<summary>3. The proof, one question at a time</summary>

We build the proof in four steps. Each step is a question first, answer after.

**Question 1:** what exactly are we claiming? Say it in one sentence, precisely enough that
someone could disagree with it.

<details>
<summary>Claim</summary>

**Claim:** for every string `s`, `longest_nice_substring(s)` returns the longest nice substring
of `s`, and on a tie it returns the leftmost one.

That is the whole thing we have to defend. Nothing more, nothing less.

</details>

**Question 2:** which inputs does the function answer without calling itself? Is the answer right
for them?

<details>
<summary>Base case</summary>

**Base case:** `first_single_case_char(s)` returns `-1`, meaning no character failed the check,
so `s` is nice. The function returns `s` itself. A string is a substring of itself, and no
substring is longer than the whole string, so `s` is its longest nice substring. Correct.

This also covers `s = ""`: the loop never runs, `-1` comes back, and `""` is returned, which is
right.

This is the `if i == -1: return s` branch, nothing else.

</details>

**Question 3:** for the recursive case, what are we allowed to assume? Careful: the two pieces we
recurse on can be *any* size smaller than `s`, not just `len(s) - 1`.

<details>
<summary>Assume</summary>

**Assume:** the Claim holds for every string shorter than `s`.

This is **strong induction**: we assume the claim for *all* smaller sizes, not only the size one
below. We need that here because splitting `"YazaAay"` at index 2 gives pieces of length 2 and 4,
neither of which is "one smaller".

(Weak induction assumes only `n - 1`. Strong induction assumes `0, 1, ..., n - 1`. Use strong
induction whenever the recursion can jump to any smaller size.)

</details>

**Question 4:** we throw away the character at index `i` entirely, it never appears in either
recursive call. Why is that not losing a possible answer?

<details>
<summary>The key step, in plain words</summary>

Say `s[i]` is `'z'` and there is no `'Z'` anywhere in `s`.

Take any substring of `s` that contains that `'z'`. For it to be nice, it would need a `'Z'`
inside it. But every character inside a substring of `s` is also a character of `s`, and `s` has
no `'Z'` at all. So that substring has no `'Z'` either, so it is not nice.

Conclusion: **no nice substring of `s` can contain index `i`.** Every nice substring therefore
lies entirely to the left of `i` or entirely to the right of `i`. Nothing is lost by splitting.

</details>

<details>
<summary>Show (the recursive case)</summary>

**Show:** `first_single_case_char(s)` returned some `i >= 0`.

1. By the step above, every nice substring of `s` lives entirely in `left = s[:i]` or entirely
   in `right = s[i+1:]`.
2. Both `left` and `right` are shorter than `s` (we dropped at least the character at `i`), so by
   **Assume**, `longest_nice_substring(left)` and `longest_nice_substring(right)` are each the
   longest nice substring of their own piece.
3. The longest nice substring of `s` is therefore the longer of those two results. `left` starts
   earlier in `s` than `right`, so on a tie we keep `left`, which is the leftmost one.

That is exactly the last three lines of the function.

**Closing the loop.** Base case covers every string where the loop finds nothing. Show covers
every string where it finds something, using only the answer for shorter strings, which the Base
case starts off and Show carries upward. Every string is one or the other, so the Claim holds
for all strings.

</details>

The same proof, written out in the same labels: [Week 2, Day 1](week02_day1.md).

<details>
<summary>References</summary>

- Rosen, *Discrete Mathematics and Its Applications*, Ch. 5 "Induction and Recursion"
  (p. 331 onward): weak induction, strong induction, and recursive definitions, with many worked
  proofs. Read this if the difference between "assume n - 1" and "assume everything below n" is
  still fuzzy.
- Erickson, *Algorithms*, Ch. 1 "Recursion", §1.4 "Correctness" (pp. 27-28): the same
  base case / inductive step shape applied to a recursive function.

</details>

</details>

<details>
<summary>4. How much work does ONE call do?</summary>

Ground rules for counting, all we need today:

- Count steps as a function of the input size. For a string, the size is its length.
- Drop constants: 3n and n are both `O(n)`.
- Keep the biggest term: `n^2 + n` is `O(n^2)`.

Take one call of `longest_nice_substring` on a piece of length `m`, and count **only what that
call does itself**, not what its recursive calls do.

**Question for the class:** what does `c.upper() in s` cost? It is one line, but is it one step?

<details>
<summary>Answer</summary>

It is a loop in disguise. `in` walks the string looking for the character, so on a piece of
length `m` it costs `O(m)`. `both_cases_exist` does that twice, so one call to it is `O(m)`.

This is the single most important habit in complexity analysis: a short line is not a cheap line.
`in`, `find`, `count`, `substr`, slicing, sorting, all of them hide loops.

</details>

**Question for the class:** now add up one whole call. How many times does the loop run, what
does each iteration cost, and what does the split cost?

<details>
<summary>Answer: one call is O(m^2)</summary>

| Line | Cost |
|---|---|
| `both_cases_exist(c, s)`, one call | `O(m)` |
| the loop in `first_single_case_char`, up to `m` iterations | `m * O(m) = O(m^2)` |
| `split_around_index`, copies both pieces | `O(m)` |
| picking the longer result | `O(1)` |

**One call costs `O(m^2)`** on a piece of length `m`, so `O(n^2)` for the very first call.

</details>

</details>

<details>
<summary>5. How many calls are there in total?</summary>

**Question for the class:** every call either stops or splits into two. Could this blow up into
`2^n` calls, like the recursive Fibonacci did?

<details>
<summary>Answer: no, there are at most O(n) calls</summary>

Look at what a splitting call does with its characters: it **deletes** the bad character at
index `i` and hands the rest to two calls that never see that character again. The two pieces
share nothing.

So each splitting call permanently consumes one character. A string of length `n` has `n`
characters, so there are at most `n` splitting calls, and each makes 2 children:

**at most `2n + 1` calls in total, which is `O(n)`.**

That is the difference from Fibonacci: `fib(n-1)` and `fib(n-2)` overlap and redo each other's
work, while these two pieces are disjoint.

</details>

</details>

<details>
<summary>6. The Master Theorem</summary>

We now have: `O(n)` calls, each costing at most `O(n^2)`. Multiplying gives a ceiling of
`O(n^3)` for the whole run. That ceiling is honest but crude. For the case we actually care
about, where the split lands somewhere in the middle, there is a formula.

Write the cost of the whole run as a **recurrence**: the cost of a call, written in terms of the
cost of the calls it makes. When the bad character sits near the middle, each call hands out two
pieces of size `n/2` and does `O(n^2)` work itself:

```
T(n) = 2 * T(n/2) + n^2
```

**Question for the class:** how do we turn that self-referencing formula into a plain answer like
"`n^2`" or "`n log n`"?

<details>
<summary>The Master Theorem</summary>

For any recurrence of the form

```
T(n) = a * T(n / b) + f(n)          with a >= 1 and b > 1
```

read off three things:

- `a`: how many recursive calls each call makes
- `b`: how many times smaller each of those pieces is
- `f(n)`: the work one call does by itself, outside the recursive calls

Compute `n^(log_b a)`, the "recursion side", and compare it with `f(n)`:

| Case | When | Answer |
|---|---|---|
| 1 | `f(n)` is polynomially **smaller** than `n^(log_b a)` | `T(n) = O(n^(log_b a))` |
| 2 | `f(n)` is the **same** as `n^(log_b a)` | `T(n) = O(n^(log_b a) * log n)` |
| 3 | `f(n)` is polynomially **bigger** than `n^(log_b a)` | `T(n) = O(f(n))` |

Plain reading: either the work piles up at the bottom of the recursion (case 1), or it is spread
evenly over all `log n` levels (case 2), or the very first call already dominates everything
below it (case 3).

Case 3 has one extra condition, `a * f(n/b) <= c * f(n)` for some `c < 1`, which just says
`f` really does shrink as you go down. It holds in every example we use.

</details>

**Question for the class:** warm up on one we already know. Merge Sort splits into 2 halves and
merges in linear time: `T(n) = 2T(n/2) + n`. Which case, and what is the answer?

<details>
<summary>Answer</summary>

`a = 2`, `b = 2`, `f(n) = n`. Then `log_b a = log_2 2 = 1`, so `n^(log_b a) = n^1 = n`.

`f(n) = n` is the same as `n`, so this is **case 2**:

```
T(n) = O(n * log n)
```

which is exactly the `O(n log n)` we claimed for Merge Sort in
[Week 2, Day 1](week02_day1.md).

</details>

**Question for the class:** now do ours: `T(n) = 2T(n/2) + n^2`.

<details>
<summary>Answer</summary>

`a = 2`, `b = 2`, `f(n) = n^2`. Again `n^(log_b a) = n`.

`f(n) = n^2` is polynomially bigger than `n`, so this is **case 3**, and the answer is `f(n)`
itself:

```
T(n) = O(n^2)
```

(Case 3's extra condition: `2 * (n/2)^2 = n^2 / 2`, which is half of `n^2`, so `c = 1/2` works.)

Read it out loud: the very first call already does `n^2` work scanning the string, and
everything below it adds up to less than that. The top call is the whole cost.

</details>

**Question for the class:** what if the bad character is at the very front, so one piece is empty
and the other has `n - 1` characters? The recurrence is `T(n) = T(n-1) + n^2`. Which case is
that?

<details>
<summary>Answer: none of them, and that is the point</summary>

The Master Theorem only covers `T(n/b)`, pieces that are a constant **fraction** of the input.
`T(n-1)` is not a fraction, it is a subtraction, so the theorem does not apply at all. Our
splits are not guaranteed to be even: the split point is wherever the bad character happens to
be, which could be anywhere.

When the theorem does not apply, **unroll** the recurrence by hand:

```
T(n) = n^2 + (n-1)^2 + (n-2)^2 + ... + 1 = O(n^3)
```

which matches the crude ceiling we already got by multiplying `O(n)` calls by `O(n^2)` per call.

</details>

<details>
<summary>References</summary>

- Cormen et al., *Introduction to Algorithms*, §4.5 "The master method for solving recurrences"
  (pp. 93-97): the three cases stated formally, with worked examples. §4.6 proves the theorem,
  which you can skip.
- Erickson, *Algorithms*, §1.7 "Recursion Trees" (pp. 31-34): how to solve a recurrence by
  drawing the tree of calls and adding up each level. Worth reading, because it works on the
  uneven recurrences the Master Theorem refuses.

</details>

</details>

<details>
<summary>7. Time and space, all together</summary>

**Time.**

| Situation | Recurrence | Result |
|---|---|---|
| Bad character near the middle | `T(n) = 2T(n/2) + n^2` | `O(n^2)` (Master Theorem, case 3) |
| Bad character at one end | `T(n) = T(n-1) + n^2` | `O(n^3)` (unroll) |
| Guaranteed ceiling | `O(n)` calls times `O(n^2)` per call | `O(n^3)` |

`O(n^3)` is the number we would quote, because complexity is a promise about the worst input,
not the convenient one. (It is a ceiling: a string that actually forces the full `n^3` is hard to
build, since there are only 52 letters to play with. Quote the ceiling anyway.)

**Question for the class:** how much extra memory does this use? There are no arrays anywhere,
so is it `O(1)`?

<details>
<summary>Answer</summary>

No. Two things cost memory:

1. **The copies.** `split_around_index` builds brand new strings, it does not view into the old
   one. A call on a piece of length `m` holds `O(m)` characters of its own.
2. **The call stack.** A call is not finished until both of its recursive calls return, so a
   whole chain of calls is alive at once, each holding its own copies. The chain can be `O(n)`
   deep (one character removed at a time).

Worst case those two multiply: `O(n^2)` characters alive at once. When the splits are even, the
chain holds `n + n/2 + n/4 + ...`, which is `O(n)`.

Fix, if you ever needed it: pass `start` and `end` indices into the original string instead of
copying pieces. Then every call holds `O(1)` of its own and the total is `O(n)`, just the stack.

</details>

</details>

<details>
<summary>8. Can we make it faster?</summary>

**Question for the class:** look back at the cost table in step 4. One line is responsible for
the whole `n^2` inside a single call. Which one, and is that work actually necessary?

<details>
<summary>Answer</summary>

The guilty line is `c.upper() in s`, inside the loop.

Here is the waste: the loop asks "is `'A'` in this piece?", then "is `'b'` in this piece?", then
"is `'B'` in this piece?", rescanning the same unchanged piece every single time. The piece does
not change during the loop. The set of characters in it does not change either. We are computing
the same answer over and over.

**So compute it once, up front.** Walk the piece one time and record every character you see in a
**hash table** (a `set` in Python, `unordered_set` in C++). After that, "is `'A'` in this piece?"
is one hash lookup instead of a scan.

- Building the set: one pass, `O(m)`.
- Each lookup afterwards: `O(1)`.

</details>

<details>
<summary>The change, function by function</summary>

Only two of the four functions move, and neither one changes shape:

- `first_single_case_char(s)`: build `chars_in_s` (a `set` in Python, an `unordered_set` in C++)
  from `s` in one pass, before the loop starts.
- `both_cases_exist(c, chars_in_s)`: take that set instead of the string, and look the two cases
  up in it.

| The check inside the loop | Cost |
|---|---|
| before: `c.upper() in s` | `O(m)`, scans the whole piece |
| after: `c.upper() in chars_in_s` | `O(1)`, one hash lookup |

`split_around_index` and `longest_nice_substring` are untouched.

The same four functions with those two edits applied:
[Python](../misc_references/longest-nice-substring-hashed.py),
[C++](../misc_references/longest-nice-substring-hashed.cpp).

</details>

**Question for the class:** redo the two counts from steps 4 and 5 with the fast check. What is
one call worth now, and what does the Master Theorem say?

<details>
<summary>Answer</summary>

One call on a piece of length `m`:

| Line | Cost |
|---|---|
| building `chars_in_s` | `O(m)` |
| the loop, up to `m` iterations, `O(1)` each | `O(m)` |
| copying the two pieces | `O(m)` |

**One call is now `O(m)` instead of `O(m^2)`.** The number of calls is unchanged, still `O(n)`.

- Even splits: `T(n) = 2T(n/2) + n`. That is `a = 2`, `b = 2`, `f(n) = n`, so
  `n^(log_b a) = n`, **case 2**, giving `O(n log n)`. Same recurrence as Merge Sort.
- Worst case: `O(n)` calls times `O(n)` per call, so `O(n^2)`.

| | Original | With the hash table |
|---|---|---|
| One `both_cases_exist` check | `O(n)` | `O(1)` |
| One call | `O(n^2)` | `O(n)` |
| Even splits | `O(n^2)` | `O(n log n)` |
| Worst case | `O(n^3)` | `O(n^2)` |

Every row dropped by a factor of `n`, and we did it by deleting repeated work, not by changing
the algorithm. The recursion, the base case, and the proof from step 3 are all untouched, so the
solution is still correct: the proof never depended on *how* `both_cases_exist` answered, only
on *what* it answered.

</details>

**This is today's takeaway solution.** The optimized version, in full:
[`optimized_solution.py`](../problem_solutions/longest-nice-substring/optimized_solution.py),
[`optimized_solution.cpp`](../problem_solutions/longest-nice-substring/optimized_solution.cpp).
This is the one to submit to LeetCode and the one to keep.

The same two edits applied to the four worksheet functions instead, if that shape is easier to
compare against what you wrote: [Python](../misc_references/longest-nice-substring-hashed.py),
[C++](../misc_references/longest-nice-substring-hashed.cpp).

Original and optimized side by side, with the write-up:
[`problem_solutions/longest-nice-substring/`](../problem_solutions/longest-nice-substring/).

</details>

<details>
<summary>9. Recap</summary>

- Tests find bugs. Induction proves correctness. Base case and inductive step line up with the
  base case and recursive case of your function.
- Complexity is two questions: how much work does **one call** do, and how many calls are there.
- A one-line operation is not a one-step operation. `in`, `find`, `substr`, and slicing all hide
  loops.
- The Master Theorem reads off `a`, `b`, `f(n)` from `T(n) = a T(n/b) + f(n)` and gives the
  answer, but only for even splits. For `T(n-1)`, unroll by hand.
- The first optimization to look for is repeated work: something recomputed inside a loop whose
  answer never changes. Precompute it into a hash table and pay `O(1)` per lookup.
- **Take away the optimized solution:**
  [`optimized_solution.py`](../problem_solutions/longest-nice-substring/optimized_solution.py),
  [`optimized_solution.cpp`](../problem_solutions/longest-nice-substring/optimized_solution.cpp).
  Same algorithm, same proof, one hash table, `O(n^3)` down to `O(n^2)`.

</details>
