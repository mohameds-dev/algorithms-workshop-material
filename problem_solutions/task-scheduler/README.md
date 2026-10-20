# Task Scheduler

LeetCode 621: https://leetcode.com/problems/task-scheduler/

- Difficulty: Medium
- Topics: Array, Hash Table, Greedy, Queue, Heap (Priority Queue), Counting
- Discussed: [Week 9, Day 1](../../weekly_material/week09_day1.md)

## Summary

Given an array of CPU `tasks` represented by uppercase English letters and a non-negative integer `n` representing the cooldown interval, determine the minimum number of CPU intervals required to complete all tasks. Between any two executions of the same task, there must be at least `n` intervals of other tasks or idle time.

## Hints

<details>
<summary>Hints</summary>

1. Which task should you execute first? If a task has a very high frequency, delaying its execution will leave empty cooldown slots at the end with no other tasks available to interleave.
2. A greedy choice is optimal: at each step, prioritize the task that has the highest remaining frequency among all currently available tasks.
3. How can you track which tasks are currently cooling down? Use a queue storing pairs: `(remaining_count, ready_time)`.
4. How can you efficiently retrieve the available task with the maximum frequency? Use a max-heap (priority queue).
5. At each clock tick `cur_time`:
   - Pop the most frequent task from the max-heap, decrement its count, and if it still has remaining instances, enqueue it into the waiting queue with `ready_time = cur_time + n`.
   - Check if the task at the front of the waiting queue has satisfied its cooldown (`ready_time == cur_time`). If so, move it back into the max-heap.
   - Advance `cur_time` by 1.

</details>

## Solution

[`solution.py`](solution.py) / [`solution.cpp`](solution.cpp): greedy scheduling with max-heap and waiting queue.

- **Greedy Strategy:** At each time unit, schedule the available task with the largest remaining count. Leaving high-frequency tasks for later forces extra idle slots at the tail of the schedule.
- **Max-Heap:** Holds counts of tasks that are currently available to execute. Python's `heapq` is a min-heap by default, so we store negative counts (`-c`) to simulate a max-heap. In C++, `std::priority_queue<int>` is a max-heap by default.
- **Cooldown Queue:** A FIFO queue holds `(remaining_count, ready_time)`. Because tasks are scheduled at strictly increasing timestamps `cur_time`, their `ready_time = cur_time + n` values are strictly increasing, preserving FIFO order.
- **Simulation Step:**
  1. If the max-heap has available tasks, pop the highest frequency task, decrement its count, and enqueue it into `wait_q` if `count > 0` (or `count != 0` in Python).
  2. If the front of `wait_q` has `ready_time == cur_time`, dequeue it and re-insert its count into the max-heap.
  3. Increment `cur_time`. If the heap was empty when attempting to schedule, this tick represents an idle slot.
  4. Repeat until both the max-heap and waiting queue are empty.

## Correctness

- **Claim:** The simulation produces a valid schedule respecting the cooldown constraint $n$, and greedy selection of the highest remaining count minimizes total intervals.
- **Initialization:** At `cur_time = 0`, the max-heap contains all initial positive task counts, `wait_q` is empty, no task has executed, and cooldown constraints are vacuously satisfied.
- **Maintenance:** In each step at `cur_time`:
  - An available task is chosen only from the max-heap. Since any task currently cooling down is held in `wait_q`, no task executes within $n$ steps of its prior execution.
  - When a task executes, its next allowed execution time is set to `cur_time + n`. It cannot re-enter the max-heap until `cur_time` reaches `ready_time`, guaranteeing at least $n$ units of separation.
  - If no task is available in the max-heap, the CPU idles for 1 unit while waiting for cooling tasks.
  - By scheduling the task with the highest remaining frequency, we maximize the opportunity to interleave other tasks during its cooldown, minimizing required idle cycles.
- **Termination:** The loop terminates when both the max-heap and `wait_q` are empty, meaning every instance of every task has executed. `cur_time` equals the exact number of executed task slots plus idle slots.

## Complexity

Let $N$ be the total number of tasks in `tasks`, and let $k$ be the number of distinct task types ($k \le 26$):

- **Time:** $O(N)$ effective time. Frequency counting takes $O(N)$ time. The max-heap and queue contain at most $k \le 26$ elements, so each heap push and pop takes $O(\log 26) = O(1)$ time. The total number of intervals is at most $O(N \cdot n)$, with each interval processed in $O(1)$ operations.
- **Space:** $O(1)$ auxiliary space, since the frequency counter, max-heap, and waiting queue store at most 26 elements.
