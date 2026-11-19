# Week 04, Day 2 (September 17, 2026)

## Today

Last session's binary search was recursive. Today we write the same idea as a loop, prove it correct
with a different tool than induction, and then reuse it, unchanged, to solve a matrix search
problem that turns out to be the same problem in disguise.

<details>
<summary>1. From recursion to a loop</summary>

Last session's `search_recursive` narrowed a range `[left, right]` by comparing `target` against the
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
(same argument as last session's recursive halving, just tracked with two variables instead of a
stack of calls): `O(log n)` iterations, `O(log n)` time.

**Space.** This is the difference from last session. `left`, `right`, and `mid` are the only extra
memory, and they don't grow: `O(1)` space. Last session's recursive version was also `O(log n)` time,
but `O(log n)` space for the call stack, one frame per halving. Same time, less space: the usual
reason an iterative rewrite is worth doing once a recursive solution is understood and proven
correct.

</details>

<details>
<summary>4. Search a 2D Matrix</summary>

[LeetCode 74](https://leetcode.com/problems/search-a-2d-matrix/description/): an `m x n` matrix
where every row is sorted ascending, and the first integer of each row is bigger than the last
integer of the row before it. Given `target`, return whether it's anywhere in the matrix.

**Question for the class:** that second property is stronger than "each row is sorted": it says
something about the rows' own starting values, `matrix[0][0], matrix[1][0], ..., matrix[rows-1][0]`.
What?

<details>
<summary>Answer</summary>

They're increasing too: `matrix[i+1][0] > matrix[i][last]`, and a row's last entry is `>=` its own
first entry, so `matrix[i+1][0] > matrix[i][0]`. A sequence of increasing numbers is exactly what
binary search needs. So: binary search over the rows for the *last* one whose first entry is
`<= target`, then binary search inside that one row. Two binary searches, one after the other, no
nesting.

</details>

**Solution:** [`solution.py`](../problem_solutions/search-a-2d-matrix/solution.py) /
[`solution.cpp`](../problem_solutions/search-a-2d-matrix/solution.cpp), written up in
[`problem_solutions/search-a-2d-matrix/`](../problem_solutions/search-a-2d-matrix/).

```
function find_row(matrix, target):
    left, right = 0, number of rows in matrix - 1
    row = -1

    while left <= right:
        mid = (left + right) // 2
        if matrix[mid][0] <= target:
            row = mid              // best candidate so far
            left = mid + 1         // a later row might be an even better candidate
        else:
            right = mid - 1

    return row

function search_matrix(matrix, target):
    row = find_row(matrix, target)
    if row == -1:
        return False

    return search_row(matrix[row], target) != -1   // -1 means "not found", same as section 1
```

`find_row` is a binary search over the row-starting values for the boundary between "row starts
`<= target`" and "row starts `> target`", keeping the best (largest) index it's seen on the true
side. `search_row` is the exact `binary_search` from section 1, unchanged, just under a name that
fits this problem: it returns `target`'s index in the row it's given, or `-1`. `search_matrix`
runs `find_row` once, hands the one row it points to over to `search_row`, and turns that index
into the bool this problem actually asks for with `!= -1`.

<details>
<summary>Correctness</summary>

**`find_row` finds the right row.** Since `matrix[i][0]` is increasing in `i`, the check
`matrix[mid][0] <= target` is a monotonic predicate: true for a prefix of row indices, false for
the rest. That's the same loop invariant shape as section 2, just for "find the last index where
a monotonic condition holds" instead of "find an equal value":

- **Claim:** at the start of every iteration, if some row index has `matrix[i][0] <= target`, the
  largest such index is either already stored in `row`, or lies in `[left, right]`.
- **Initialization:** `left = 0`, `right = rows - 1` covers every row index, and `row = -1`;
  trivially true.
- **Maintenance:** if `matrix[mid][0] <= target`, `mid` satisfies the check, so it's at least as
  good as whatever `row` held before; store it, and since the largest satisfying index can't be
  smaller than `mid`, set `left = mid + 1` to keep looking to the right for a better one. If
  `matrix[mid][0] > target`, monotonicity means every index `>= mid` fails the check too, so the
  largest satisfying index (if any) is `< mid`; set `right = mid - 1`.
- **Termination:** `left > right` means every row index has been accounted for, so `row` holds
  exactly the largest index with `matrix[row][0] <= target`, or `-1` if no index has it.

**Only that row can contain `target`.** If `row == -1`, `target < matrix[0][0]`, the smallest
value in the whole matrix, so `target` can't be anywhere; the `return False` is correct. Otherwise,
let `r = row`. Every row `i < r` has `matrix[i][last] < matrix[i+1][0] <= ... <= matrix[r][0] <=
target`, so every value in it is `< target`. Every row `i > r` has `matrix[i][0] > target` (`r`
was the *largest* index satisfying the check), so every value in it, being `>= matrix[i][0]`, is
`> target`. Row `r` is the only place left `target` could be, and `search_matrix` hands it to
`search_row`, whose correctness is already proved in section 2 (it's `binary_search`, unchanged):
it returns an index `!= -1` exactly when `target` is in that row, which is exactly when `target`
is in the matrix at all.

</details>

<details>
<summary>Complexity</summary>

`find_row` is one binary search over `rows` indices: `O(log rows)`. `search_row` on one row is
`O(log cols)`. One after the other: `O(log rows) + O(log cols) = O(log rows + log cols) =
O(log(rows * cols))` time, `O(1)` space, two loops, no recursion, no extra memory beyond a handful
of indices.

</details>

**Question for the class:** a tempting variant: instead of finishing `find_row` completely and
*then* searching the row, search the row as soon as a candidate turns up, every time
`matrix[mid][0] <= target` during the row search, before deciding whether to keep looking right.
Still correct, every candidate gets a fair check. What does it cost?

<details>
<summary>Answer: worse, because the row search now runs inside the loop, not after it</summary>

The outer binary search still visits `O(log rows)` candidate row indices. In the worst case
(`target` bigger than every row's first entry), *every single one* of those candidates passes the
check and triggers a full row search, each costing `O(log cols)`, before the outer loop moves on.
Multiply instead of add: `O(log rows * log cols)`.

For `rows = cols = 1024` (`log rows = log cols = 10`), that's `100` versus this section's `20`, and
the gap only widens as the matrix grows. Doing the two binary searches strictly one after the
other, only ever touching one row, is both simpler to read and asymptotically better than checking
a row at every step of the outer search.

</details>

</details>

<details>
<summary>5. Recap</summary>

- The same binary search can be written recursively (last session) or iteratively (today). Iterative
  trades the recursion's call stack for a couple of loop variables: same `O(log n)` time, `O(1)`
  space instead of `O(log n)`.
- **Loop invariants** are the correctness tool for loops, the way induction is the tool for
  recursion. **Claim** (the invariant), **Initialization** (true before the loop), **Maintenance**
  (one iteration preserves it), **Termination** (what it means when the loop stops) play the same
  roles as **Claim**, **Base case**, **Assume**, and **Show** do for a recursive proof.
- A matrix where every row is sorted *and* each row's first value beats the previous row's last
  value has increasing row-starting values too. Binary search over the rows for the last one
  whose start is `<= target`, that's the only row that can contain it, then binary search inside
  that one row with `binary_search` exactly as written.
- The same "find the last index where a monotonic condition holds" loop invariant that locates
  the right row is the one from section 2, just applied to row-starting values instead of array
  values.
- Two binary searches run one after the other cost `O(log rows) + O(log cols) = O(log(rows *
  cols))`. Running the row search inside every step of the outer search instead of after it costs
  `O(log rows * log cols)` in the worst case, strictly worse, for no gain in correctness.

</details>
