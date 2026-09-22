# Week 05, Day 1 (September 21, 2026)

## Today

So far, every problem asked for one answer: an index, a boolean, a sorted position. Today's
problems ask for *every* valid answer: every subset, every ordering. That needs a different tool
than divide and conquer's "throw half away": backtracking explores every choice and undoes each
one before trying the next, turning last week's recursion into a decision tree instead of a
narrowing range.

**Session plan (4:00-5:20):**

| Time | Section |
|---|---|
| 4:00-4:10 | 1. Exploring instead of narrowing |
| 4:10-4:40 | 2. Subsets |
| 4:40-5:05 | 3. Permutations |
| 5:05-5:15 | 4. Recap |
| 5:15-5:20 | Buffer |

<details>
<summary>1. Exploring instead of narrowing (4:00-4:10)</summary>

Binary search picks *one* of two halves to recurse into and discards the other, so the recursion
visits `O(log n)` nodes total. Today's problems need every combination of choices to show up in
the output, so the recursion has to explore *every* branch at every decision, not just one. That's
the "explore" half of backtracking. The other half, "backtrack," is undoing a choice (popping it
back off a shared list) once its branch is fully explored, so the same variables get reused for
the next branch instead of copying state at every call.

**Question for the class:** if a recursive call tries every one of `k` choices at each step, and
makes a fresh recursive call after each one, how does the size of the recursion tree grow with the
number of decisions made?

<details>
<summary>Answer</summary>

Exponentially: with `d` decisions and `k` choices each, the tree has `k^d` leaves. This is why
"generate every X" problems typically can't beat exponential time: the output itself can be
exponentially large, and the recursion has to visit every leaf to produce it. Both problems below
have this shape, `k = 2` for one, `k` shrinking by one each level for the other.

</details>

</details>

<details>
<summary>2. Subsets (4:10-4:40)</summary>

[LeetCode 78](https://leetcode.com/problems/subsets/): given an array `nums` of `n` unique
integers, return every possible subset (the power set), in any order.

**Question for the class:** how many subsets does an `n`-element array have?

<details>
<summary>Answer</summary>

`2^n`. Every element is independently either in a given subset or not, `n` independent binary
choices, `2 * 2 * ... * 2` (`n` times).

</details>

**Your turn.** Since the answer is "for every element, decide in or out," write a recursive
function that walks `nums` index by index, keeping a `chosen` list of what's "in" so far.

<details>
<summary>Hints</summary>

1. Base case: what should happen once `index` has walked past every element of `nums`?
2. `chosen` is a single list reused across the whole recursion, not copied per call. When it fully
   describes a subset (the base case), save a *copy* of it, since `chosen` keeps changing after
   that point.
3. Recursive case: try leaving `nums[index]` out of `chosen` first (recurse), then try putting it
   in (append, recurse, then remove it again) before returning. That removal is what lets the same
   `chosen` list serve both branches.

</details>

**Solution:** [`solution.py`](../problem_solutions/subsets/solution.py) /
[`solution.cpp`](../problem_solutions/subsets/solution.cpp), written up in
[`problem_solutions/subsets/`](../problem_solutions/subsets/).

```
function backtrack(nums, index, chosen, subsets):
    if index == len(nums):
        subsets.append(copy of chosen)              // chosen fully decided: record it
        return

    backtrack(nums, index + 1, chosen, subsets)       // leave nums[index] out

    chosen.append(nums[index])                        // put nums[index] in
    backtrack(nums, index + 1, chosen, subsets)
    chosen.pop()                                       // undo it: "backtrack"
```

<details>
<summary>Correctness</summary>

**Claim:** for every `index` and every `chosen`, calling `backtrack(nums, index, chosen, subsets)`
appends `chosen + s` to `subsets`, for every subset `s` of `nums[index:]`, exactly once each, and
leaves `chosen` unchanged once it returns.

**Base case:** `index == len(nums)`. `nums[index:]` is empty, and its only subset is the empty
set, so the Claim says exactly one entry, `chosen` itself, should be appended. That's the
`subsets.append(...)` line, and nothing else modifies `chosen`.

**Assume:** the Claim holds for `index + 1`, for any `chosen`.

**Show:** for `index < len(nums)`, the call makes two recursive calls, both at `index + 1`.

- The first, `backtrack(nums, index + 1, chosen, subsets)`, runs before `chosen` is touched. By
  **Assume**, it appends `chosen + s` for every subset `s` of `nums[index+1:]`, exactly once each,
  and restores `chosen` to what it was. These are exactly the subsets of `nums[index:]` that
  *don't* contain `nums[index]`.
- `nums[index]` is then appended to `chosen`, and the second call runs with that longer `chosen`.
  By **Assume** again, it appends `chosen + [nums[index]] + s` for every subset `s` of
  `nums[index+1:]`, exactly once each, and restores that longer `chosen`. These are exactly the
  subsets of `nums[index:]` that *do* contain `nums[index]`.
- `chosen.pop()` then removes `nums[index]`, restoring `chosen` to its original value.

Every subset of `nums[index:]` either contains `nums[index]` or doesn't, and not both, so the two
calls together append every subset of `nums[index:]` extended onto `chosen`, exactly once each,
and `chosen` ends up unchanged: exactly the Claim at `index`.

By induction (downward from `len(nums)`), the Claim holds at `index = 0` with `chosen = []`, so
the initial call appends every subset of `nums`, exactly once.

</details>

<details>
<summary>Complexity</summary>

**Question for the class:** how many leaves does this recursion tree have, and how many calls
total?

<details>
<summary>Answer</summary>

`2^n` leaves, one per subset, by the Correctness argument. The tree is a full binary tree of depth
`n`, so `2^(n+1) - 1` calls total, still `O(2^n)`.

</details>

**Time:** every call does `O(1)` work of its own (an append/pop, a comparison), except the base
case, which pays `O(n)` to copy `chosen`. There are `2^n` base cases, so copying dominates:
**`O(n * 2^n)`**.

**Space:** the recursion stack goes `n` frames deep, and `chosen` never holds more than `n`
elements: **`O(n)`**, not counting the output itself, which takes `O(n * 2^n)` to hold every
subset.

</details>

</details>

<details>
<summary>3. Permutations (4:40-5:05)</summary>

[LeetCode 46](https://leetcode.com/problems/permutations/): given an array `nums` of `n` distinct
integers, return every possible ordering (permutation) of them, in any order.

**Question for the class:** how many permutations does an `n`-element array have?

<details>
<summary>Answer</summary>

`n!`. The first slot can be any of the `n` elements, the second any of the remaining `n - 1`, the
third any of the remaining `n - 2`, and so on down to `1` choice for the last slot:
`n * (n - 1) * ... * 1`.

</details>

Contrast with Subsets: there, every element got exactly one yes/no decision, branching factor `2`
the whole way down. Here, the branching factor itself shrinks, `n` choices for the first slot,
`n - 1` for the second, since whichever element got used first is no longer available.

**Your turn.** Track which elements are still available with a `used` array (parallel to `nums`),
and a `chosen` list for the ordering built so far.

<details>
<summary>Hints</summary>

1. Base case: what does it mean for `chosen` to already be a full permutation?
2. Recursive case: loop over every index `i` in `nums`, skipping any already `used`. For each one:
   mark it used, append `nums[i]` to `chosen`, recurse, then undo both (pop `chosen`, clear
   `used[i]`) before the loop moves to its next `i`.
3. That undo is what lets the same `chosen` and `used` serve every iteration of the loop, not just
   the whole call: without it, the second iteration would see leftover state from the first.

</details>

**Solution:** [`solution.py`](../problem_solutions/permutations/solution.py) /
[`solution.cpp`](../problem_solutions/permutations/solution.cpp), written up in
[`problem_solutions/permutations/`](../problem_solutions/permutations/).

```
function backtrack(nums, used, chosen, permutations):
    if len(chosen) == len(nums):
        permutations.append(copy of chosen)          // chosen uses every element: record it
        return

    for i from 0 to len(nums) - 1:
        if used[i]:
            continue                                   // nums[i] is already placed earlier

        used[i] = true
        chosen.append(nums[i])
        backtrack(nums, used, chosen, permutations)
        chosen.pop()                                    // undo: "backtrack"
        used[i] = false
```

<details>
<summary>Correctness</summary>

**Claim:** for every `chosen` and `used`, calling `backtrack(nums, used, chosen, permutations)`
appends `chosen + p` to `permutations`, for every permutation `p` of the elements with
`used[i] == false`, exactly once each, and leaves `chosen` and `used` unchanged once it returns.

**Base case:** `len(chosen) == len(nums)`. Every element is used (`chosen` only ever grows when an
element is marked used, and it has `n` entries now), so there are no unused elements left, and the
only permutation of an empty set is the empty ordering. The Claim says exactly one entry, `chosen`
itself, gets appended, which is the `permutations.append(...)` line.

**Assume:** the Claim holds whenever `chosen` is one element longer (equivalently, one fewer
element is unused) than in the case being shown.

**Show:** for `len(chosen) < len(nums)`, the loop considers every index `i` with
`used[i] == false` in turn (skipping the rest). For each such `i`:

- `used[i]` is set true and `nums[i]` appended to `chosen`, giving a `chosen` one longer, with
  `nums[i]` no longer among the unused elements.
- The recursive call, by **Assume**, appends `chosen + [nums[i]] + p` for every permutation `p` of
  the elements unused *after* excluding `nums[i]`, exactly once each, and restores that longer
  `chosen` and the updated `used`.
- `chosen.pop()` and `used[i] = false` then undo both changes, restoring `chosen` and `used` to
  what they were before this iteration.

Every permutation of the currently-unused elements starts with exactly one of those elements, so
as `i` ranges over every currently-unused index, the appended entries `chosen + [nums[i]] + p`
cover every permutation of the unused elements, extended onto `chosen`, exactly once each. Each
iteration restores `chosen` and `used` before the next one starts, so after the loop finishes they
match the Claim.

By induction (downward from `len(chosen) == len(nums)`), the Claim holds for `chosen = []` and
`used` all false, so the initial call appends every permutation of `nums`, exactly once.

</details>

<details>
<summary>Complexity</summary>

**Question for the class:** how many leaves does this recursion tree have?

<details>
<summary>Answer</summary>

`n!`, one call per permutation, by the Correctness argument. Unlike Subsets, the tree isn't a full
binary tree: it's `n`-ary at the root, `(n - 1)`-ary at the next level, down to `1`-ary at the
last, which comes out to exactly `n!` leaves and, summed across levels, `O(n * n!)` calls total.

</details>

**Time:** every call does `O(n)` work of its own (the loop over `nums`), but this is dominated by
the same `O(n)` copy at each of the `n!` base cases: **`O(n * n!)`**.

**Space:** the recursion stack goes `n` frames deep, and `chosen` and `used` never exceed size
`n`: **`O(n)`**, not counting the `O(n * n!)` output.

</details>

</details>

<details>
<summary>4. Recap (5:05-5:15)</summary>

- "Find one answer" (binary search, matrix search) narrows a range and throws half away; "find
  every answer" (today) has to explore every branch, since the output itself is exponentially
  large.
- Backtracking's skeleton: make a choice, recurse, undo the choice before trying the next one.
  Subsets and Permutations use the same skeleton with a different notion of "choice": Subsets
  decides each element's in/out status once, in a fixed order, so the branching factor is always
  `2`. Permutations decides which unused element goes next, so the branching factor shrinks by one
  each level.
- Both proofs follow the same shape as every recursive proof so far, **Claim**, **Base case**,
  **Assume**, **Show**, just with the Claim describing a set of entries appended to an output list
  instead of a single returned value.
- Subsets: `O(n * 2^n)` time, `O(n)` space (excluding output). Permutations: `O(n * n!)` time,
  `O(n)` space (excluding output). Both are dominated by the `O(n)` cost of copying `chosen` at
  every leaf, since there's one leaf per item in the output.

</details>
