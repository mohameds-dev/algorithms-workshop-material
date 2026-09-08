# Week 03, Day 1 (September 8, 2026)

## Today

Last time we finished building Longest Nice Substring, one small function at a time. It passes
the tests. That leaves the two questions we ask about every solution:

1. **Is it correct?** Not "did my tests pass", but "does it give the right answer for every
   possible input".
2. **How slow is it?** And once we know that, can we make it faster?

We'll answer both these questions in Part 1 below. Then, we'll introduce a new problem (Towers of Hanoi) in Part 2. Let's go!

---

## Part 1: Longest Nice Substring, correctness and complexity

<details>
<summary>1. The solution we're analyzing</summary>

The four functions we built last session, in one file:
[Python](../misc_references/longest-nice-substring.py),
[C++](../misc_references/longest-nice-substring.cpp).

**Open one and keep it on screen.** Everything in Part 1 is about those lines:

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

- Rosen, *Discrete Mathematics and Its Applications*, Ch. 5 "Induction and Recursion" (p. 331 onward): weak induction, strong induction,
  and recursive definitions, with many worked proofs. Read this if the difference between
  "assume n - 1" and "assume everything below n" is still fuzzy.
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

Both versions, side by side, with the write-up:
[`problem_solutions/longest-nice-substring/`](../problem_solutions/longest-nice-substring/).

</details>

<details>
<summary>9. Part 1 recap</summary>

- Tests find bugs. Induction proves correctness. Base case and inductive step line up with the
  base case and recursive case of your function.
- Complexity is two questions: how much work does **one call** do, and how many calls are there.
- A one-line operation is not a one-step operation. `in`, `find`, `substr`, and slicing all hide
  loops.
- The Master Theorem reads off `a`, `b`, `f(n)` from `T(n) = a T(n/b) + f(n)` and gives the
  answer, but only for even splits. For `T(n-1)`, unroll by hand.
- The first optimization to look for is repeated work: something recomputed inside a loop whose
  answer never changes. Precompute it into a hash table and pay `O(1)` per lookup.

</details>

---

## Part 2: Towers of Hanoi

<details>
<summary>1. The problem</summary>

Three poles: `A`, `B`, `C`. On pole `A` there is a stack of `n` disks, all different sizes,
biggest at the bottom, getting smaller as you go up.

```
   |        |        |
  ###       |        |
 #####      |        |
#######     |        |
---A---  ---B---  ---C---
```

**Goal:** move the whole stack from `A` to `C`.

**Rules:**
1. Move exactly one disk at a time.
2. Only the top disk of a pole can be moved.
3. A disk may never sit on top of a smaller disk.

**Output:** print each move as you make it, for example `move disk 2 from A to B`.

**Your turn.** Write the function. Use these headers so everyone is building the same thing:

```
function move_disk(disk, from_pole, to_pole):
    print "move disk <disk> from <from_pole> to <to_pole>"

function hanoi(n, from_pole, to_pole, aux_pole):
    // move the top n disks from from_pole to to_pole, using aux_pole as the spare
```

Note what `hanoi` takes: not "move from A to C", but "move from *whichever* pole to *whichever*
pole, with a third one free". You call it as `hanoi(n, "A", "C", "B")`.

**Question to sit with before you write anything:** forget the small disks for a second. Disk `n`
is the biggest one, sitting at the bottom of `A`, and it has to end up at the bottom of `C`.
What has to be true about the other `n - 1` disks at the moment you move it?

<details>
<summary>Hints</summary>

1. Do not try to picture all `n` moves at once. Think about **one** move: the move of the biggest
   disk, disk `n`, from `A` to `C`.
2. For that move to be legal, disk `n` must be the top of `A` (so nothing is above it) and `C`
   must be empty of anything smaller (so nothing is below it to break rule 3). Where does that
   force the other `n - 1` disks to be? There is only one pole left.
3. So the plan is: get `n - 1` disks onto `B`, move disk `n` from `A` to `C`, then get those
   `n - 1` disks from `B` onto `C`.
4. "Get `n - 1` disks from `A` to `B`" is the same problem you are solving, one size smaller,
   with `B` as the destination and `C` as the spare. That is why the poles are parameters: the
   roles rotate on every call.
5. Base case: what is there to do when `n` is 0? Answer that and you are done.

</details>

</details>

<details>
<summary>2. Solution</summary>

Three lines of work, and the two recursive calls are the same function with the poles swapped:

```
function hanoi(n, from_pole, to_pole, aux_pole):
    if n == 0:
        return                                      // base case: no disks, nothing to do

    hanoi(n - 1, from_pole, aux_pole, to_pole)      // move the small disks out of the way
    move_disk(n, from_pole, to_pole)                // move the biggest disk
    hanoi(n - 1, aux_pole, to_pole, from_pole)      // move the small disks back on top
```

Read the argument order carefully, that is where the whole trick lives:

- Call 1: the **destination** is `aux_pole`, because we are parking the small disks. The old
  destination `to_pole` becomes the spare.
- Call 2: the **source** is `aux_pole`, because that is where we parked them. The old source
  `from_pole` is now free, so it becomes the spare.

**Example run:** `hanoi(3, "A", "C", "B")` prints

```
move disk 1 from A to C
move disk 2 from A to B
move disk 1 from C to B
move disk 3 from A to C
move disk 1 from B to A
move disk 2 from B to C
move disk 1 from A to C
```

7 moves. Look at line 4: that is disk 3 moving, and by then disks 1 and 2 are both parked on `B`,
exactly as the plan promised. The 3 lines above it are `hanoi(2, A, B, C)` and the 3 below it are
`hanoi(2, B, C, A)`.

Full solutions, ready to run:
[`solution.py`](../algorithm_implementation/towers-of-hanoi/solution.py),
[`solution.cpp`](../algorithm_implementation/towers-of-hanoi/solution.cpp). They are the
pseudocode above line for line, plus the `move_disk` printer. Write-up:
[`algorithm_implementation/towers-of-hanoi/`](../algorithm_implementation/towers-of-hanoi/).

</details>

<details>
<summary>3. Why it's correct</summary>

**Question for the class:** the code never checks rule 3. There is no `if` anywhere asking
whether the disk we are about to place is smaller than the one underneath. So why is every move
it prints legal?

<details>
<summary>Proof by induction</summary>

Setup we rely on: the `n` disks being moved are the `n` **smallest** disks in the game, and they
are the top `n` disks of `from_pole`. Any disk sitting on the other two poles is bigger than all
of them, so nothing we place can ever be too big.

**Claim:** `hanoi(n, X, Y, Z)` moves the top `n` disks from `X` to `Y`, one at a time, never
placing a disk on a smaller one, and leaves every other disk where it found it.

**Base case:** `n = 0`. The function returns immediately and prints nothing. Zero moves, zero
illegal moves, nothing disturbed. This is the `if n == 0: return` line.

**Assume:** the Claim holds for `n - 1`.

**Show:** for `n`, the function does exactly three things:

1. `hanoi(n - 1, X, Z, Y)`. Those `n - 1` disks are the smallest in the game and sit on top of
   `X`, so **Assume** applies: they all end up on `Z`, legally. Disk `n` never moved, so it is
   now alone at the top of `X`.
2. `move_disk(n, X, Y)`. Legal, because disk `n` is the top of `X` (step 1 cleared everything
   above it), and `Y` holds none of the `n - 1` smaller disks (they are all on `Z`), so `Y` is
   either empty or its top disk is bigger than disk `n`.
3. `hanoi(n - 1, Z, Y, X)`. Those same `n - 1` disks are now the top of `Z` and still the
   smallest in the game, so **Assume** applies again: they all end up on `Y`, legally, landing on
   top of disk `n`, which is bigger than every one of them.

After step 3, all `n` disks are on `Y` in the right order, and nothing else moved.

Base case and Show together cover every `n >= 0`, so the Claim holds.

Answer to the question: rule 3 is never checked because it is never in danger. The recursion
always moves a **complete set of the smallest disks**, and something smaller than everything else
can be placed anywhere.

</details>

<details>
<summary>References</summary>

- Erickson, *Algorithms*, Ch. 1 "Recursion", §1.3 "Tower of Hanoi" (pp. 24-26): the same
  algorithm and the same argument, with pictures of the "ignore everything but the bottom disk"
  idea.

</details>

</details>

<details>
<summary>4. Complexity</summary>

**Question for the class:** guess first, then count. How many moves does `hanoi(n)` print? Our
run with `n = 3` printed 7.

<details>
<summary>Answer: 2^n - 1 moves</summary>

Let `M(n)` be the number of printed moves. Read them straight off the three lines of the
function: two recursive calls on `n - 1` disks, plus the one move in the middle.

```
M(0) = 0
M(n) = 2 * M(n-1) + 1
```

Unroll it:

```
M(n) = 2 M(n-1) + 1
     = 4 M(n-2) + 2 + 1
     = 8 M(n-3) + 4 + 2 + 1
     ...
     = 2^n * M(0) + (2^(n-1) + ... + 4 + 2 + 1)
     = 2^n - 1
```

Check against the run above: `M(3) = 2^3 - 1 = 7`. Correct.

If you prefer induction: `M(0) = 0 = 2^0 - 1`, and `M(n) = 2(2^(n-1) - 1) + 1 = 2^n - 1`.

**Time: `O(2^n)`.** Each call does `O(1)` work besides its recursive calls, and there are about
`2^n` of them.

</details>

**Question for the class:** why can't we just use the Master Theorem on `M(n) = 2M(n-1) + 1`?

<details>
<summary>Answer</summary>

Same reason as the lopsided case in Part 1: the Master Theorem needs `T(n/b)`, a piece that is a
constant **fraction** of the input. Here the subproblem is `n - 1`, a subtraction, not a
division. The theorem simply does not apply, so we unroll, which is what we just did.

Rule of thumb: `T(n/2)` means the Master Theorem is on the table, `T(n-1)` means unroll.

</details>

**Question for the class:** the time is exponential. How much memory does it use?

<details>
<summary>Answer: O(n)</summary>

There is no array, no copy, no data structure at all. The only memory is the call stack, and the
deepest chain of calls that are alive at the same time is `n` frames (`n`, then `n-1`, down to
`0`). Each frame holds 4 small values.

**Space: `O(n)`.**

This is worth pausing on: `O(2^n)` time and `O(n)` space in the same function. Time counts every
call ever made, space counts only the calls alive at one moment.

</details>

<details>
<summary>Can it be done in fewer than 2^n - 1 moves?</summary>

No. Disk `n` has to move at least once. Right before it moves off `from_pole`, the other `n - 1`
disks must be off both `from_pole` and `to_pole`, so they are all stacked on the third pole:
that is a complete `n - 1` transfer. Right after, they must all come back on top of it: another
complete `n - 1` transfer. So any correct solution needs at least `2 M(n-1) + 1` moves, which is
the exact recurrence our algorithm achieves. It is optimal.

Fun consequence: the legend attaches 64 disks to this puzzle. At one move per second, `2^64 - 1`
moves take about 585 billion years.

</details>

</details>

<details>
<summary>5. Towers of Hanoi on a graph of poles</summary>

Now the version from Dr. Leiss's class.

Same disks, same three rules, but the poles are now the **nodes of a graph**, and a disk may only
move along an **edge**. Our `hanoi` quietly assumed all three poles were connected to each other,
so any move was allowed. Drop that assumption.

Example: 5 poles, `S` (start), `A`, `B`, `C`, `E` (end).

```
S --- A --- B --- C --- E
      |                 |
      +-----------------+
```

Edges: `S-A`, `A-B`, `B-C`, `C-E`, `E-A`. The goal is to move all `n` disks from `S` to `E`.

**Question for the class:** `S` touches only `A`. There is no `S-E` edge, so no disk can ever go
straight from `S` to `E`. Is this still solvable? And what is our function even supposed to do
with `aux_pole` now, when the three poles involved may not be connected to each other?

<details>
<summary>Answer: yes, as long as the graph is connected</summary>

Two ideas, and they call each other.

**Idea 1: moving a whole stack between two poles that are not neighbors.** Find a path in the
graph and walk the entire stack along it, one edge at a time. To get a stack from `S` to `E`,
take the path `S -> A -> E`: move the whole stack from `S` to `A`, then the whole stack from `A`
to `E`.

**Idea 2: moving a whole stack across a single edge `X-Y`.** This is the original trick, with one
change: the parking pole no longer has to be a neighbor of anything. Park the top `n - 1` disks
on *any* other pole (getting them there is Idea 1), move disk `n` across the edge `X-Y`, then
bring the `n - 1` disks back on top of it (Idea 1 again).

```
// move the top n disks from X to Y, where X-Y IS an edge
function moveAcrossEdge(n, X, Y):
    if n == 0:
        return
    Z = any pole other than X and Y            // the parking pole, no adjacency needed
    moveStack(n - 1, X, Z)
    move_disk(n, X, Y)
    moveStack(n - 1, Z, Y)

// move the top n disks from X to Y, for ANY two poles
function moveStack(n, X, Y):
    if n == 0 or X == Y:
        return
    for each edge (U, V) along some path X -> ... -> Y in the graph:
        moveAcrossEdge(n, U, V)
```

Legality is free for the same reason as before: we always move a complete set of the smallest
disks, so they can land anywhere, including on poles they are only passing through.

Why this terminates: `moveStack` never calls itself, it only calls `moveAcrossEdge` with the same
`n`. And `moveAcrossEdge` only calls `moveStack` with `n - 1`. So every round trip between the
two functions drops the disk count by one, until `n = 0`.

</details>

<details>
<summary>Walking the example: the states</summary>

Write a **state** as `(X -> Y, k)`: "move a stack of `k` disks from `X` to `Y`". Start from the
goal and expand:

```
(S -> E, n)                      path S-A-E, so two edge moves
|
+-- (S -> A, n)                  edge. park the top n-1 on B
|   +-- (S -> B, n-1)            not an edge. path S-A-B
|   |   +-- (S -> A, n-1)        <-- state we are already inside, now with n-1 disks
|   |   +-- (A -> B, n-1)        edge. park on C
|   +-- move disk n: S -> A
|   +-- (B -> A, n-1)            edge. park on C
|
+-- (A -> E, n)                  edge. park the top n-1 on B
    +-- (A -> B, n-1)            <-- state seen above, now with n-1 disks
    +-- move disk n: A -> E
    +-- (B -> E, n-1)            not an edge. path B-C-E
        +-- (B -> C, n-1)        edge. park on A
        +-- (C -> E, n-1)        edge. park on A
```

That is the whole point of the exercise: **the states loop back on themselves.** `(S -> A)`
appears inside `(S -> A)`. `(A -> B)` shows up on both sides of the tree. And that is fine,
because there are only finitely many pole pairs (5 poles give 20 ordered pairs), and every time a
pair comes back it comes back with **one disk fewer**. The pairs repeat, the disk count never
does, so the whole thing bottoms out at `n = 0`.

So the recipe for any connected graph of poles is:

1. Pick a path from the source to the destination.
2. For each edge on it: park the smaller disks on any free pole, cross the edge, bring them back.
3. "Park" and "bring back" are themselves steps 1 and 2, with one disk fewer.

</details>

<details>
<summary>What does it cost?</summary>

Suppose every path we use is at most `L` edges long. Then:

```
cost of one edge move:    C(n) = 2 * (cost of moving n-1 disks anywhere) + 1
cost of moving anywhere:         at most L edge moves
```

so `C(n) <= 2L * C(n-1) + 1`, which unrolls to `O((2L)^n)`.

Still exponential, just with a bigger base than 2. Sanity check: the classic puzzle is the case
where all three poles are connected to each other, so every path is a single edge, `L = 1`, and
the formula collapses to `C(n) = 2C(n-1) + 1 = 2^n - 1`. Same answer as Part 2, step 4.

</details>

<details>
<summary>References</summary>

- Erickson, *Algorithms*, Ch. 1 exercises, problems 4 and 5 (pp. 47-49): restricted Towers of
  Hanoi. Problem 4 forbids moves between two of the pegs (a 3-node path graph), problem 5 puts
  `k` pegs in a row and allows moves only between neighbors. Good practice for this exact idea.

</details>

</details>

<details>
<summary>6. Part 2 recap</summary>

- Towers of Hanoi: to move `n` disks, park `n - 1` somewhere, move the big one, bring the
  `n - 1` back. Three lines.
- The poles are parameters, not fixed names. The roles rotate on every call, and reading that
  argument order is the whole exercise.
- Rule 3 is never checked in the code because it is never in danger: the recursion only ever
  moves a complete set of the smallest disks.
- `2^n - 1` moves, `O(2^n)` time, `O(n)` space, and no algorithm can do better on move count.
- `T(n) = 2T(n-1) + 1` is a subtraction, not a division, so unroll it. The Master Theorem is for
  `T(n/b)`.
- Restrict the moves to a graph and the same recursion still works: walk the stack along a path,
  one edge at a time, parking the smaller disks anywhere. The pole pairs repeat, the disk count
  strictly drops, so it terminates.

</details>
