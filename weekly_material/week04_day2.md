# Week 04, Day 2 (September 17, 2026)

## Today

Yesterday's binary search was recursive. Today we write the same idea as a loop, prove it correct
with a different tool than induction, and then reuse it, unchanged, to solve a matrix search
problem that turns out to be the same problem in disguise.

<details>
<summary>1. From recursion to a loop</summary>

Yesterday's `search_recursive` narrowed a range `[left, right]` by comparing `target` against the
*value range* `nums[left]` through `nums[mid]`. There's a more common shape for binary search:
compare `target` directly against `nums[mid]` and let that single comparison decide everything.

```
function binary_search(nums, target):
    left, right = 0, len(nums) - 1

    while left <= right:
        mid = (left + right) // 2

        if nums[mid] == target:
            return mid
        elif nums[mid] < target:
            left = mid + 1
        else:
            right = mid - 1

    return -1
```

No recursive call, no call stack, just `left` and `right` walking toward each other. This is the
version you'll see in most references, and it's the one we'll build on for the rest of today.

</details>

<details>
<summary>2. Why it's correct: loop invariants</summary>

There's no base case or recursive case here to induct on, it's a loop. The matching tool is a
**loop invariant**: a statement about `left` and `right` that's true before the loop starts, stays
true across every iteration, and, combined with the reason the loop stops, tells you the answer
is correct.

It has three parts, and they play the same roles **Base case**, **Assume**, and **Show** play for
recursion: one part anchors the argument, one part carries it forward one step, one part cashes it
in when the process ends.

**Claim (the invariant):** at the start of every iteration, if `target` is in `nums`, it's in
`nums[left..right]`.

**Initialization:** before the first iteration, `left = 0` and `right = len(nums) - 1`, so
`nums[left..right]` is the whole array. If `target` is in `nums` at all, it's trivially in the
whole array. This is the state right before the `while` line runs.

**Maintenance:** assume the Claim holds at the start of some iteration; show it still holds at the
start of the next one. The iteration computes `mid` and does one of three things:

- `nums[mid] == target`: returns `mid` immediately. Correct on the spot, nothing to maintain.
- `nums[mid] < target`: since `nums` is sorted, everything at index `<= mid` is `<= nums[mid] <
  target`, so `target` can't be at any of those indices. If `target` is in `nums[left..right]`
  (the Claim), it must be in `nums[mid+1..right]`. Setting `left = mid + 1` makes the Claim true
  again for the next iteration.
- `nums[mid] > target`: symmetric. `target` can't be at index `>= mid`, so if it's anywhere in
  `nums[left..right]`, it's in `nums[left..mid-1]`. Setting `right = mid - 1` maintains the Claim.

**Termination:** the loop exits when `left > right`, meaning `nums[left..right]` is empty. By the
Claim, if `target` were in `nums`, it would be in that empty range, which is impossible. So
`target` is not in `nums`, and returning `-1` is correct.

Every exit is covered: the early `return mid` is correct by construction, and falling out of the
loop is correct by **Termination**. That's the whole proof.

</details>

<details>
<summary>3. Complexity</summary>

**Time.** Each iteration is `O(1)` work, and `right - left` shrinks by at least half every time
(same argument as yesterday's recursive halving, just tracked with two variables instead of a
stack of calls): `O(log n)` iterations, `O(log n)` time.

**Space.** This is the difference from yesterday. `left`, `right`, and `mid` are the only extra
memory, and they don't grow: `O(1)` space. Yesterday's recursive version was also `O(log n)` time,
but `O(log n)` space for the call stack, one frame per halving. Same time, less space: the usual
reason an iterative rewrite is worth doing once a recursive solution is understood and proven
correct.

</details>

<details>
<summary>4. Search a 2D Matrix</summary>

[LeetCode 74](https://leetcode.com/problems/search-a-2d-matrix/description/): an `m x n` matrix
where every row is sorted ascending, and the first integer of each row is bigger than the last
integer of the row before it. Given `target`, return whether it's anywhere in the matrix.

**Question for the class:** that second property is stronger than "each row is sorted". Read the
matrix left to right, top to bottom, row after row. What does that make it look like?

<details>
<summary>Answer</summary>

A single sorted array of length `rows * cols`, just written on `rows` lines instead of one. Row 0
sorted, then row 1 sorted and everything in it bigger than everything in row 0, then row 2 bigger
than all of row 1, and so on. Reading in that order, values never go down.

If it's a sorted array in disguise, binary search from today already solves it, provided we can
turn a position in that imaginary array back into a `(row, col)` cell.

</details>

**Question for the class:** given an index `idx` counting through that imaginary flattened array,
`0, 1, ..., rows * cols - 1`, which cell of the real matrix does it correspond to?

<details>
<summary>Answer</summary>

Row `idx // cols`, column `idx % cols`. `cols` cells per row, so every `cols` steps of `idx` moves
down one row, and the remainder is how far along that row you are.

</details>

**Solution:** [`solution.py`](../problem_solutions/search-a-2d-matrix/solution.py) /
[`solution.cpp`](../problem_solutions/search-a-2d-matrix/solution.cpp), written up in
[`problem_solutions/search-a-2d-matrix/`](../problem_solutions/search-a-2d-matrix/).

```
function search_matrix(matrix, target):
    rows, cols = number of rows, number of columns in matrix
    left, right = 0, rows * cols - 1

    while left <= right:
        mid = (left + right) // 2
        value = matrix[mid // cols][mid % cols]      // mid, read as a matrix cell

        if value == target:
            return True
        elif value < target:
            left = mid + 1
        else:
            right = mid - 1

    return False
```

Section 1's `binary_search`, unchanged in every line that matters, `left`, `right`, `mid`, and the
three-way branch, just reading `matrix[mid // cols][mid % cols]` wherever it used to read
`nums[mid]`.

<details>
<summary>Correctness and complexity</summary>

**Correctness** needs nothing new. `value(idx) = matrix[idx // cols][idx % cols]` for
`idx` from `0` to `rows * cols - 1` is nondecreasing, sorted within a row by the problem's first
guarantee, and not dropping across a row boundary by its second guarantee. That makes
`search_matrix` exactly `binary_search` run on the array `value(0), value(1), ..., value(rows *
cols - 1)`, so section 2's Claim, Initialization, Maintenance, and Termination all carry over
untouched; only the way a cell's value is read changed, not the loop that decides where to look.

**Complexity:** `O(log(rows * cols))` time, which is `O(log rows + log cols)`, and `O(1)` space,
same as section 3, since `rows * cols` is just this problem's `n`.

</details>

**Question for the class:** a different idea for this problem: binary search over the rows for the
one whose first entry is `<= target`, and inside that call, binary search over the row itself
(effectively two nested copies of section 1's `binary_search`). It's correct, every row visited
either fully rules itself out or gets a real row search. How does its complexity compare to the
flattened version above?

<details>
<summary>Answer: worse, and it's a good Master Theorem-style habit to check</summary>

The outer binary search visits `O(log rows)` candidate row indices before it stops. In the worst
case (say `target` is bigger than every row's first entry), *every* one of those candidates passes
the `matrix[mid][0] <= target` check and triggers a full row search, each costing `O(log cols)`.
Multiply: `O(log rows * log cols)`.

Compare the two bounds directly: `log rows + log cols` versus `log rows * log cols`. For
`rows = cols = 1024`, `log rows = log cols = 10`: the sum is `20`, the product is `100`. Once both
logs are at least `2` (that is, the matrix has at least 4 rows and at least 4 columns, a very mild
condition), the product is at least as big as the sum, and it pulls further ahead as the matrix
grows. The flattened, single binary search is strictly the tighter bound, and it's also less code:
one loop, reused as-is, instead of two nested copies of it.

</details>

</details>

<details>
<summary>5. Recap</summary>

- The same binary search can be written recursively (yesterday) or iteratively (today). Iterative
  trades the recursion's call stack for a couple of loop variables: same `O(log n)` time, `O(1)`
  space instead of `O(log n)`.
- **Loop invariants** are the correctness tool for loops, the way induction is the tool for
  recursion. **Claim** (the invariant), **Initialization** (true before the loop), **Maintenance**
  (one iteration preserves it), **Termination** (what it means when the loop stops) play the same
  roles as **Claim**, **Base case**, **Assume**, and **Show** do for a recursive proof.
- A matrix where every row is sorted *and* each row's first value beats the previous row's last
  value is a sorted 1D array wearing a `rows x cols` costume. Map a virtual index to a cell with
  `idx // cols, idx % cols` and reuse binary search exactly as written.
- Two nested binary searches (rows, then within a row) are also correct, but cost
  `O(log rows * log cols)` in the worst case, looser than the flattened version's
  `O(log rows + log cols) = O(log(rows * cols))`. When a problem splits into two independent
  binary searches, check whether it can be flattened into one before settling for nesting them.

</details>
