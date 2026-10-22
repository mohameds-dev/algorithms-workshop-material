# Week 09, Day 2 (October 22, 2026)

## Today

Today we look at scheduling problems and how to track available rooms:
1. **Can one person attend all meetings?** [Meeting Rooms](https://neetcode.io/problems/meeting-schedule) (LeetCode 252 / NeetCode Meeting Schedule).
2. **How many rooms do we need?** [Meeting Rooms II](https://neetcode.io/problems/meeting-schedule-ii) (LeetCode 253 / NeetCode Meeting Schedule II) using a custom comparator and a descending multiset (`multiset<int, greater<>>` with `lower_bound`).
3. **For Practice (Stretch Problem):** [Classrooms](https://open.kattis.com/problems/classrooms) (Kattis) where the number of rooms is fixed and we want to fit as many classes as possible.

You can write and test your code without any local setup using the [Online IDE Guide](../misc_references/online-ide.md) ([Judge0 IDE](https://ide.judge0.com/)).

---

<details>
<summary>1. Meeting Rooms: Can You Attend All Meetings? (LeetCode 252 / NeetCode)</summary>

### Problem

Given an array of meeting time intervals consisting of start and end times `[[start_1, end_1], [start_2, end_2], ...]`, determine if a person could attend all meetings.

[NeetCode: Meeting Schedule](https://neetcode.io/problems/meeting-schedule)

### Intuition

We have one person. If any two meetings overlap in time, the person cannot attend both.

1. **Sort by Start Time:**
   If meetings are given out of order, checking for conflicts would require comparing every pair in $O(n^2)$ time. By sorting meetings in chronological order of their start times, any scheduling conflict must occur between two adjacent intervals in the sorted sequence.

2. **Adjacent Overlap Check:**
   After sorting, meeting $i$ finishes at `intervals[i].end` and the next meeting begins at `intervals[i + 1].start`.
   If `intervals[i].end > intervals[i + 1].start`, meeting $i$ has not concluded before the next meeting begins. Attending both is impossible, so we return `False`.
   If the loop finishes without detecting any overlap, return `True`.

### Python Solution

```python
from typing import List


class Interval:
    def __init__(self, start: int, end: int):
        self.start = start
        self.end = end


class Solution:
    def canAttendMeetings(self, intervals: List[Interval]) -> bool:
        intervals.sort(key=lambda i: i.start)
        for i in range(len(intervals) - 1):
            if intervals[i].end > intervals[i + 1].start:
                return False

        return True
```

### C++ Solution

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Interval {
public:
    int start, end;
    Interval(int start, int end) {
        this->start = start;
        this->end = end;
    }
};

class Solution {
public:
    bool canAttendMeetings(vector<Interval> &intervals) {
        sort(intervals.begin(), intervals.end(), [](const Interval &a, const Interval &b) {
            return a.start < b.start;
        });

        for (size_t i = 0; i + 1 < intervals.size(); i++) {
            if (intervals[i].end > intervals[i + 1].start) {
                return false;
            }
        }

        return true;
    }
};
```

### Code Links

- [Problem Description and Complexity Analysis](../problem_solutions/meeting-rooms/README.md)
- [Python Solution](../problem_solutions/meeting-rooms/solution.py)
- [C++ Solution](../problem_solutions/meeting-rooms/solution.cpp)

</details>

---

<details>
<summary>2. Meeting Rooms II: How Many Rooms Do We Need? (LeetCode 253 / NeetCode)</summary>

### Problem

Given an array of meeting time intervals consisting of start and end times `[[start_1, end_1], [start_2, end_2], ...]`, find the minimum number of conference rooms required to hold all meetings without conflicts.

[NeetCode: Meeting Schedule II](https://neetcode.io/problems/meeting-schedule-ii)

### Problem Intuition and Solution Derivation

In Meeting Rooms I, we only had 1 person or 1 room. Now, all meetings must happen without conflicts, and we want to find the minimum number of rooms needed.

1. **Processing in Chronological Order:**
   We sort meetings primarily by start time ascending. This models chronological time: as meetings begin, we allocate rooms as needed.

2. **Tracking Room Availability:**
   What matters about a room? Not its room number, but **when it becomes available next** (its end time).
   When meeting `i` arrives at `i.start`:
   - Any room whose previous meeting ended at or before `i.start` (`room_end <= i.start`) is free and can be reused.
   - If multiple rooms are free, which one should we reuse?
     We pick the room whose previous meeting ended latest (largest end time $\le i.start$). This leaves earlier-freed rooms available for other meetings.
   - If no existing room is free at `i.start`, we must open a new room.

3. **Data Structure Choice:**
   We need a dynamic container of room end times that supports:
   - Querying for the largest value $\le i.start$.
   - Erasing that old end time and inserting the new finish time `i.end`.
   A balanced binary search tree (`std::multiset`) provides both operations in $O(\log k)$ time.

### High-Level Pseudocode

```text
function minMeetingRooms(intervals):
    sort intervals by start time ascending (break ties by end time ascending)
    initialize room_available as an empty multiset sorted in descending order

    for each meeting in intervals:
        // Find the room with the latest available time <= meeting.start
        target_room = find room in room_available with largest time <= meeting.start

        if target_room exists:
            remove target_room from room_available

        insert meeting.end into room_available

    return size of room_available
```

### Problem Breakdown and Technical Concepts

#### Part A (Q&A): How to Store and Sort Intervals with a Custom Comparator

**Question:** How do we define and sort intervals by start time, breaking ties by end time?

**Answer:**
In C++, write a custom comparator function:

```cpp
bool compareIntervals(const Interval &a, const Interval &b) {
    return a.start < b.start or (a.start == b.start and a.end < b.end);
}

// In method:
sort(intervals.begin(), intervals.end(), compareIntervals);
```

In Python, sort using a tuple key:
```python
intervals.sort(key=lambda i: (i.start, i.end))
```

#### Part B (Q&A): Searching for Available Rooms in a Descending Multiset

**Question:** Why does `room_available.lower_bound(i.start)` on `multiset<int, greater<>>` return the largest room end time that is $\le i.start$?

**Answer:**
- By C++ specification, `container.lower_bound(x)` finds the first element $y$ where `comparator(y, x)` is false.
- Under `greater<>`, `comparator(y, x)` evaluates `y > x`. The condition `y > x` is false precisely when $y \le x$.
- Because elements in `multiset<int, greater<>>` are ordered in descending order (highest to lowest), the very first element satisfying $y \le x$ is guaranteed to be the **maximum element $\le x$**.
- If no room has finished by `i.start`, `it == room_available.end()`.
- If a room is found (`it != room_available.end()`), we reuse it by erasing: `room_available.erase(it)`.
- We then insert the meeting's finish time: `room_available.insert(i.end)`.
- When all meetings have been processed, `room_available.size()` is the minimum number of rooms needed.

### Starting Code (C++)

```cpp
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * };
 */

// Part 1: Implement the custom comparator
// Sort primarily by start time ascending, breaking ties by end time ascending.
bool compareIntervals(const Interval &a, const Interval &b) {
    // Your code here
    return false;
}

class Solution {
public:
    int minMeetingRooms(vector<Interval> &intervals) {
        // Part 2: Sort intervals using compareIntervals

        // Part 3: Set up descending multiset to track room availability
        // Hint: multiset<int, greater<>> room_available;

        // Part 4: Iterate through intervals and allocate rooms
        // For each interval i:
        // a. Query room_available.lower_bound(i.start).
        // b. If a compatible room is found (it != room_available.end()):
        //    - Erase the old availability time (erase by iterator!).
        // c. Insert i.end into room_available.

        // Part 5: Return total rooms used
        return 0;
    }
};
```

### Theoretical Discussion and Pause

> [!NOTE]
> **Pause and Discuss:** Before checking the solution code, discuss these theoretical mechanics:
> 
> 1. **Start Time vs. End Time Sorting:** Why do we sort by start time in Meeting Rooms II, whereas in interval scheduling we often sort by end time? (Hint: in Meeting Rooms II, we cannot drop any meeting; all must be served in chronological order).
> 2. **Lower Bound with `greater<>`:** Verify on paper why `lower_bound` on a descending multiset yields $\le$, whereas on a default ascending multiset it yields $\ge$.
> 3. **Erase by Iterator:** Why must we call `room_available.erase(it)` instead of `room_available.erase(*it)`?

### Full Solution (C++)

```cpp
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Interval {
public:
    int start, end;
    Interval(int start, int end) {
        this->start = start;
        this->end = end;
    }
};

bool compareIntervals(const Interval &a, const Interval &b) {
    return a.start < b.start or (a.start == b.start and a.end < b.end);
}

class Solution {
public:
    int minMeetingRooms(vector<Interval> &intervals) {
        sort(intervals.begin(), intervals.end(), compareIntervals);
        multiset<int, greater<>> room_available;

        for (auto &i : intervals) {
            auto it = room_available.lower_bound(i.start);
            // if room exists such that its next available time <= our start time
            // we book it, and update its next available time
            if (it != room_available.end()) {
                room_available.erase(it); // remove old available time
            }
            // else, we reserve anyway
            room_available.insert(i.end); // insert the end time of our class
        }
        return room_available.size();
    }
};
```

### Code Links

- [Problem Description and Complexity Analysis](../problem_solutions/meeting-rooms-ii/README.md)
- [Python Solution](../problem_solutions/meeting-rooms-ii/solution.py)
- [C++ Solution](../problem_solutions/meeting-rooms-ii/solution.cpp)

</details>

---

<details>
<summary>3. For Practice (Stretch Problem): Classrooms (Kattis)</summary>

### Comparing Meeting Rooms II vs. Classrooms

Notice the fundamental contrast between the two problems:
- **Meeting Rooms II:** You **must** schedule **all** meetings. You have unlimited rooms and want to find the **minimum number of rooms** required.
  - Sorting rule: sort by **start time** to process requests chronologically.
  - Query rule: non-strict inequality $\le$ (`lower_bound` on `greater<>`).
- **Classrooms (Kattis):** The number of rooms $m$ is **fixed**, and you want to **maximize the number of classes scheduled** (some classes may have to be dropped!).
  - Sorting rule: sort by **end time** (Earliest Finish Time first) to maximize remaining capacity for future classes.
  - Query rule: strict inequality $<$ (`upper_bound` on `greater<>`), because Kattis specifies that a new class cannot start at the exact same minute another finishes ($s_j > f_i$).

[Kattis: Classrooms](https://open.kattis.com/problems/classrooms)

### Problem Overview

You are given $n$ classes and $m$ rooms. Each class has a start time and an end time. A room can host at most one class at a time, and a class can begin in a room if and only if the previous class finished strictly before the new class starts (`previous_end < new_start`). Find the maximum number of classes that can be scheduled across the $m$ rooms.

### High-Level Pseudocode

```text
function scheduleClasses(classes, m):
    sort classes by end time ascending (break ties by start time ascending)
    initialize room_end_times as an empty multiset in descending order
    answer = 0

    for each class in classes:
        // Find the room with the largest end time strictly less than class.start
        target_room = find room in room_end_times with maximum value < class.start

        if target_room exists:
            remove target_room from room_end_times
            insert class.end into room_end_times
            answer = answer + 1
        else if size of room_end_times < m:
            insert class.end into room_end_times
            answer = answer + 1
        else:
            // Class cannot be accommodated; skip it
            pass

    return answer
```

### Why `upper_bound` for Strict Inequality ($<$)

In a descending multiset (`multiset<int, greater<>>`), `container.upper_bound(x)` finds the first element $y$ where `comparator(x, y)` is true.
With `comparator = greater<>()`, `comparator(x, y)` evaluates `x > y` (which means $y < x$).

Because the multiset is ordered descendingly, the very first element satisfying $y < x$ is guaranteed to be the **maximum element strictly less than $x$**:

```cpp
multiset<int, greater<>> room_end_times = {12, 8, 5, 2};
int target = 8;

// Finds the first element where 8 > y (y < 8).
// In descending order, that first element is 5!
auto it = room_end_times.upper_bound(target);

if (it != room_end_times.end()) {
    cout << "Largest room end time < 8 is: " << *it << "\n"; // prints 5
}
```

### C++ Solution

```cpp
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct Class {
    int start, end;
};

bool compare_classes(const Class &a, const Class &b) {
    if (a.end == b.end)
        return a.start < b.start;

    return a.end < b.end;
}

int main() {
    int num_classes, num_rooms;
    cin >> num_classes >> num_rooms;

    vector<Class> classes(num_classes);

    for (int i = 0; i < num_classes; ++i) {
        int a, b;
        cin >> a >> b;
        classes[i] = {a, b};
    }

    sort(classes.begin(), classes.end(), compare_classes);

    // Track when each occupied room becomes free
    multiset<int, greater<>> room_end_times;
    int answer = 0;
    for (const auto &c : classes) {
        auto it = room_end_times.upper_bound(c.start);

        if (it == room_end_times.end()) {
            if ((int)room_end_times.size() < num_rooms) {
                room_end_times.insert(c.end);
                answer++;
            }
        } else {
            room_end_times.erase(it);
            room_end_times.insert(c.end);
            answer++;
        }
    }

    cout << answer << "\n";
    return 0;
}
```

### Code Links

- [Problem Description and Complexity Analysis](../problem_solutions/classrooms/README.md)
- [C++ Solution](../problem_solutions/classrooms/solution.cpp)

</details>
