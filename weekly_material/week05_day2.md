# Week 05, Day 2 (September 24, 2026)

## Today

First, we finish what last session ran out of time for: Subsets' complexity and all of
Permutations. Then, a review session built from problems on the COSC3320 Fall 2025 midterm: one
set of recurrences, and two divide-and-conquer/backtracking problems that build directly on
Merge Sort and today's Permutations.

**Session plan (4:00-5:20):**

| Time | Section |
|---|---|
| 4:00-4:25 | 1. Finish backtracking (continue in Week 5, Day 1) |
| 4:25-4:30 | 2. Review: recurrences |
| 4:30-5:00 | 3. Review: counting inversions |
| 5:00-5:10 | 4. Review: social permutations |
| 5:10-5:15 | 5. Recap |
| 5:15-5:20 | Buffer |

<details>
<summary>1. Finish backtracking (4:00-4:25)</summary>

Last session ran out of time before reaching Subsets' complexity and before starting Permutations.
Pick up directly in [Week 5, Day 1](week05_day1.md): finish §2 Subsets' **Complexity** block, then
work through all of §3 **Permutations** (concept, your turn, correctness, complexity).

Everything below assumes that's done: Social Permutations, later in this session, builds directly
on the Permutations backtracking skeleton.

</details>

<details>
<summary>2. Review: recurrences (4:25-4:30)</summary>

Three Master Theorem applications, straight out of [Week 3, Day 1](week03_day1.md)'s toolbox. For
each, identify `a`, `b`, and `f(n)`, then compare `f(n)` against `n^(log_b a)`.

a) `T(n) = 3T(n/3) + n, T(1) = 1`

b) `T(n) = 3T(n/2) + n, T(1) = 1`

c) `T(n) = 7T(n/2) + n^2, T(1) = 1`

<details>
<summary>Hints</summary>

1. Compute `n^(log_b a)` for each: it's `n^1`, `n^(log_2 3)`, and `n^(log_2 7)`, respectively.
2. Compare that against `f(n)`. Matching growth rates means Case 2; `n^(log_b a)` growing strictly
   faster means Case 1.
3. None of these three need Case 3's regularity condition.

</details>

<details>
<summary>Solution</summary>

a) `a = 3, b = 3, f(n) = n`. `n^(log_3 3) = n`, matching `f(n)`: **Case 2**, so
`T(n) = Θ(n log n)`. Same complexity (and Case 2 matching) as Merge Sort.

b) `a = 3, b = 2, f(n) = n`. `n^(log_2 3) ≈ n^1.585`, growing strictly faster than `f(n) = n`:
**Case 1**, so `T(n) = Θ(n^(log_2 3))`.

c) `a = 7, b = 2, f(n) = n^2`. `n^(log_2 7) ≈ n^2.807`, growing strictly faster than
`f(n) = n^2`: **Case 1**, so `T(n) = Θ(n^(log_2 7))`. This is Strassen's matrix-multiplication
recurrence.

</details>

<details>
<summary>References</summary>

- Cormen et al., *Introduction to Algorithms*, §4.5 "The master method for solving recurrences"
  (pp. 93-97), already cited in [Week 3, Day 1](week03_day1.md): its exercises are good extra
  practice for this kind of case-matching.

</details>

<details>
<summary>Extra practice</summary>

A Case 3 example, to cover the one case none of the three above land in:
`T(n) = 2T(n/2) + n^2`.

`a = 2, b = 2, f(n) = n^2`. `n^(log_2 2) = n`, so `f(n) = n^2` grows strictly faster: **Case 3**.
Regularity condition: `a * f(n/b) = 2(n/2)^2 = n^2 / 2 <= c * f(n)` holds with `c = 1/2 < 1`.
So `T(n) = Θ(n^2)`.

</details>

</details>

<details>
<summary>3. Review: counting inversions (4:30-5:00)</summary>

An **inversion** in an array `A[0:n]` is a pair of indices `(i, j)` with `i < j` and
`A[i] > A[j]`. A sorted array has 0 inversions; a reverse-sorted array has `C(n, 2)`, the maximum
possible.

**Part a (10 pt).** Assume `A[0:n/2]` and `A[n/2:n]` are both already sorted ascending. Count the
inversions in all of `A[0:n]` in `O(n)` time. Briefly argue correctness and time complexity.

**Part b (24 pt).** `A[0:n]` is unsorted. Count its inversions with an `O(n log n)`
divide-and-conquer algorithm. Prove correctness and analyze time complexity.

<details>
<summary>Hints</summary>

1. Part a is the merge step from [Merge Sort](../algorithm_implementation/merge-sort/): two
   pointers, one per half, always take the smaller front element.
2. When the merge takes from the right half before the left is exhausted, every element still
   sitting in the left half is bigger than the one just taken (the left half is sorted) and
   appears earlier (it's still in the left half): each one forms an inversion with it. Count that
   whole remaining stretch at once, not one pair at a time, to stay `O(n)`.
3. Part b is part a laid on top of Merge Sort's own recursion: count inversions in the left half,
   count them in the right half, then merge-and-count the two halves together for the cross
   inversions.

</details>

**Solution:** [`solution.py`](../problem_solutions/counting-inversions/solution.py) /
[`solution.cpp`](../problem_solutions/counting-inversions/solution.cpp), written up in
[`problem_solutions/counting-inversions/`](../problem_solutions/counting-inversions/).

```
// counts inversions between the already-sorted A[lo:mid] and A[mid:hi],
// while merging them into one sorted A[lo:hi]
function merge_and_count(A, lo, mid, hi):
    i = lo; j = mid; inversions = 0
    C = []
    while i < mid and j < hi:
        if A[i] <= A[j]:
            append A[i] to C; i = i + 1
        else:
            append A[j] to C; j = j + 1
            inversions = inversions + (mid - i)      // every remaining A[i:mid] beats A[j]
    append the remaining elements of A[i:mid] and A[j:hi] to C
    copy C back into A[lo:hi]
    return inversions

// counts inversions in A[lo:hi], sorting it in place along the way
function count_inversions(A, lo, hi):
    if hi - lo <= 1: return 0                         // base case: 0 or 1 elements, no inversions

    mid = lo + (hi - lo) / 2
    inversions = count_inversions(A, lo, mid)
    inversions = inversions + count_inversions(A, mid, hi)
    inversions = inversions + merge_and_count(A, lo, mid, hi)
    return inversions
```

<details>
<summary>Correctness</summary>

**Claim:** for every `lo <= hi`, `count_inversions(A, lo, hi)` returns the number of inversions in
`A[lo:hi]`, and leaves `A[lo:hi]` sorted ascending.

**Base case:** `hi - lo <= 1`. A range of 0 or 1 elements has no pair of indices at all, so it has
0 inversions and is trivially sorted. That's the `return 0` line.

**Assume:** `count_inversions` is correct, in the sense of the Claim, for every range shorter than
`A[lo:hi]`.

**Show:** `A[lo:hi]` has more than one element, so split it at `mid` into `A[lo:mid]` and
`A[mid:hi]`, both strictly shorter. By **Assume**, the two recursive calls return the exact
inversion counts within each half and leave both halves sorted. Every inversion in `A[lo:hi]` is
one of exactly three kinds: both indices in `A[lo:mid]` (counted by the first call), both in
`A[mid:hi]` (counted by the second), or one in each (a **cross inversion**). `merge_and_count`
counts cross inversions exactly: since both halves are now sorted, whenever it takes `A[j]` from
the right half before the left is exhausted, `A[j]` is smaller than every element still remaining
in `A[i:mid]` (the left half is sorted ascending, so nothing later in it could be smaller), and
every one of those remaining elements sits at a smaller index than `j`, so each forms a cross
inversion with `A[j]`. Adding `mid - i` counts exactly that batch, and it's also exactly the
standard merge routine, so `A[lo:hi]` ends up sorted too. Summing the three counts (the two from
**Assume**, plus this merge's cross count) gives the total inversions in `A[lo:hi]`.

Base case and Show together cover every range, so the Claim holds, and in particular
`count_inversions(A, 0, n)` returns the total inversions in `A[0:n]`.

</details>

<details>
<summary>Complexity</summary>

Same recurrence as Merge Sort: `T(n) = 2T(n/2) + O(n)` (the `O(n)` is `merge_and_count`, a linear
scan doing `O(1)` work per element). By the Master Theorem, Case 2 from the recurrence review
above, `T(n) = Θ(n log n)`. Space: `O(n)` for the auxiliary buffer, plus `O(log n)` for the
recursion stack, same as Merge Sort.

</details>

<details>
<summary>Extra practice</summary>

- GeeksforGeeks, "Counting Inversions": the classic version of exactly this problem.
- [LeetCode 493, Reverse Pairs](https://leetcode.com/problems/reverse-pairs/) (Hard): same
  divide-and-conquer-during-merge idea, harder condition (`A[i] > 2 * A[j]`).
- [LeetCode 315, Count of Smaller Numbers After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/)
  (Hard): same technique, but needs a count per index instead of one running total.
- [LeetCode 775, Global and Local Inversions](https://leetcode.com/problems/global-and-local-inversions/)
  (Medium): a much easier warm-up with a different, non-divide-and-conquer angle.

</details>

</details>

<details>
<summary>4. Review: social permutations (5:00-5:10)</summary>

`N` people, labeled `0` through `N - 1`, each give exactly one gift and receive exactly one gift:
a permutation `p`, where `p[i]` is who person `i` gives to. Call `p` **social** if:

- `p[i] != i` for every `i` (no self-gift), and
- there's no pair `i, j` with `p[i] = j` and `p[j] = i` (no mutual gift).

Write a recursive backtracking algorithm that **prints** every social permutation for a given `N`,
using no more than `O(n)` memory.

<details>
<summary>Hints</summary>

1. Start from [Permutations](week05_day1.md)' skeleton: build the permutation one position at a
   time, tracking which values are already used.
2. Add a check before recursing into each candidate value: reject it if it's a self-gift, or if it
   would complete a mutual pair with a position already filled.
3. The mutual-gift check only ever needs to look backward, at positions already decided. A forward
   conflict gets caught later, symmetrically, when the recursion reaches that later position.

</details>

**Solution:** [`solution.py`](../problem_solutions/social-permutations/solution.py) /
[`solution.cpp`](../problem_solutions/social-permutations/solution.cpp), written up in
[`problem_solutions/social-permutations/`](../problem_solutions/social-permutations/).

```
// fills p[index:] and, once every position is filled, prints one social permutation
function backtrack(n, index, p, used):
    if index == n:
        print p
        return

    for v from 0 to n - 1:
        if used[v] or v == index:
            continue                                    // v already placed, or self-gift

        if v < index and p[v] == index:
            continue                                     // p[v] already points back: mutual gift

        p[index] = v
        used[v] = true
        backtrack(n, index + 1, p, used)
        used[v] = false                                  // undo: "backtrack"
```

<details>
<summary>Correctness</summary>

**Claim:** for every `index` and every assignment of `p[0:index]` that is social so far (distinct
values, none equal to its own position, no mutual pair among positions `< index`), with `used`
marking exactly those values, `backtrack(n, index, p, used)` prints every way to fill
`p[index:n]` that extends `p[0:index]` into a full social permutation, exactly once each, and
leaves `p[0:index]` and `used` unchanged when it returns.

**Base case:** `index == n`. `p` is fully assigned and, by the precondition, social throughout, so
there's exactly one completion, the empty one, and the Claim says exactly one print should happen:
`p` itself. That's the `print p` line, and nothing after it touches `p` or `used`.

**Assume:** the Claim holds at `index + 1`, for any social partial assignment there.

**Show:** for `index < n`, the loop tries every `v` from `0` to `n - 1`. It skips `v` already in
`used` (a permutation can't repeat a value), `v == index` (self-gift), and
`v < index and p[v] == index` (setting `p[index] = v` here would make `p[v] = index` and
`p[index] = v` a mutual pair). For every `v` that survives: setting `p[index] = v` and
`used[v] = true` extends the assignment to length `index + 1`, and it's still social, since the
first two checks rule out a self-gift at `index` and the third rules out a mutual pair with any
earlier position (positions after `index` aren't assigned yet, so they can't yet violate
anything). By **Assume**, the recursive call prints every completion of that longer assignment,
exactly once each, and restores `p[0:index+1]` and `used`. `used[v] = false` then undoes this
iteration's change, restoring `used` to what it was before it.

Every social completion of `p[0:index]` picks some value for position `index`, and that value must
be unused, not equal to `index`, and not create a mutual pair with an earlier position, since
otherwise the completion wouldn't be social. So it's exactly one of the `v` the loop doesn't skip.
Across every non-skipped `v`, the loop therefore prints every social completion of `p[0:index]`,
exactly once each: the Claim at `index`.

By induction (downward from `index = n`), the Claim holds at `index = 0` with `p` empty and `used`
all false (vacuously social), so the initial call prints every social permutation of `n` people,
exactly once.

</details>

<details>
<summary>Complexity</summary>

**Question for the class:** why doesn't this need `O(n * n!)` space the way Permutations did?

<details>
<summary>Answer</summary>

Permutations *collects* every ordering into an output list, copying `chosen` at each of its `n!`
leaves. This algorithm only *prints* each one as it's found, so there's nothing to copy or hold
onto: `p` and `used` are both size `n`, reused across the whole recursion, and the recursion stack
goes `n` frames deep. Space: `O(n)`.

</details>

Time is bounded above by Permutations' `O(n * n!)` (the pruning only ever skips work, never adds
any), but it's a loose bound: the extra checks prune out every permutation with a self-gift or a
mutual pair, so the real leaf count is smaller, just not smaller by more than a constant factor
asymptotically.

</details>

<details>
<summary>Extra practice</summary>

- [LeetCode 51, N-Queens](https://leetcode.com/problems/n-queens/) (Hard): same shape,
  backtracking with an `O(1)` pruning check per candidate before recursing.
- [LeetCode 47, Permutations II](https://leetcode.com/problems/permutations-ii/) (Medium): a
  gentler pruning warm-up, avoiding duplicate branches instead of unsocial ones.
- GeeksforGeeks, "Count Derangements": the version of this problem without the no-mutual-pair
  rule, useful for isolating which constraint does what.

</details>

</details>

<details>
<summary>5. Recap (5:10-5:15)</summary>

- Subsets and Permutations, finished from last session: two backtracking skeletons, fixed
  branching factor vs. shrinking branching factor, `O(n * 2^n)` and `O(n * n!)` time
  respectively, both `O(n)` space excluding the output.
- Recurrences: identify `a`, `b`, `f(n)`, compare `f(n)` to `n^(log_b a)`, read off the Master
  Theorem case.
- Counting inversions: Merge Sort's own merge step, counted in bulk instead of one pair at a
  time, `O(n log n)` overall by the same recurrence as Merge Sort itself.
- Social permutations: Permutations' skeleton plus one backward-looking pruning check, `O(n)`
  memory since it prints instead of collecting.
- Every proof today, recurrences aside, used the same shape: **Claim**, **Base case**,
  **Assume**, **Show**.

</details>
