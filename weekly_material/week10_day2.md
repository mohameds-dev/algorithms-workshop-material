# Week 10, Day 2 (October 29, 2026)

## Today

Today we cover three high-yield array and hash set patterns:
1. **Meeting Rooms II Revisited:** Quick review of the descending multiset solution, followed by the two-pointer chronological timeline approach for [Meeting Rooms II](https://neetcode.io/problems/meeting-schedule-ii) (LeetCode 253 / NeetCode).
2. **Prefix and Suffix Accumulations:** [Products of Array Discluding Self](https://neetcode.io/problems/products-of-array-discluding-self/) (LeetCode 238 / NeetCode) without using the division operation in $O(n)$ time.
3. **Hash Set Sequence Start Detection:** [Longest Consecutive Sequence](https://neetcode.io/problems/longest-consecutive-sequence/) (LeetCode 128 / NeetCode) in strictly $O(n)$ time.

You can write and test your code without any local setup using the [Online IDE Guide](../misc_references/online-ide.md) ([Judge0 IDE](https://ide.judge0.com/)).

---

<details>
<summary>1. Meeting Rooms II: The Two-Pointer Timeline Approach</summary>

### Quick Review: The Multiset Approach

In our previous session, we tracked room availability by storing each occupied room's finish time in a descending multiset (`multiset<int, greater<>>`). For each meeting in start-time order, we queried for the latest finishing room that became free on or before our start time.

For a full review of that data structure and its implementation, see the [Week 09 Day 2 C++ Multiset Solution](./week09_day2.md#full-solution-c) and its [Descending Multiset Intuition](./week09_day2.md#part-b-qa-searching-for-available-rooms-in-a-descending-multiset).

---

### Pivoting to a New Intuition: Do We Care About Specific Rooms?

Ask yourself this question: when looking for the minimum number of conference rooms, does it matter **which** specific room hosts **which** specific meeting?

No. If Meeting A finishes at 10:00 and Meeting B starts at 10:00, Meeting B can simply use whichever room just opened up. We only care about one number:

> **How many meetings are active at the exact same time?**

The minimum number of rooms needed is simply the **peak number of overlapping meetings** across the entire day.

---

### Deriving the Two-Pointer Solution

Every meeting has two events:
1. **Start Time:** A new room is taken (`currently_reserved += 1`).
2. **End Time:** An existing room is freed (`currently_reserved -= 1`).

If we extract all start times and all end times into separate lists:

1. **Sort Both Lists Chronologically:**
   - `starts = sorted([x.start for x in intervals])`
   - `ends = sorted([x.end for x in intervals])`

2. **Simulate Time with Two Pointers:**
   Let pointer `s` track the next meeting waiting to start, and pointer `e` track the earliest ongoing meeting waiting to end.

3. **Compare `starts[s]` and `ends[e]`:**
   - **Case 1: `starts[s] < ends[e]`**
     The next chronological event is a meeting starting before any ongoing meeting has finished. We must allocate another room:
     ```text
     currently_reserved += 1
     s += 1
     ```
   - **Case 2: `starts[s] >= ends[e]`**
     An ongoing meeting finishes before (or at the exact same moment) the next meeting starts. A room is released and becomes free:
     ```text
     currently_reserved -= 1
     e += 1
     ```

4. **Track the Peak:**
   At each step, record the highest concurrency reached:
   ```text
   answer = max(answer, currently_reserved)
   ```

5. **Stopping Condition:**
   Once `s == len(starts)`, all meetings have already started. Any remaining meetings can only finish and release rooms (`currently_reserved` can only go down). We can safely stop and return `answer`.

---

### Scaffold and Starter Code

Given the standard interval definition:

```python
class Interval(object):
    def __init__(self, start, end):
        self.start = start
        self.end = end
```

Try completing the solution below:

```python
from typing import List


class Solution:
    def minMeetingRooms(self, intervals: List[Interval]) -> int:
        # Step 1: Extract and sort all start times and end times separately
        starts = ...
        ends = ...

        # Step 2: Initialize two pointers and room counters
        s, e = 0, 0
        currently_reserved = 0
        answer = 0

        # Step 3: Advance through events chronologically
        while s < len(starts):
            # Your code here: compare starts[s] with ends[e]
            pass

        return answer
```

<details>
<summary>Hints</summary>

1. If `starts[s] < ends[e]`, a new meeting starts before any room is freed. Increment `currently_reserved` and advance pointer `s`.
2. If `starts[s] >= ends[e]`, an ongoing meeting finishes. Decrement `currently_reserved` and advance pointer `e`.
3. If a meeting ends at time 10 and another starts at time 10, the problem allows the room to be reused immediately. Placing the `>=` in the `else` branch handles this tie cleanly by freeing the room before allocating it.
4. Remember to update `answer = max(answer, currently_reserved)` during each iteration.

</details>

<details>
<summary>Solution</summary>

### Python Solution

```python
from typing import List


class Interval(object):
    def __init__(self, start: int, end: int):
        self.start = start
        self.end = end


class Solution:
    def minMeetingRooms(self, intervals: List[Interval]) -> int:
        starts = sorted([x.start for x in intervals])
        ends = sorted([x.end for x in intervals])

        s, e = 0, 0
        currently_reserved = 0
        answer = 0

        while s < len(starts):
            if starts[s] < ends[e]:
                currently_reserved += 1
                s += 1
            else:  # starts[s] >= ends[e] means an ongoing meeting ended
                currently_reserved -= 1
                e += 1

            answer = max(answer, currently_reserved)

        return answer
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
    int minMeetingRooms(vector<Interval> &intervals) {
        vector<int> starts;
        vector<int> ends;
        starts.reserve(intervals.size());
        ends.reserve(intervals.size());

        for (const auto &item : intervals) {
            starts.push_back(item.start);
            ends.push_back(item.end);
        }

        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());

        size_t s = 0, e = 0;
        int currently_reserved = 0;
        int answer = 0;

        while (s < starts.size()) {
            if (starts[s] < ends[e]) {
                currently_reserved++;
                s++;
            } else {
                currently_reserved--;
                e++;
            }
            answer = max(answer, currently_reserved);
        }

        return answer;
    }
};
```

### Complexity Comparison

| Approach | Time Complexity | Auxiliary Space | Key Advantage |
| :--- | :--- | :--- | :--- |
| **Descending Multiset** | $O(n \log n)$ | $O(n)$ | Assigns meetings to concrete room IDs; useful when room assignments must be tracked. |
| **Two Pointers (Timeline)** | $O(n \log n)$ | $O(n)$ | Minimal logic, contiguous vector operations, very low constant overhead. |

</details>

</details>

---

<details>
<summary>2. Products of Array Discluding Self (LeetCode 238 / NeetCode)</summary>

### Problem

Given an integer array `nums`, return an array `answer` such that `answer[i]` is equal to the product of all elements of `nums` except `nums[i]`.

**Constraints:**
- You must write an algorithm that runs in $O(n)$ time.
- You **cannot** use the division operation.

[NeetCode: Products of Array Discluding Self](https://neetcode.io/problems/products-of-array-discluding-self/) | [LeetCode 238: Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/)

---

### Examples and Tracing

#### Example 1:
- **Input:** `nums = [1, 2, 3, 4]`
- **Calculation for each position:**
  - Index 0: product of `[2, 3, 4]` = 24
  - Index 1: product of `[1, 3, 4]` = 12
  - Index 2: product of `[1, 2, 4]` = 8
  - Index 3: product of `[1, 2, 3]` = 6
- **Output:** `[24, 12, 8, 6]`

#### Example 2 (with zeroes):
- **Input:** `nums = [-1, 1, 0, -3, 3]`
- **Output:** `[0, 0, 9, 0, 0]`

---

### Problem Intuition

Why is this problem interesting?
If division were allowed, we could multiply every number together into a `total_product` and then set `answer[i] = total_product / nums[i]`. But:
1. Division is forbidden by problem constraints.
2. Even if division were permitted, whenever `nums` contains `0`, computing `total_product / 0` throws a division-by-zero error!

Notice what `answer[i]` actually represents:
$$\text{answer}[i] = (\text{product of all numbers to the left of } i) \times (\text{product of all numbers to the right of } i)$$

```text
nums:      [   1,       2,       3,       4   ]
               ^                 ^        ^
             left of 2        index 2   right of 2

For index 2 (value 3):
Left product:  nums[0] * nums[1] = 1 * 2 = 2
Right product: nums[3]           = 4
answer[2] = 2 * 4 = 8
```

If we precalculate:
1. **A `prefix` product array:** where `prefix[i]` is the product of all elements from index `0` up to `i`.
2. **A `suffix` product array:** where `suffix[i]` is the product of all elements from index `n - 1` down to `i`.

Then for any index `i`:
- If `0 < i < n - 1`: `answer[i] = prefix[i - 1] * suffix[i + 1]`
- If `i == 0` (no elements to the left): `answer[0] = suffix[1]`
- If `i == n - 1` (no elements to the right): `answer[n - 1] = prefix[n - 2]`

---

### Starter Code

```python
from typing import List


class Solution:
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        n = len(nums)

        # Step 1: Precalculate prefix products
        prefix = [0] * n
        # Your code here

        # Step 2: Precalculate suffix products
        suffix = [0] * n
        # Your code here

        # Step 3: Combine prefix and suffix products for each index
        answer = [0] * n
        # Your code here

        return answer
```

<details>
<summary>Hints</summary>

1. To build `prefix`: initialize a running variable `product = 1`. As you loop from `0` to `n - 1`, multiply `product *= nums[i]` and store `prefix[i] = product`.
2. To build `suffix`: reset `product = 1`. As you loop backwards from `n - 1` down to `0`, multiply `product *= nums[i]` and store `suffix[i] = product`.
3. To compute `answer[i]`: for middle elements, multiply `prefix[i - 1] * suffix[i + 1]`. Take care of index `0` (where only `suffix[1]` exists) and index `n - 1` (where only `prefix[n - 2]` exists).

</details>

<details>
<summary>Solution</summary>

### Python Solution

```python
from typing import List


class Solution:
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        n = len(nums)
        product = 1
        prefix = [0] * n
        for i in range(n):
            product *= nums[i]
            prefix[i] = product

        product = 1
        suffix = [0] * n
        for i in range(n - 1, -1, -1):
            product *= nums[i]
            suffix[i] = product

        answer = [0] * n
        for i in range(n):
            answer[i] = (
                prefix[i - 1] * suffix[i + 1]
                if 0 < i < n - 1
                else suffix[i + 1] if i == 0 else prefix[i - 1]
            )

        return answer
```

### C++ Solution

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int> &nums) {
        int n = nums.size();
        vector<int> prefix(n, 0);
        int product = 1;
        for (int i = 0; i < n; i++) {
            product *= nums[i];
            prefix[i] = product;
        }

        vector<int> suffix(n, 0);
        product = 1;
        for (int i = n - 1; i >= 0; i--) {
            product *= nums[i];
            suffix[i] = product;
        }

        vector<int> answer(n, 0);
        for (int i = 0; i < n; i++) {
            if (i > 0 && i < n - 1) {
                answer[i] = prefix[i - 1] * suffix[i + 1];
            } else if (i == 0) {
                answer[i] = suffix[i + 1];
            } else {
                answer[i] = prefix[i - 1];
            }
        }

        return answer;
    }
};
```

</details>

### Code Links

- [Problem Description and Complexity Analysis](../problem_solutions/products-of-array-discluding-self/README.md)
- [Python Solution](../problem_solutions/products-of-array-discluding-self/solution.py)
- [C++ Solution](../problem_solutions/products-of-array-discluding-self/solution.cpp)

</details>

---

<details>
<summary>3. Longest Consecutive Sequence (LeetCode 128 / NeetCode)</summary>

### Problem

Given an unsorted array of integers `nums`, return the length of the longest consecutive elements sequence.

**Constraints:**
- You must write an algorithm that runs in strictly $O(n)$ time.

[NeetCode: Longest Consecutive Sequence](https://neetcode.io/problems/longest-consecutive-sequence/) | [LeetCode 128: Longest Consecutive Sequence](https://leetcode.com/problems/longest-consecutive-sequence/)

---

### Examples and Tracing

#### Example 1:
- **Input:** `nums = [100, 4, 200, 1, 3, 2]`
- **Consecutive sequences present:**
  - `[100]` (length 1)
  - `[200]` (length 1)
  - `[1, 2, 3, 4]` (length 4)
- **Output:** `4`

#### Example 2:
- **Input:** `nums = [0, 3, 7, 2, 5, 8, 4, 6, 0, 1]`
- **Consecutive sequence:** `[0, 1, 2, 3, 4, 5, 6, 7, 8]`
- **Output:** `9`

#### Example 3:
- **Input:** `nums = []`
- **Output:** `0`

---

### Problem Intuition: How to Beat Sorting ($O(n \log n)$)

If we sorted `nums`, we could simply scan adjacent elements. However, sorting takes $O(n \log n)$ time, which violates the $O(n)$ requirement.

To get $O(n)$ time, we need $O(1)$ lookups. We can insert all numbers into a **hash set**:
```python
my_set = set(nums)
```

Now we can check if any number exists in $O(1)$ average time.

#### The Big Question: How Do We Avoid Redundant Work?

Suppose `nums = [1, 2, 3, 4, 5]`.
- If we start counting from `1`, we count up to `5` (length 5).
- If we then start counting from `2`, we count up to `5` (length 4).
- If we do this for every number, a sequence of length $k$ will do $O(k^2)$ checks, degrading total time to $O(n^2)$!

#### The Key Observation: Only Start from Sequence Beginnings

How do you know if a number `num` is the **start** of a sequence?
- Check if `num - 1` is in `my_set`.
- If `num - 1` **is** in the set, then `num` is not the beginning; it is just a middle element of a sequence that started earlier! We can skip it immediately:
  ```python
  if num - 1 in my_set:
      continue
  ```
- If `num - 1` **is not** in the set, then `num` is guaranteed to be the start of a consecutive chain. We then step forward: `num + 1`, `num + 2`, ..., counting until the chain breaks.

Because the inner while loop only runs for the first element of each sequence, each number in `nums` is visited at most twice (once in the outer loop, and at most once in a while loop). This guarantees an overall runtime of $O(n)$!

---

### Starter Code

```python
from typing import List


class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        # Step 1: Insert all numbers into a set for O(1) lookups
        my_set = set(nums)
        answer = 0

        # Step 2: Iterate over each number
        for num in nums:
            # Step 3: Only begin counting if num is the start of a sequence
            # Your code here

            # Step 4: Count consecutive numbers: num + 1, num + 2, ...
            # Your code here
            pass

        return answer
```

<details>
<summary>Hints</summary>

1. If `num - 1 in my_set`, skip `num` using `continue`. Someone smaller already started this chain.
2. Initialize `i = 1`. Run a while loop: `while num + i in my_set: i += 1`.
3. When the loop ends, the length of the chain starting at `num` is `i`. Update `answer = max(answer, i)`.
4. Empty lists will naturally return `0` because the loop does not run.

</details>

<details>
<summary>Solution</summary>

### Python Solution

```python
from typing import List


class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        my_set = set(nums)
        answer = 0
        for num in nums:
            if num - 1 in my_set:
                continue
            i = 1
            while num + i in my_set:
                i += 1
            answer = max(answer, i)
        return answer
```

### C++ Solution

```cpp
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int> &nums) {
        unordered_set<int> my_set(nums.begin(), nums.end());
        int answer = 0;

        for (int num : nums) {
            if (my_set.find(num - 1) != my_set.end()) {
                continue;
            }

            int i = 1;
            while (my_set.find(num + i) != my_set.end()) {
                i++;
            }
            answer = max(answer, i);
        }

        return answer;
    }
};
```

### Complexity

| Step | Time Complexity | Auxiliary Space |
| :--- | :--- | :--- |
| **Set Construction** | $O(n)$ average | $O(n)$ |
| **Outer Loop + Skip Check** | $O(n)$ | $O(1)$ |
| **Inner While Loop Expansion** | $O(n)$ amortized total | $O(1)$ |
| **Total** | **$O(n)$** | **$O(n)$** |

</details>

### Code Links

- [Problem Description and Complexity Analysis](../problem_solutions/longest-consecutive-sequence/README.md)
- [Python Solution](../problem_solutions/longest-consecutive-sequence/solution.py)
- [C++ Solution](../problem_solutions/longest-consecutive-sequence/solution.cpp)

</details>
