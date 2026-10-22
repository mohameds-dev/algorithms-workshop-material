# Meeting Rooms II

LeetCode 253 / NeetCode: https://neetcode.io/problems/meeting-schedule-ii

- Difficulty: Medium
- Topics: Array, Greedy, Sorting, Heap, Balanced Binary Search Tree (Multiset)
- Discussed: [Week 9, Day 2](../../weekly_material/week09_day2.md)

## Summary

Given an array of meeting time intervals consisting of start and end times `[[start_1, end_1], [start_2, end_2], ...]`, find the minimum number of conference rooms required to hold all meetings without conflicts.

## Hints

<details>
<summary>Hints</summary>

1. In Meeting Rooms I, we checked whether 1 room was sufficient. Here, we must accommodate every single meeting.
2. In what order should we process meetings? Processing them in chronological order of start times allows us to allocate rooms as meetings begin.
3. When meeting $i$ starts, what condition allows it to reuse an existing room? An existing room can be reused if its previous meeting finished at or before $i.start$ (`room_end <= i.start`).
4. If multiple rooms are free, which one should we reuse? Picking the room that freed up most recently ($\le i.start$) leaves earlier-freed rooms available for other meetings.
5. If no existing room is free at $i.start$, we must open a new room.

</details>

## Solution

[`solution.cpp`](solution.cpp): sorting intervals with a custom comparator and tracking room availability via `std::multiset<int, greater<>>`.

- **Sorting:** We sort meetings by start time ascending. If start times tie, we break ties by end time ascending.
- **Descending Multiset (`multiset<int, greater<>>`):** We maintain `room_available`, storing the time each currently occupied room becomes free, in descending order.
- **Querying with `lower_bound`:**
  - In a descending multiset (`greater<>`), `lower_bound(x)` finds the first element where `element > x` is false, meaning `element <= x`.
  - Because elements are ordered largest to smallest, the first element with `element <= x` is the **maximum (latest) available time $\le x$**.
  - If found (`it != room_available.end()`), we reuse this room by erasing the old time: `room_available.erase(it)`.
  - We then insert the meeting's finish time: `room_available.insert(i.end)`.
- At the end, `room_available.size()` gives the total number of rooms allocated.

## Problem Breakdown and Q&A

### Part 1: Storing and Sorting Intervals with a Custom Comparator

```cpp
bool compareIntervals(const Interval &a, const Interval &b) {
    return a.start < b.start or (a.start == b.start and a.end < b.end);
}

// In main / method:
sort(intervals.begin(), intervals.end(), compareIntervals);
```

### Part 2: Searching for Room Availability in a Descending Multiset

**Question:** Why does `room_available.lower_bound(i.start)` on `multiset<int, greater<>>` return the largest room end time that is $\le i.start$?

**Answer:**
- By C++ specification, `lower_bound(x)` finds the first element $y$ where `comp(y, x)` is false.
- Under `greater<>`, `comp(y, x)` is `y > x`. The condition is false when $y \le x$.
- Since elements are stored in descending order (highest to lowest), the first element satisfying $y \le x$ is guaranteed to be the **maximum element $\le x$**.
- This enables $O(\log k)$ lookup of the best compatible room and immediate $O(\log k)$ update.

## Complexity

Let $n$ be the number of intervals:

- **Time:**
  - Sorting $n$ intervals: $O(n \log n)$.
  - For each interval, multiset `lower_bound`, `erase`, and `insert` take $O(\log k)$ time, where $k \le n$ is the number of allocated rooms.
  - Overall time: $O(n \log n)$.
- **Space:** $O(n)$ auxiliary space to store the room end times in the multiset.
