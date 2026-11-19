# Week 09, Day 1 (October 20, 2026)

## Today

Today we explore greedy scheduling algorithms and priority queue simulation:
- **Greedy Scheduling with Cooldown:** [Task Scheduler](https://leetcode.com/problems/task-scheduler/) ([LeetCode 621](https://leetcode.com/problems/task-scheduler/)).

You can write and test your code without any local setup using the [Online IDE Guide](../misc_references/online-ide.md) ([Judge0 IDE](https://ide.judge0.com/)).

---

<details>
<summary>1. Explanation: Motivation, Solution Derivation, and Correctness</summary>

### The Problem and the Bottleneck

We are given a list of CPU tasks, where each task takes exactly 1 unit of time to execute. There is a cooldown constraint: between any two executions of the same task, there must be at least `n` units of time. During any time unit, the CPU can either execute an available task or sit idle.

Our objective is to find the minimum total time required to complete all tasks.

Why does this problem require careful planning?
If all tasks were unique, the order would not matter at all. The CPU would simply execute all tasks consecutively with zero idle time in exactly `len(tasks)` units.

The entire challenge arises from duplicate tasks and the cooldown constraint `n`. When a task executes, it becomes unavailable for the next `n` intervals. If we run out of other tasks to interleave during that waiting window, the CPU has no choice but to sit idle. Every idle cycle represents wasted time that extends the total schedule. Minimizing total time is therefore completely equivalent to **minimizing CPU idle slots**.

### Solution Derivation: Where Does Idle Time Come From?

To derive the strategy, consider what determines the length of the schedule:

1. **The Most Frequent Task Dictates the Scaffold:**
   Suppose task `A` occurs 4 times and the cooldown is `n = 2`.
   The four instances of `A` cannot be packed together. They require a scaffold:
   `A _ _ A _ _ A _ _ A`
   Notice that `A` creates 3 separate cooldown chunks between its executions. Each chunk requires at least 2 units of other tasks or idle cycles. That means `A` alone demands at least $3 \times 2 = 6$ non-`A` slots to avoid stalling the CPU.

2. **The Danger of Scheduling Rare Tasks Early:**
   Suppose we also have tasks `B` and `C`, each appearing only once.
   What happens if we schedule `B` and `C` first?
   - Times 0 and 1: Run `B`, then `C`. Both are now completely finished.
   - We now have only the 4 copies of `A` left.
   - Because `B` and `C` have already been burned, there are no other tasks available to fill the gaps between copies of `A`.
   - The CPU is forced to idle: `B -> C -> A -> idle -> idle -> A -> idle -> idle -> A -> idle -> idle -> A`.
   - Total time: 12 intervals (6 idle slots).

3. **Greedy Interleaving:**
   What happens if we prioritize `A` first instead?
   - `A -> B -> C -> A -> idle -> idle -> A -> idle -> idle -> A`
   - Notice that `B` and `C` were placed directly into the cooldown gap of `A`, reducing idle slots.
   - If we have multiple frequent tasks (for example, four `A`s and four `B`s), interleaving them preserves our options and fills gaps naturally: `A -> B -> idle -> A -> B -> idle -> A -> B -> idle -> A -> B`.

This leads to our primary intuition:
**The task with the largest remaining frequency creates the largest future idle risk.**
To minimize idle slots, whenever the CPU is ready to schedule a task, it must greedily pick whichever available task has the highest remaining count.

### Correctness Intuition: The Greedy Choice Property

Why is choosing the highest remaining frequency always optimal?

- **Exchange Argument:**
  Suppose at time $t$, task $X$ has more remaining copies than task $Y$, and both are currently eligible to run.
  If we choose to schedule $Y$ instead of $X$:
  - $X$ is delayed, pushing its future availability further back.
  - Since $X$ has more instances to complete, delaying $X$ prolongs the chain of future cooldown gaps that $X$ will require.
  - Toward the end of the schedule, when lower-frequency tasks have been exhausted, the remaining copies of $X$ will have nothing left to interleave with, forcing extra idle cycles.
  - Swapping $X$ in place of $Y$ at time $t$ can only reduce or maintain the number of trailing idle slots, never increase them.

### The Two-State Conceptual Model

From the perspective of the scheduler, at any given time unit, every task type belongs to one of two states:
1. **Ready to Execute:** The task has never run, or at least `n` units of time have passed since its last execution.
2. **In Cooldown:** The task ran recently and is waiting for its mandatory `n` units to expire.

This leads directly to the simulation lifecycle:
- At each clock tick:
  - If tasks are **Ready**, select the ready task with the **maximum remaining frequency**, execute it for 1 unit, and transition it into **Cooldown** (if it still has copies left).
  - Check if any task in **Cooldown** has finished its waiting window. If so, transition it back to **Ready**.
  - If no tasks are **Ready**, the CPU must **idle** for 1 unit while waiting for cooling tasks to become eligible.
  - Advance the clock.

</details>

---

<details>
<summary>2. Hints</summary>

1. High-frequency tasks create the biggest scheduling bottlenecks. If you schedule rare tasks first, what happens when only copies of the most frequent task remain?
2. At any point in time, what are the two possible states a task can be in?
3. Which abstract data type lets you efficiently query and extract the task with the largest remaining frequency from the available pool?
4. When a task is executed at timestamp `cur_time`, at what timestamp is it allowed to run again?
5. How does the simulation know when the CPU is idle versus busy executing a task?

</details>

---

<details>
<summary>3. More Hints</summary>

1. **Ready Pool (Max-Heap):**
   - You need rapid access to the maximum frequency among all ready tasks.
   - In Python, `heapq` is a min-heap by default. You can simulate a max-heap by storing negated counts (e.g. `-count`).
   - In C++, `std::priority_queue<int>` is a max-heap by default.
2. **Cooldown Line (Waiting Queue):**
   - For tasks in cooldown, what information must you track? Each entry needs two pieces of data: the remaining count and the `ready_time`.
   - Do you need a priority queue for the cooldown line as well? Notice that tasks are dispatched at strictly increasing timestamps `cur_time`, so `ready_time = cur_time + n` is strictly non-decreasing. A standard FIFO queue (`deque` in Python, `std::queue` in C++) naturally maintains elements in chronological order of readiness.
3. **Idle Handling:**
   - At clock tick `cur_time`, what does an empty ready pool mean? It means all unfinished tasks are currently cooling down. The CPU idles for this tick, and you advance `cur_time` by 1.

</details>

---

<details>
<summary>4. High Level Pseudocode</summary>

```text
function leastInterval(tasks, n):
    // Part 1: Frequency counting and max-heap
    counts = frequency map of tasks
    max_heap = build max-heap from counts.values()

    // Part 2: Waiting queue and clock
    wait_queue = empty FIFO queue of (count, ready_time)
    cur_time = 0

    // Part 3: Simulation loop
    while max_heap is not empty OR wait_queue is not empty:
        // Part 3a: Execute highest frequency available task
        if max_heap is not empty:
            count = pop max from max_heap
            count = count - 1
            if count > 0:
                push (count, cur_time + n) to wait_queue

        // Part 3b: Cooldown expiration check
        if wait_queue is not empty AND wait_queue.front.ready_time == cur_time:
            (count, ready_time) = pop front from wait_queue
            push count to max_heap

        // Part 3c: Advance time
        cur_time = cur_time + 1

    return cur_time
```

</details>

---

<details>
<summary>5. Starting Code (Python and C++)</summary>

Open the [Judge0 Online IDE](https://ide.judge0.com/) or your local environment. Each comment below corresponds to one part of the high level pseudocode. Implement each part and test your solution with your own test inputs.

### Python Starting Code

```python
from collections import Counter, deque
import heapq


class Solution:
    def leastInterval(self, tasks: list[str], n: int) -> int:
        # Part 1: Count task frequencies and build a max-heap
        # Hint: Python heapq is a min-heap, so store negated counts (-c).

        # Part 2: Initialize waiting queue and simulation clock
        # wait_q holds pairs of (-count, ready_time).
        # cur_time starts at 0.

        # Part 3: Main simulation loop
        # Run while there are tasks in the heap OR tasks cooling down in wait_q.

            # Part 3a: Schedule the most frequent available task
            # If the max-heap has available tasks:
            # Pop the highest frequency task, decrement its count (add 1 to negative value),
            # and if count != 0, append (count, cur_time + n) to wait_q.

            # Part 3b: Return ready tasks to the max-heap
            # If wait_q has a task at the front whose ready_time == cur_time:
            # Pop it from wait_q and push its count back into the max-heap.

            # Part 3c: Advance the clock
            # Increment cur_time by 1 (accounts for task execution or idle cycle).

        # Part 4: Return total time
        pass
```

### C++ Starting Code

```cpp
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    int leastInterval(vector<char> &tasks, int n) {
        // Part 1: Count task frequencies and populate max-heap
        // Count frequencies of tasks 'A' to 'Z', then push positive counts to priority_queue<int>.

        // Part 2: Initialize waiting queue and simulation clock
        // queue<pair<int, int>> waitQueue stores (count, readyTime).
        // int curTime starts at 0.

        // Part 3: Main simulation loop
        // Run while maxHeap is not empty OR waitQueue is not empty.

            // Part 3a: Schedule the most frequent available task
            // If maxHeap is not empty:
            // Pop the top task, decrement count, and if count > 0, push {count, curTime + n} to waitQueue.

            // Part 3b: Return ready tasks to the max-heap
            // If waitQueue is not empty and front task has readyTime == curTime:
            // Pop from waitQueue and push count back into maxHeap.

            // Part 3c: Advance the clock
            // Increment curTime by 1 (accounts for task execution or idle cycle).

        // Part 4: Return total time
        return 0;
    }
};
```

</details>

---

<details>
<summary>6. Theoretical Discussion and Pause</summary>

> [!NOTE]
> **Pause and Discuss:** Before viewing the solution code, take time to trace the algorithm and discuss the theoretical mechanics:
> 
> 1. **Greedy Choice Property:** Why does prioritizing the task with the highest remaining frequency minimize idle slots? What would happen if we prioritized tasks with lower remaining frequencies instead?
> 2. **Monotonicity of Ready Times:** Why is a standard FIFO queue sufficient for tracking cooldowns rather than a second priority queue? Under what condition would a FIFO queue fail to preserve chronological order?
> 3. **Implicit Idle Accounting:** How does this simulation handle idle intervals? Where in the loop is an idle slot registered, and why is no separate `idle_count` variable needed?
> 4. **By-Hand Trace:** Walk through `tasks = ["A", "A", "A", "B", "B", "B"], n = 2` on paper or the whiteboard to verify when each task is pushed and popped.

</details>

---

<details>
<summary>7. Solutions and Code Explanation (Python and C++)</summary>

### Code Explanation: How the Simulation Operates

Now let us examine how the theoretical two-state model maps directly to concrete code:

1. **State 1: Ready Tasks (`counts` / `maxHeap`)**
   - We extract task frequencies from the input. Notice that the specific letters ('A', 'B', etc.) do not matter for the schedule length, only their remaining counts matter.
   - Python's `heapq` module is a min-heap by default. We store negated frequencies `-c` so that `heappop()` returns the task with the largest count (most negative value).
   - In C++, `std::priority_queue<int>` is a max-heap by default, so we push positive integers directly.
2. **State 2: Cooling Tasks (`wait_q` / `waitQueue`)**
   - When a task is executed, its remaining count is decremented. If it still has copies remaining, it enters the cooldown queue with `ready_time = cur_time + n`.
   - In Python, adding 1 to `-c` moves it closer to 0 (e.g. `-3 + 1 = -2`). If `count != 0`, we enqueue `(count, cur_time + n)`.
   - In C++, subtracting 1 from `count` reduces the count (e.g. `3 - 1 = 2`). If `count > 0`, we enqueue `{count, curTime + n}`.
3. **Cooldown Expiry Check**
   - At each time step, before or after dispatching a task, we inspect the front of the cooldown queue.
   - If `wait_q[0][1] == cur_time` (or `waitQueue.front().second == curTime`), the earliest cooling task has completed its mandatory $n$ intervals. We pop it from the queue and push its count back into the max-heap, making it eligible for future scheduling.
4. **Clock and Idle Ticks**
   - If `counts` (or `maxHeap`) is empty when scheduling occurs, no task is popped. The CPU does nothing during this interval.
   - Regardless of whether a task executed or the CPU idled, `cur_time` increments by 1.
   - When both the heap and the cooldown queue are empty, every task has finished, and `cur_time` represents the total makespan.

### Python Solution

```python
from collections import Counter, deque
import heapq


class Solution:
    def leastInterval(self, tasks: list[str], n: int) -> int:
        counts = [-c for c in Counter(tasks).values()]
        heapq.heapify(counts)
        wait_q = deque()  # (-count, ready_time)

        cur_time = 0

        while counts or wait_q:
            if counts:
                count = heapq.heappop(counts) + 1
                if count != 0:
                    wait_q.append((count, cur_time + n))

            if wait_q and wait_q[0][1] == cur_time:
                count, ready_time = wait_q.popleft()
                heapq.heappush(counts, count)

            cur_time += 1

        return cur_time
```

### C++ Solution

```cpp
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    int leastInterval(vector<char> &tasks, int n) {
        vector<int> freq(26, 0);
        for (char task : tasks) {
            freq[task - 'A']++;
        }

        priority_queue<int> maxHeap;
        for (int count : freq) {
            if (count > 0) {
                maxHeap.push(count);
            }
        }

        queue<pair<int, int>> waitQueue;
        int curTime = 0;

        while (!maxHeap.empty() || !waitQueue.empty()) {
            if (!maxHeap.empty()) {
                int count = maxHeap.top() - 1;
                maxHeap.pop();
                if (count > 0) {
                    waitQueue.push({count, curTime + n});
                }
            }

            if (!waitQueue.empty() && waitQueue.front().second == curTime) {
                int count = waitQueue.front().first;
                waitQueue.pop();
                maxHeap.push(count);
            }

            curTime++;
        }

        return curTime;
    }
};
```

### Code Links

- [Problem Description and Complexity Analysis](../problem_solutions/task-scheduler/README.md)
- [Python Solution](../problem_solutions/task-scheduler/solution.py)
- [C++ Solution](../problem_solutions/task-scheduler/solution.cpp)

</details>
