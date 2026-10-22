# Meeting Rooms

LeetCode 252 / NeetCode: https://neetcode.io/problems/meeting-schedule

- Difficulty: Easy
- Topics: Array, Sorting
- Discussed: [Week 9, Day 2](../../weekly_material/week09_day2.md)

## Summary

Given an array of meeting time intervals consisting of start and end times `[[start_1, end_1], [start_2, end_2], ...]`, determine if a person could attend all meetings. In other words, check if any two meetings overlap.

## Hints

<details>
<summary>Hints</summary>

1. If meetings appear out of order, how can you easily check for conflicts without comparing every pair in $O(n^2)$ time?
2. Sort the meetings by their start times.
3. After sorting, if any conflict exists, will it always occur between two adjacent meetings in the sorted array?
4. If meeting $i$ ends after meeting $i+1$ starts (`intervals[i].end > intervals[i+1].start`), is attending both possible?

</details>

## Solution

[`solution.py`](solution.py) / [`solution.cpp`](solution.cpp): sort by start time and verify adjacent intervals.

- Sort all intervals by their start times.
- Linearly scan through adjacent pairs: for index $i$ from 0 to $n - 2$, if `intervals[i].end > intervals[i+1].start`, return `false`.
- If the loop completes with no conflicts detected, return `true`.

## Correctness

- **Claim:** Sorting by start time and checking adjacent pairs detects all overlapping intervals.
- **Proof:** Suppose there exist two overlapping intervals $A$ and $B$ with $A.start \le B.start$.
  - Because they overlap, $A.end > B.start$.
  - In the sorted order, let $A = I_j$ and $B = I_k$ with $j < k$.
  - If $k = j + 1$, the adjacent check directly catches the overlap.
  - If $k > j + 1$, consider $I_{j+1}$. Since intervals are sorted by start time, $A.start \le I_{j+1}.start \le B.start < A.end$.
  - Thus, $A$ also overlaps with $I_{j+1}$. By induction, at least one adjacent pair of intervals must overlap. Checking only adjacent intervals is therefore necessary and sufficient.

## Complexity

Let $n$ be the number of intervals:

- **Time:** $O(n \log n)$ to sort the intervals, followed by an $O(n)$ linear scan. Overall time is $O(n \log n)$.
- **Space:** $O(1)$ auxiliary space if sorting in place, or $O(n)$ depending on the language sort implementation.
