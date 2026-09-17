# Week 04, Day 1 (September 15, 2026)

## Today

Every solution so far has scanned its input once, start to end, recursion aside. Today's problem
starts with that same scan, search for a target in an array, and asks whether being handed a
**sorted** array should change the answer. It does, and the change is Binary Search.

<details>
<summary>1. The baseline: linear search</summary>

**Problem:** given an array `nums` and a `target`, return the index of `target` in `nums`, or
`-1` if it isn't there.

The only thing you can do to an array you know nothing about is look at every element:

```
function linear_search(nums, target):
    for i from 0 to len(nums) - 1:
        if nums[i] == target:
            return i
    return -1
```

**Correctness.** If `target` is at index `i`, the loop reaches `i` before returning (nothing
earlier matched), and returns it. If `target` isn't anywhere in `nums`, the loop checks every
index and finds nothing, so it falls through to `-1`. There's no recursive case here, so there's
nothing to induct on beyond that.

**Complexity.** Worst case (`target` at the last index, or missing entirely) checks all `n`
elements: `O(n)` time, `O(1)` space.

</details>

<details>
<summary>2. Is O(n) actually a problem?</summary>

**Question for the class:** one search, `O(n)`. Is that bad?

<details>
<summary>Answer: not by itself</summary>

No. `O(n)` is about as cheap as touching the data at all; you can't answer "is `target` in here"
without looking at it in some form.

</details>

**Question for the class:** now suppose the array doesn't change, but you're asked `Q` searches
against it, one target at a time. What does that cost?

<details>
<summary>Answer: O(Q * n)</summary>

Linear search doesn't remember anything between calls, so each of the `Q` searches pays the full
`O(n)` again: `O(Q * n)` total. For a fixed array and a large number of queries, that's the part
worth fixing: is there a way to spend some effort once, up front, so each search after that is
cheaper than `O(n)`?

</details>

</details>

<details>
<summary>3. What sorted buys you for free</summary>

Suppose `nums` is sorted in ascending order (spending `O(n log n)` once to sort it, if it wasn't
already, is exactly the "effort up front" from the question above).

**Question for the class:** without touching anything but `nums[0]` and `nums[n-1]`, the first
and last elements, can you tell in `O(1)` whether `target` is *definitely not* in `nums`?

<details>
<summary>Answer</summary>

Yes. `nums` sorted means `nums[0]` is the minimum and `nums[n-1]` is the maximum of the whole
array. If `target < nums[0]` or `target > nums[n-1]`, `target` is outside the range every element
falls in, so it can't be anywhere in `nums`. One comparison on each end, `O(1)`.

That's the payoff of "sorted" that linear search never gets to use: it tells you something about
elements you haven't looked at yet.

</details>

**Question for the class:** that check only fires when `target` is out of range. What about when
`nums[0] <= target <= nums[n-1]`? The check says nothing there, `target` might or might not be in
`nums`. Can the same "learn something without checking every element" idea narrow that down too?

<details>
<summary>Answer: yes, recursively</summary>

Look at the middle element, `nums[mid]`. Sorted tells you everything to its left is `<= nums[mid]`
and everything to its right is `>= nums[mid]`, so comparing `target` against that split rules out
one whole half in `O(1)`, no need to look inside it. That leaves a search over a range half the
size, the same problem, smaller: divide and conquer.

</details>

</details>

<details>
<summary>4. Binary Search</summary>

[LeetCode 704](https://leetcode.com/problems/binary-search/description/): given `nums` sorted
ascending with distinct values, and a `target`, return `target`'s index, or `-1`. Required time:
`O(log n)`.

**Your turn.** Write it as a recursive function over an index range `[left, right]`.

<details>
<summary>Hints</summary>

1. This is divide and conquer over the range `[left, right]`, not over the array itself: shrink
   the range, don't copy pieces of the array.
2. Base case: what should happen when the range is empty, `left > right`? What about when it's
   down to a single index, `left == right`?
3. Recursive case: pick `mid` inside `[left, right]`. Since the range is sorted, every value in
   `nums[left..mid]` is `<= nums[mid]`, and every value in `nums[mid+1..right]` is `> nums[mid]`.
   Compare `target` against that range of values, not just against `nums[mid]`, to decide which
   half to recurse into.
4. Whichever half you pick, the other one is thrown away completely, the same way the "bad
   character" split threw away a whole side of the string in Longest Nice Substring.

</details>

**Solution:** [`solution.py`](../problem_solutions/binary-search/solution.py) /
[`solution.cpp`](../problem_solutions/binary-search/solution.cpp), written up in
[`problem_solutions/binary-search/`](../problem_solutions/binary-search/).

```
function search_recursive(nums, target, left, right):
    if left > right:
        return -1                                          // base case: empty range

    if left == right:
        return left if nums[left] == target else -1        // base case: one element

    mid = (left + right) // 2
    if target >= nums[left] and target <= nums[mid]:
        return search_recursive(nums, target, left, mid)    // target's value fits the left half

    return search_recursive(nums, target, mid + 1, right)   // otherwise it can only be on the right
```

</details>

<details>
<summary>5. Why it's correct</summary>

Assume throughout that `nums[left..right]` is sorted ascending. (LeetCode 704 guarantees the
whole array is sorted with distinct values; that's inherited by every sub-range.)

**Claim:** `search_recursive(nums, target, left, right)` returns an index `i` with
`left <= i <= right` and `nums[i] == target` if such an index exists, and `-1` otherwise.

**Base case:** two of them, both direct.

- `left > right`: the range is empty, no index satisfies `left <= i <= right`, so `-1` is
  correct. This is the `if left > right: return -1` line.
- `left == right`: the range is one index. `target` is there exactly when `nums[left] == target`,
  which is exactly what's returned.

**Assume:** the Claim holds for every range strictly smaller than `[left, right]`. (Strong
induction on range size, same reason as [Longest Nice Substring](week03_day1.md): the two
sub-ranges below are different sizes in general, not "one smaller".)

**Show:** for `left < right`, `mid` is chosen with `left <= mid < right`. Because
`nums[left..right]` is sorted:

- every value in `nums[left..mid]` is `<= nums[mid]`
- every value in `nums[mid+1..right]` is `> nums[mid]` (values are distinct and ascending, so the
  first element past `mid` is already strictly bigger)

So the two halves' values don't overlap: nothing in the right half is `<= nums[mid]`, and nothing
in the left half is `> nums[mid]`.

- If `nums[left] <= target <= nums[mid]`: were `target` to appear in the right half, its value
  would have to be `> nums[mid]`, contradicting `target <= nums[mid]`. So if `target` is in
  `nums[left..right]` at all, it's in `nums[left..mid]`. That range is smaller than
  `[left, right]`, so by **Assume**, `search_recursive(nums, target, left, mid)` returns exactly
  what the Claim promises for it, which is what the Claim promises here too.
- Otherwise (`target < nums[left]` or `target > nums[mid]`): `target`'s value doesn't fit
  `nums[left..mid]` (every value there is between `nums[left]` and `nums[mid]`), so if `target` is
  anywhere in `nums[left..right]`, it's in `nums[mid+1..right]`. Same argument, by **Assume**, on
  the other call.

Either branch reduces to a strictly smaller range and hands off to **Assume**, so by induction the
Claim holds for every range, including the full array.

**Question for the class:** what happens when `target < nums[left]`, meaning `target` isn't in
`nums[left..right]` at all? The code doesn't check that case up front, unlike the `O(1)` endpoint
check from section 3.

<details>
<summary>Answer</summary>

The first branch's condition, `target >= nums[left]`, is false, so it takes the second branch and
recurses into `nums[mid+1..right]`. The recursion keeps shrinking the range until it hits a base
case and correctly returns `-1`. It costs a few extra calls compared to bailing out immediately,
but it never returns a wrong answer; the endpoint check from section 3 is a nice `O(1)`
short-circuit you could bolt on in front, not something the recursion depends on for correctness.

</details>

</details>

<details>
<summary>6. Complexity</summary>

**Question for the class:** how many indices does a range of size `s = right - left + 1` hand to
each recursive call?

<details>
<summary>Answer</summary>

`mid = left + (s - 1) // 2`. The left half, `[left, mid]`, has `mid - left + 1` indices, which
works out to `ceil(s / 2)`. The right half, `[mid + 1, right]`, has the rest, `floor(s / 2)`.
Either way, exactly one call is made, on a range at most `ceil(s / 2)`, roughly half of `s`.

</details>

**Question for the class:** each call does a constant amount of work (one `mid`, two comparisons)
before making exactly one recursive call on roughly half the range. Write that as a recurrence,
and solve it.

<details>
<summary>Answer</summary>

```
T(n) = T(n / 2) + O(1)
```

Master Theorem: `a = 1`, `b = 2`, `f(n) = O(1) = O(n^0)`. `n^(log_b a) = n^(log_2 1) = n^0`, the
same as `f(n)`, so this is **case 2**:

```
T(n) = O(n^0 * log n) = O(log n)
```

Contrast with [Merge Sort](../algorithm_implementation/merge-sort/README.md) and
[Longest Nice Substring](week03_day1.md), also case 2, but with `a = 2` recursive calls instead of
`1`: that's why those come out to `O(n log n)` and this comes out to `O(log n)`. Same case,
different `a`.

**Time: `O(log n)`.** For `Q` queries against the same sorted array, that's `O(Q log n)` total,
against linear search's `O(Q * n)`; a large `Q` is exactly when that gap matters.

**Space:** each call holds only `left`, `right`, and `target`, no copying, but the call stack is
one frame deep per halving: `O(log n)` frames. `O(log n)` space, against linear search's `O(1)`
(no recursion at all). Binary search trades a bit of space for a large amount of time, in the
regime where `Q` is large.

</details>

</details>

<details>
<summary>7. Recap</summary>

- Linear search: `O(n)` per query, and it forgets everything between queries, so `Q` queries cost
  `O(Q * n)`.
- A sorted array answers questions about ranges of values, not just single elements: checking the
  two endpoints tells you "definitely not here" in `O(1)`.
- Binary search extends that idea recursively: pick `mid`, decide which half's value range could
  contain `target`, throw the other half away, recurse. Same divide and conquer shape as
  [Longest Nice Substring](week03_day1.md), splitting on a range of values instead of on a bad
  character.
- Correctness doesn't need an `if target == nums[mid]` shortcut; showing the two halves' value
  ranges can't overlap is enough, and the recursion still terminates correctly even when `target`
  isn't in the array at all.
- `T(n) = T(n/2) + O(1)` is Master Theorem case 2 with `a = 1`, giving `O(log n)` time,
  `O(log n)` space for the recursion stack. `Q` queries: `O(Q log n)`, against `O(Q * n)` for
  linear search.

</details>
