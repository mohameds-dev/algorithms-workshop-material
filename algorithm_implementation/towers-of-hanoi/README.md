# Towers of Hanoi

The classic recursion exercise: move a stack of `n` disks from one pole to another, one disk at a
time, never placing a disk on a smaller one.

- Discussed: [Week 3, Day 1](../../weekly_material/week03_day1.md)

## Summary

Three poles, `A`, `B`, and `C`. Pole `A` holds `n` disks of different sizes, biggest at the
bottom. Move the whole stack to pole `C`, printing every move, subject to three rules:

1. Move exactly one disk at a time.
2. Only the top disk of a pole can be moved.
3. A disk may never sit on top of a smaller disk.

## Hints

Ignore the small disks and think about the biggest one, disk `n`. It has to get from the bottom
of `A` to the bottom of `C`. For that single move to be legal, nothing can be above it on `A` and
nothing smaller can be on `C`, which forces all `n - 1` other disks onto `B`. Getting `n - 1`
disks onto `B` is the same problem one size smaller, with the poles playing different roles.

## Solution

[`solution.cpp`](solution.cpp) / [`solution.py`](solution.py): `hanoi(n, from_pole, to_pole,
aux_pole)` moves the top `n` disks from `from_pole` to `to_pole`, using `aux_pole` as the spare.
With 0 disks there is nothing to do (the base case). Otherwise it moves the top `n - 1` disks out
of the way onto `aux_pole`, moves disk `n` directly to `to_pole`, then moves those `n - 1` disks
from `aux_pole` onto `to_pole`.

The poles are parameters rather than fixed names, and their roles rotate between the two
recursive calls: in the first call the destination is the spare pole, in the second call the
source is the spare pole. That argument order is the whole algorithm.

Nothing in the code checks rule 3, because rule 3 is never in danger: every recursive call moves
a complete set of the smallest disks currently in play, and a disk smaller than every other disk
can be placed anywhere.

`hanoi(3, "A", "C", "B")` prints:

```
move disk 1 from A to C
move disk 2 from A to B
move disk 1 from C to B
move disk 3 from A to C
move disk 1 from B to A
move disk 2 from B to C
move disk 1 from A to C
```

## Complexity

Each call makes two recursive calls on `n - 1` disks plus one move of its own, so the number of
moves is:

```
M(0) = 0
M(n) = 2 * M(n-1) + 1
```

Unrolling gives `M(n) = 2^n - 1`, so time is `O(2^n)`. The Master Theorem does not apply here:
it covers `T(n/b)`, a piece that is a constant fraction of the input, while this recurrence
subtracts instead of dividing.

Space is `O(n)`: no arrays or copies, only the call stack, which is `n` frames deep at its
deepest.

`2^n - 1` is optimal. Disk `n` has to move at least once, and both before and after that move the
other `n - 1` disks must sit together on a single pole, which is a full `n - 1` transfer each
time, so any correct solution needs at least `2 M(n-1) + 1` moves.

Further reading: Erickson, *Algorithms*, Ch. 1 "Recursion", §1.3 "Tower of Hanoi" (pp. 24-26)
covers the same algorithm and argument with pictures. The exercises for that chapter (problems 4
and 5, pp. 47-49) cover restricted variants where moves are only allowed between certain poles,
which is the graph version discussed in
[Week 3, Day 1](../../weekly_material/week03_day1.md).
