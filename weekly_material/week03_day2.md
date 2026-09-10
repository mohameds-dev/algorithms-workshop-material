# Week 03, Day 2 (September 10, 2026)

## Today

Last session we took a solution we had already written and asked two questions about it: is it
correct, and how slow is it. Today we start from scratch with a new problem, Towers of Hanoi.
You solve it first, then we ask those same two questions about your own solution, and finish
with a version of the puzzle where the poles are not all connected to each other.

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

Same reason as the lopsided split in [last session](week03_day1.md): the Master Theorem needs
`T(n/b)`, a piece that is a constant **fraction** of the input. Here the subproblem is `n - 1`,
a subtraction, not a division. The theorem simply does not apply, so we unroll, which is what we
just did.

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
the formula collapses to `C(n) = 2C(n-1) + 1 = 2^n - 1`. Same answer as step 4 above.

</details>

<details>
<summary>References</summary>

- Erickson, *Algorithms*, Ch. 1 exercises, problems 4 and 5 (pp. 47-49): restricted Towers of
  Hanoi. Problem 4 forbids moves between two of the pegs (a 3-node path graph), problem 5 puts
  `k` pegs in a row and allows moves only between neighbors. Good practice for this exact idea.

</details>

</details>

<details>
<summary>6. Recap</summary>

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
