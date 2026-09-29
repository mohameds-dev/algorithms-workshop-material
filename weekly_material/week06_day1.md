# Week 06, Day 1 (September 28, 2026)

## Today

Last week we explored backtracking through two structural lenses: binary include/exclude
decisions (Subsets) and sequential element selection (Permutations and Social Permutations).
Today we consolidate those complexity models, then apply backtracking with multi-directional
pruning to a classic benchmark: [LeetCode 51, N-Queens](https://leetcode.com/problems/n-queens/).

<details>
<summary>1. Backtracking review and complexity models</summary>

Over the previous sessions, we developed three distinct backtracking structures. Review the
individual solutions and proofs in their respective session notes:

- **Subsets:** [Week 5, Day 1](week05_day1.md) and [`problem_solutions/subsets/`](../problem_solutions/subsets/)
- **Permutations:** [Week 5, Day 1](week05_day1.md) and [`problem_solutions/permutations/`](../problem_solutions/permutations/)
- **Social Permutations:** [Week 5, Day 2](week05_day2.md) and [`problem_solutions/social-permutations/`](../problem_solutions/social-permutations/)

### Comparing the three decision models

| Problem | Decision per step | Branching factor | Leaves | Time complexity | Working space |
|---|---|---|---|---|---|
| Subsets | Include or exclude element | 2 (fixed) | `2^n` | `O(n * 2^n)` | `O(n)` |
| Permutations | Pick next unused element | `n - level` (shrinking) | `n!` | `O(n * n!)` | `O(n)` |
| Social Permutations | Pick unused element without conflict | `<= n - level` (pruned) | `< n!` | `O(n * n!)` bound | `O(n)` |

**Key observations:**

1. **Fixed vs shrinking branching factor:** Subsets makes a binary decision at each index, yielding
   a full binary recursion tree of depth `n` with `2^n` leaves. Permutations selects an unused
   element, starting with `n` branches, then `n - 1`, down to `1`, producing `n!` leaves.
2. **Copying dominates leaf cost:** Both Subsets and Permutations perform `O(1)` work at internal
   nodes (excluding loop overhead), but pay `O(n)` at each leaf to copy the accumulated solution
   into the results array.
3. **Pruning avoids entire subtrees:** Social Permutations uses the exact same skeleton as
   Permutations, but checks constraints (no self-gift, no mutual gift) before recursing. An invalid
   choice is pruned immediately, preventing the recursion from expanding subtrees that cannot lead
   to valid outputs.

<details>
<summary>Question: When should we use include/exclude vs next-element choice?</summary>

Use **include/exclude** when each item has an independent binary state (present or absent), and
ordering does not matter. The search tree depth is fixed to the number of items, and the branching
factor is always 2.

Use **next-element choice** when placing items into sequential slots or orderings. The choices at
each step depend on which elements remain available, producing a shrinking branching factor.

</details>

</details>

<details>
<summary>2. N-Queens</summary>

[LeetCode 51](https://leetcode.com/problems/n-queens/): given an integer `n`, place `n` queens on an
`n x n` chessboard such that no two queens attack each other. Return all distinct board
configurations, where `'Q'` is a queen and `'.'` is an empty space.

Recall that a queen attacks along its row, column, and both diagonals.

**Question for the class:** An `n x n` board has `n^2` squares. If we placed `n` queens by picking
any `n` distinct squares on the board, how many states would we need to inspect?

<details>
<summary>Answer</summary>

`C(n^2, n) = (n^2)! / (n! * (n^2 - n)!)`. For `n = 8`, this is `C(64, 8) ≈ 4.42 * 10^9` states.
Checking this exhaustively is completely infeasible.

</details>

### Formulating the search space

We can drastically reduce the search space by encoding the rules directly into our recursion:

1. **Row constraint:** No two queens can share a row. Because there are `n` queens and `n` rows,
   every row must contain *exactly one* queen. We place queens row by row: row `0`, row `1`, ...,
   row `n - 1`.
2. **Column constraint:** No two queens can share a column. When placing a queen in row `r`, we must
   pick a column `c` that has not been used yet. Thus, the list of column choices
   `[c_0, c_1, ..., c_{n-1}]` is a **permutation** of `[0, 1, ..., n - 1]`.
   This constraint alone drops the search space from `4.42 * 10^9` down to `n! = 8! = 40,320`.
3. **Diagonal constraint:** No two queens can share a diagonal. If a candidate column conflicts with
   an existing queen on either diagonal, prune that choice immediately.

### How to formulate the O(1) diagonal optimization

Ray-casting along diagonals (as in [`verbose_inefficient_solution.py`](../problem_solutions/n-queens/verbose_inefficient_solution.py)
and [`fair_solution.py`](../problem_solutions/n-queens/fair_solution.py)) takes $O(\text{row})$ time
at every candidate square. We can achieve $O(1)$ lookups by finding a mathematical invariant for
each diagonal, just as we did for columns.

Here is the 4-step thought process to formulate this:

#### Step 1: Think about invariants (constant change along each line)

Whenever you move one step diagonally on a grid:
- `row` changes by $\pm 1$.
- `col` changes by $\pm 1$.

Because both coordinates change at the exact same rate, there must be a simple linear combination
of `row` and `col` whose net change is zero: an **invariant**.

#### Step 2: Formulate the algebraic invariant

1. **Anti-diagonals (`/`, top-right to bottom-left):**
   - As you move down and left, `row` increases by 1 ($+1$) while `col` decreases by 1 ($-1$).
   - The sum changes by $(+1) + (-1) = 0$.
   - **Invariant:** `row + col` is identical for every square on the same anti-diagonal.

2. **Main diagonals (`\`, top-left to bottom-right):**
   - As you move down and right, `row` increases by 1 ($+1$) and `col` increases by 1 ($+1$).
   - The difference changes by $(+1) - (+1) = 0$.
   - **Invariant:** `row - col` is identical for every square on the same main diagonal.

#### Step 3: Plot the invariants on a 5x5 grid (n = 5)

Let us plot the raw invariant values across a $5 \times 5$ board to see their patterns and bounds:

**Anti-diagonals (`row + col`):**
```
row \ col    0   1   2   3   4
   0         0   1   2   3   4
   1         1   2   3   4   5
   2         2   3   4   5   6
   3         3   4   5   6   7
   4         4   5   6   7   8
```
- Smallest sum: `(0, 0)` gives $0 + 0 = 0$.
- Largest sum: `(4, 4)` gives $4 + 4 = 8$ (in general, $2n - 2$).
- Total distinct anti-diagonals: $8 - 0 + 1 = 9$ (in general, $2n - 1$).
- Because values naturally run from `0` to `2n - 2`, `row + col` is immediately ready to serve as
  a 0-based array index into `anti_diagonal_reserved` of size $2n - 1$.

**Main diagonals (raw `row - col`):**
```
row \ col    0    1    2    3    4
   0         0   -1   -2   -3   -4   <-- negative values!
   1         1    0   -1   -2   -3
   2         2    1    0   -1   -2
   3         3    2    1    0   -1
   4         4    3    2    1    0
```
- Smallest difference: top-right corner `(0, 4)` gives $0 - 4 = -4$ (in general, $-(n - 1)$).
- Largest difference: bottom-left corner `(4, 0)` gives $4 - 0 = +4$ (in general, $+(n - 1)$).
- Total distinct main diagonals: $4 - (-4) + 1 = 9$ (in general, $2n - 1$).

#### Step 4: Fix negative indices with + (n - 1)

Raw differences range from $-(n - 1)$ to $+(n - 1)$ (here, $-4$ to $+4$). Negative indices cannot be
used directly:
- In C++, accessing a negative index causes an immediate out-of-bounds error / segfault.
- In Python, negative indices wrap around from the back of the list (e.g., `-1` hits index `8`),
  silently creating false positive collisions between completely unrelated diagonals.

To shift the minimum value from $-(n - 1)$ up to `0`, add $(n - 1)$ (here, $+ 4$):

$$\text{main\_diagonal\_index} = (\text{row} - \text{col}) + (n - 1)$$

Plotting the shifted values `row - col + 4` on the $5 \times 5$ grid:
```
row \ col    0   1   2   3   4
   0         4   3   2   1   0
   1         5   4   3   2   1
   2         6   5   4   3   2
   3         7   6   5   4   3
   4         8   7   6   5   4
```
Now every main diagonal maps to a unique, valid 0-based index from `0` to `2n - 2` ($0$ to $8$).

### Summary: O(1) Tracking State

By maintaining three boolean arrays:
- `col_reserved`: size $n$, indexed by `col`
- `anti_diagonal_reserved`: size $2n - 1$, indexed by `row + col`
- `main_diagonal_reserved`: size $2n - 1$, indexed by `row - col + (n - 1)`

Checking whether a square `(row, col)` is under attack becomes three $O(1)$ array lookups:
```
is_attacked(row, col) = col_reserved[col] or
                        main_diagonal_reserved[row - col + (n - 1)] or
                        anti_diagonal_reserved[row + col]
```

### Problem Structure and Mental Model

To keep your code clean, break the solution into three distinct responsibilities:

1. **`is_attacked(row, col)` (The Validator):**
   Given candidate coordinates `(row, col)`, checks whether column `col`, main diagonal
   `row - col + (n - 1)`, or anti-diagonal `row + col` is already occupied by a previously placed queen.
   Returns `true` if attacked (prune branch), or `false` if safe.
2. **`backtrack(current_row)` (The Recursive Explorer):**
   - **Base case:** When `current_row == n`, all `n` queens have been safely placed in rows `0` to `n - 1`.
     Format the board rows into strings, append to `answer`, and return.
   - **Recursive step:** Iterate `col` from `0` to `n - 1`. For each non-attacked square:
     1. Place queen: write `'Q'` on `board` and mark `col_reserved`, `main_diagonal_reserved`, and `anti_diagonal_reserved` as `true`.
     2. Recurse: call `backtrack(current_row + 1)`.
     3. Undo (backtrack): restore `board` to `'.'` and reset all three reservation booleans to `false`.
3. **`solveNQueens(n)` (The Orchestrator):**
   Initializes the empty board, the tracking arrays, launches `backtrack(0)`, and returns `answer`.

<details>
<summary>Starting snippet (Python)</summary>

```python
from typing import List


class Solution:
    def solveNQueens(self, n: int) -> List[List[str]]:
        board = [["." for _ in range(n)] for _ in range(n)]
        col_reserved = [False for _ in range(n)]
        main_diagonal_reserved = [False for _ in range(2 * n - 1)]  # row - col + (n - 1)
        anti_diagonal_reserved = [False for _ in range(2 * n - 1)]  # row + col
        answer: List[List[str]] = []

        def is_attacked(row: int, col: int) -> bool:
            # TODO: compute main and anti diagonal indices
            # return True if col or either diagonal is already reserved
            pass

        def backtrack(current_row: int) -> None:
            # TODO: Base case: if current_row == n, record formatted board in answer and return

            # TODO: Recursive step: loop col from 0 to n - 1
            # If not is_attacked(current_row, col):
            #   1. place 'Q' on board and mark reservations true
            #   2. recurse on current_row + 1
            #   3. restore '.' on board and unmark reservations false (backtrack!)
            pass

        backtrack(0)
        return answer


# Manual verification snippet:
if __name__ == "__main__":
    sol = Solution()
    boards = sol.solveNQueens(4)
    print(f"Found {len(boards)} solution(s) for n = 4:\n")
    for i, b in enumerate(boards, 1):
        print(f"Solution {i}:")
        for row in b:
            print(row)
        print()
```

</details>

<details>
<summary>Starting snippet (C++)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int n;
    vector<string> board;
    vector<bool> col_reserved;
    vector<bool> main_diagonal_reserved;
    vector<bool> anti_diagonal_reserved;
    vector<vector<string>> answer;

    void initialize_fields(int board_size) {
        n = board_size;
        board = vector<string>(n, string(n, '.'));
        col_reserved = vector<bool>(n, false);
        main_diagonal_reserved = vector<bool>(2 * n - 1, false);
        anti_diagonal_reserved = vector<bool>(2 * n - 1, false);
        answer.clear();
    }

    bool is_attacked(int row, int col) {
        // TODO: compute main_diagonal_index and anti_diagonal_index
        // return true if col_reserved, main_diagonal_reserved, or anti_diagonal_reserved is true
        return false;
    }

    void backtrack(int current_row) {
        // TODO: Base case: if current_row == n, push board into answer and return

        // TODO: Recursive step: loop col from 0 to n - 1
        // If !is_attacked(current_row, col):
        //   1. place 'Q' on board and mark reservations true
        //   2. recurse on current_row + 1
        //   3. restore '.' on board and unmark reservations false (backtrack!)
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        initialize_fields(n);
        backtrack(0);
        return answer;
    }
};

// Manual verification snippet:
int main() {
    Solution sol;
    auto boards = sol.solveNQueens(4);
    cout << "Found " << boards.size() << " solution(s) for n = 4:\n\n";
    for (size_t i = 0; i < boards.size(); i++) {
        cout << "Solution " << i + 1 << ":\n";
        for (const auto &row : boards[i]) {
            cout << row << "\n";
        }
        cout << "\n";
    }
    return 0;
}
```

</details>

<details>
<summary>Hints</summary>

1. **`is_attacked` indexing:**
   - Main diagonal index: `row - col + (n - 1)`. Why $+ (n - 1)$? To shift negative differences
     $[- (n - 1), n - 1]$ to positive array indices $[0, 2n - 2]$.
   - Anti-diagonal index: `row + col`. Range is $[0, 2n - 2]$.
   - Check if `col_reserved[col]`, `main_diagonal_reserved[...]`, or `anti_diagonal_reserved[...]`
     is true.
2. **`backtrack` base case:**
   - When `current_row == n`, all rows `0` to `n - 1` have received a safe queen.
   - In Python, convert each row list into a string using `["".join(r) for r in board]`, append to
     `answer`, and return.
   - In C++, `board` is already a `vector<string>`, so `answer.push_back(board);` directly records it.
3. **`backtrack` recursive loop:**
   - Iterate over each candidate column: `for col in range(n)` / `for (int col = 0; col < n; col++)`.
   - Before doing anything, check `is_attacked(current_row, col)`. If it is attacked, `continue` to
     skip to the next column.
4. **Placement and state update:**
   - Set `board[current_row][col] = 'Q'`.
   - Set `col_reserved[col] = true`.
   - Set `main_diagonal_reserved[current_row - col + n - 1] = true`.
   - Set `anti_diagonal_reserved[current_row + col] = true`.
5. **Recursive exploration:**
   - Call `backtrack(current_row + 1)`.
6. **Undo (The Backtrack Step):**
   - Crucial: Once the recursive call returns, reset `board[current_row][col] = '.'` and unmark
     all three reservation booleans to `false`. Without this undo step, future branches in the loop
     will see ghost queens left behind from previous branches.

</details>

**Solutions:** Walk through the problem in three steps:
1. [`verbose_inefficient_solution.py`](../problem_solutions/n-queens/verbose_inefficient_solution.py):
   intuitive baseline testing rows, columns, and 4-way ray-casting diagonals.
2. [`fair_solution.py`](../problem_solutions/n-queens/fair_solution.py):
   removes redundant row/downward checks, uses `col_reserved` for $O(1)$ column checks.
3. [`solution.py`](../problem_solutions/n-queens/solution.py) /
   [`solution.cpp`](../problem_solutions/n-queens/solution.cpp):
   optimal $O(1)$ diagonal index checks, written up in
   [`problem_solutions/n-queens/`](../problem_solutions/n-queens/).

```
function backtrack(current_row):
    if current_row == n:
        answer.append(format_board(board))             // all n queens placed safely
        return

    for col from 0 to n - 1:
        if not is_attacked(current_row, col):
            main_idx = current_row - col + n - 1
            anti_idx = current_row + col

            board[current_row][col] = 'Q'
            col_reserved[col] = true
            main_diagonal_reserved[main_idx] = true
            anti_diagonal_reserved[anti_idx] = true

            backtrack(current_row + 1)

            board[current_row][col] = '.'              // undo: "backtrack"
            col_reserved[col] = false
            main_diagonal_reserved[main_idx] = false
            anti_diagonal_reserved[anti_idx] = false
```

<details>
<summary>Correctness</summary>

**Claim:** For any `current_row` from `0` to `n`, given a valid placement of non-attacking queens in
rows `0` to `current_row - 1`, calling `backtrack(current_row)` appends all valid completions of the
chessboard to `answer`, and leaves `board`, `col_reserved`, `main_diagonal_reserved`, and
`anti_diagonal_reserved` unchanged upon return.

**Base case:** `current_row == n`. Exactly `n` queens have been safely placed in rows `0` to `n - 1`
with no conflicts. No further rows remain. The Claim requires recording this complete board, which
matches `answer.append(...)`. No tracking arrays are modified, so state is preserved.

**Assume:** The Claim holds for `current_row + 1` with any valid placement in rows `0` to `current_row`.

**Show:** For `current_row < n`, the loop inspects every column `col` from `0` to `n - 1`:

- If `is_attacked(current_row, col)` is true, placing a queen at `(current_row, col)` attacks an
  earlier queen. Any configuration starting with this placement is invalid, so pruning it preserves
  correctness.
- If not attacked, `(current_row, col)` does not conflict with any queen placed so far. The algorithm
  places `'Q'` on `board` and marks `col_reserved`, `main_diagonal_reserved`, and
  `anti_diagonal_reserved` as true.
- By **Assume**, the recursive call `backtrack(current_row + 1)` appends all valid completions
  extending this placement, and restores the tracking state.
- The algorithm then restores `board[current_row][col] = '.'` and unmarks `col_reserved`,
  `main_diagonal_reserved`, and `anti_diagonal_reserved`, returning state to what it was prior to
  testing column `col`.

Because every valid configuration must place a queen in some non-conflicting column of row
`current_row`, and every such column is explored and restored, `backtrack(current_row)` generates all
valid completions extending rows `0` to `current_row - 1` exactly once.

By induction (downward from `current_row = n`), the initial call `backtrack(0)` appends every valid
solution on an `n x n` board, exactly once.

</details>

<details>
<summary>Complexity</summary>

**Question for the class:** How many nodes does the recursion tree visit?

<details>
<summary>Answer</summary>

At most `O(n!)` nodes. Row 0 has `n` choices, row 1 has at most `n - 1` (excluding the same column),
row 2 has at most `n - 2`, and so on. Diagonal pruning eliminates most branches much earlier: for
`n = 8`, only 2,057 nodes are visited in total out of `8! = 40,320` full column permutations.

</details>

**Time:** Each state takes `O(1)` work to check and update candidate columns. When a valid placement
reaches row `n`, constructing the `n` strings of length `n` takes `O(n^2)` time. Thus, time is
**`O(n!)`** upper bounded by permutations, or more precisely `O(S * n^2)` where `S` is the number
of valid solutions.

**Space:** The recursion depth is `n`. The arrays `board` (size `n x n`), `col_reserved` (size `n`),
`main_diagonal_reserved` (size `2n - 1`), and `anti_diagonal_reserved` (size `2n - 1`) take
`O(n^2)` auxiliary space for the board state, or `O(n)` if representing row placements directly,
excluding the solution output list.

</details>

</details>

<details>
<summary>3. Recap</summary>

- **Permutation with constraints:** N-Queens is Permutations in disguise. Row-by-row placement
  satisfies the row rule automatically; column tracking ensures column uniqueness (a permutation);
  diagonal arrays prune invalid branches early.
- **Constant-time constraint checking:** Using the invariant lines `row - col` and `row + col` turns
  geometric diagonal checks into `O(1)` array lookups, avoiding costly board scans.
- **The Backtracking Progression:**
  1. *Subsets:* Binary branching, fixed branching factor 2, `O(n * 2^n)`.
  2. *Permutations:* Unused element branching, shrinking branching factor `n - level`, `O(n * n!)`.
  3. *Social Permutations:* Permutations with mutual-pair pruning.
  4. *N-Queens:* Permutations with column and diagonal pruning.

</details>

<details>
<summary>References</summary>

- LeetCode 51: [N-Queens](https://leetcode.com/problems/n-queens/)
- LeetCode 52: [N-Queens II](https://leetcode.com/problems/n-queens-ii/) (counting solutions without board construction)

</details>
