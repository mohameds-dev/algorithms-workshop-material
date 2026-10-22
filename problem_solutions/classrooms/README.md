# Classrooms

Kattis: https://open.kattis.com/problems/classrooms

- Difficulty: Medium (Kattis 4.9)
- Topics: Greedy, Sorting, Binary Search, Multiset, Balanced Binary Search Tree
- Discussed: [Week 9, Day 2](../../weekly_material/week09_day2.md)

## Terminology

To avoid confusion throughout this discussion:
- **Classes:** The sessions that need to be scheduled, each defined by an interval $[s_i, f_i]$ with a start time and an end time.
- **Rooms:** The physical classrooms available to host classes (at most $m$ total rooms).

## Summary

You are given $n$ classes and $m$ rooms. Each class $i$ is specified by its start time $s_i$ and end time $f_i$. A room can hold at most one class at any point in time, and a class cannot use a room if another class ended at or after its start time (i.e. another class $j$ can start in a room if and only if $s_j > f_i$). Determine the maximum number of classes that can be scheduled across the $m$ rooms.

## Intuition

In single-room interval scheduling, the optimal greedy strategy is Earliest Finish Time (EFT): sort classes by end time and greedily accept every class that starts after the previous class finished. This maximizes the remaining time left for future classes.

When scaling to $m$ rooms, how should classes be assigned?

1. **Sort Classes by End Time:**
   We still process classes in order of increasing finish time ($f_i$). Taking classes that end early leaves all $m$ rooms available as early as possible.

2. **What Really Matters About a Room?**
   A room's specific label does not matter. The only property of a room that affects future scheduling decisions is **when the room becomes available**, which is given by the **end time** of the class currently occupying it.

3. **Room Compatibility:**
   A room is compatible with an incoming class if the room's current end time is strictly less than the class's start time (`room_end < class.start`).

4. **Greedy Room Selection:**
   Suppose multiple rooms are currently compatible with class $a$. Which room should we choose?
   - Consider Room 1 ending at time 2 and Room 2 ending at time 6.
   - Incoming class $a$ starts at time 8 and ends at time 10.
   - Both rooms can host class $a$.
   - If we put class $a$ in Room 1 (end time 2), Room 1's end time jumps to 10, leaving Room 2 (end time 6) as the earliest available room.
   - Now suppose another class arrives with `start = 4`. It cannot be scheduled in Room 2 ($6 \not< 4$) and cannot be scheduled in Room 1 ($10 \not< 4$). We miss out on that class!
   - If we had placed class $a$ into Room 2 instead, Room 1 (end time 2) would have remained free to take the class starting at 4 ($2 < 4$).
   - **Greedy Rule:** Always assign an incoming class to the compatible room whose class finished as late as possible without conflicting. That is, choose the room with the **largest end time strictly less than `class.start`**. This preserves earlier-ending rooms for future classes that start earlier.

5. **Opening New Rooms:**
   If no existing room has an end time $< class.start$, but we have currently used fewer than $m$ rooms, we open a new room starting with this class. Otherwise, this class cannot be scheduled and is skipped.

## High-Level Pseudocode

```text
function scheduleClasses(classes, m):
    sort classes by end time ascending (break ties by start time ascending)
    initialize end_times as an empty multiset
    answer = 0

    for each class in classes:
        // Find the room with the largest end time strictly less than class.start
        target_room = find room in end_times with maximum value < class.start

        if target_room exists:
            remove target_room from end_times
            insert class.end into end_times
            answer = answer + 1
        else if size of end_times < m:
            insert class.end into end_times
            answer = answer + 1
        else:
            // Class cannot be accommodated; skip it
            pass

    return answer
```

## Problem Breakdown and Q&A

### Part 1: Storing and Sorting Pairs with a Custom Comparator

We need to sort classes primarily by end time ascending, breaking ties by start time ascending.

#### C++ Implementation

In C++, define a custom struct and a comparison function:

```cpp
struct Class {
    int start, end;
};

bool compare_classes(const Class &a, const Class &b) {
    if (a.end == b.end)
        return a.start < b.start;
    return a.end < b.end;
}

// In main:
sort(classes.begin(), classes.end(), compare_classes);
```

#### Python Comparison

In Python, sorting tuples or objects with a `key` lambda accomplishes this directly:

```python
# Assuming classes is a list of objects or tuples (start, end)
classes.sort(key=lambda c: (c.end, c.start))
```

> [!NOTE]
> We only present Python for the sorting snippet above. The full solution requires a dynamic balanced binary search tree with multiset semantics, which is native to C++ (`std::multiset`) but not provided in Python's standard library.

---

### Part 2: Q&A: Efficiently Searching for Values in a Multiset

**Question:** In a sorted collection, how do we efficiently search for the earliest value greater than or equal to ($\ge$) a target value, or strictly greater than ($>$)?

**Answer:** Use `std::set` or `std::multiset` in C++, which are backed by red-black trees.
- `lower_bound(x)`: returns an iterator to the first element that is $\ge x$.
- `upper_bound(x)`: returns an iterator to the first element that is $> x$.

```cpp
multiset<int> values = {1, 3, 5, 7, 9};

auto it_ge = values.lower_bound(5); // points to 5 (first element >= 5)
auto it_gt = values.upper_bound(5); // points to 7 (first element > 5)
```

Both queries execute in $O(\log k)$ time, where $k$ is the number of elements in the multiset.

---

### Part 3: Q&A: How to Call Upper Bound on a Set or Multiset

**Question:** How should `upper_bound` be invoked on a `std::set` or `std::multiset`?

**Answer:** **Always use the member function `s.upper_bound(val)`, never the generic algorithm `std::upper_bound(s.begin(), s.end(), val)`.**

```cpp
multiset<int> s = {2, 4, 6, 8};

// Correct: O(log k) member function
auto it1 = s.upper_bound(4);

// INCORRECT: O(k) linear time!
// std::upper_bound on bidirectional tree iterators cannot jump;
// it advances step-by-step, degrading to O(k).
auto it2 = upper_bound(s.begin(), s.end(), 4);
```

Using the generic `std::upper_bound` algorithm on trees is a common pitfall that turns an $O(n \log m)$ solution into $O(n \cdot m)$, causing Time Limit Exceeded (TLE).

---

### Part 4: Q&A: Searching for the Latest Value Less Than a Target ($<$)

**Question:** What if we need the opposite query: finding the **largest (latest) value strictly less than** a given target value ($<$)?

In our problem, we need the compatible room with the largest end time strictly less than `class.start`.

There are multiple ways to implement this:

#### Way 1: `prev(lower_bound)` in a Default (Ascending) Multiset

In an ascending multiset, `s.lower_bound(x)` finds the first element $\ge x$. The element immediately preceding it (`std::prev(it)`) is the largest element $< x$.

```cpp
multiset<int> s = {2, 5, 8, 12};
int target = 8;

auto it = s.lower_bound(target); // points to 8 (first >= 8)
if (it != s.begin()) {
    auto pred = prev(it); // points to 5 (largest < 8)
} else {
    // Every element is >= target, no smaller element exists
}
```

*Tradeoff:* Requires checking `it != s.begin()` to avoid undefined iterator behavior when no smaller element exists.

#### Way 2: Storing Negated Values

Store `-end_time` in a standard multiset. Finding the largest `end_time < target` is equivalent to finding the smallest `-end_time > -target`, which maps to `upper_bound(-target)`.

*Tradeoff:* Adding negations throughout the codebase adds mental overhead and potential sign bugs.

#### Way 3 (The Cleanest & Most Idiomatic): Custom Comparator `multiset<int, greater<>>`

By defining the multiset with `greater<>`, elements are stored in descending order (largest to smallest).

```cpp
multiset<int, greater<>> room_end_times;
```

In C++, `container.upper_bound(x)` finds the first element $y$ where `comparator(x, y)` is true.
With `comparator = greater<>()`, `comparator(x, y)` evaluates `x > y` (meaning $y < x$).

Because the multiset is ordered descendingly, the very first element satisfying $y < x$ is guaranteed to be the **maximum element strictly less than $x$**:

```cpp
multiset<int, greater<>> room_end_times = {12, 8, 5, 2};
int target = 8;

// Directly finds the first element where 8 > y (y < 8).
// In descending order, that first element is 5!
auto it = room_end_times.upper_bound(target);

if (it != room_end_times.end()) {
    cout << "Largest room end time < 8 is: " << *it << "\n"; // prints 5
}
```

If no element in the multiset is $< target$, `it == room_end_times.end()`. No manual iterator decrements or `begin()` checks are required.

---

## Solution

[`solution.cpp`](solution.cpp): greedy scheduling with sorted classes and a descending multiset of room end times.

- We sort all classes by end time ascending, breaking ties by start time ascending.
- We maintain `room_end_times`, a `multiset<int, greater<>>` storing the end time of the active class in each occupied room.
- For each class `c`:
  - Query `it = room_end_times.upper_bound(c.start)` to find the latest room end time strictly less than `c.start`.
  - If a compatible room is found (`it != room_end_times.end()`):
    - Erase this room's old end time using `room_end_times.erase(it)` (erasing by iterator removes only one instance).
    - Insert the new end time `room_end_times.insert(c.end)`.
    - Increment the count of scheduled classes.
  - If no compatible room is found:
    - If the number of occupied rooms is less than $m$ (`room_end_times.size() < m`), open a new room by inserting `c.end` and incrementing the count.
    - If all $m$ rooms are occupied with end times $\ge c.start$, class `c` cannot be scheduled.

## Correctness

- **Claim:** Greedily scheduling classes in increasing order of end time and assigning each to the compatible room with the maximum end time maximizes the total number of scheduled classes.
- **Proof Sketch (Exchange Argument):**
  - Earliest finish time first is optimal for interval scheduling: choosing a class that finishes earlier frees up a room earlier than a class that finishes later, providing a superset of future scheduling opportunities.
  - Among compatible rooms with end times $< a.start$, picking the room with the maximum end time leaves rooms with smaller end times intact. Since a smaller end time is compatible with more future start times, preserving smaller end times dominates preserving larger end times.
  - Any optimal schedule that deviates from this choice can be transformed step-by-step into the greedy schedule without reducing the total number of scheduled classes.

## Complexity

Let $n$ be the number of classes and $m$ be the number of rooms:

- **Time:**
  - Sorting $n$ classes takes $O(n \log n)$ time.
  - The multiset contains at most $m$ room end times.
  - For each of the $n$ classes, `upper_bound`, `erase`, and `insert` each take $O(\log m)$ time.
  - Total time: $O(n \log n + n \log m)$, which comfortably runs within the 2.0-second time limit for $n, m \le 200\,000$.
- **Space:**
  - $O(n)$ to store the array of classes.
  - $O(m)$ auxiliary space for the multiset of room end times.
  - Total space: $O(n + m)$.
