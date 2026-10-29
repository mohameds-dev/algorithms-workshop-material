# Week 10, Day 2 (October 29, 2026)

## Today

Today we conduct an exam review session based directly on Dr. Wu's COSC 3320 Midterm 2 (Fall 2025 paper):
1. **Problem 1 (DP on Numbers):** Minimum cost basic arithmetic expression to form integer $n$ in $O(n^2)$ time.
2. **Problem 2 (Linear-Time Array DP):** Maximum length of a contiguous strictly increasing subarray after deleting at most one element in $O(n)$ time.
3. **Problem 3 (Greedy Choice Proof and Disproof):** Interval Hitting Set: disproving Rule A via counterexample and proving Rule B via exchange argument.

You can write and test your code without any local setup using the [Online IDE Guide](../misc_references/online-ide.md) ([Judge0 IDE](https://ide.judge0.com/)).

---

<details>
<summary>1. Problem 1: Minimum Cost Arithmetic Expression (DP)</summary>

### Problem Statement

A basic arithmetic expression is composed of characters from the set $\{1, +, \times\}$ and parentheses. Almost every integer can be represented by more than one basic arithmetic expression.

For example, all of the following basic arithmetic expressions represent the integer 14:
- $1+1+1+1+1+1+1+1+1+1+1+1+1+1$ (cost = 14)
- $((1+1) \times (1+1+1+1+1)) + ((1+1) \times (1+1))$ (cost: 11 ones + 2 multiplications = 13)
- $(1+1) \times (1+1+1+1+1+1+1)$ (cost: 9 ones + 1 multiplication = 10)
- $(1+1) \times (((1+1+1) \times (1+1)) + 1)$ (cost: 8 ones + 2 multiplications = 10)

Describe and analyze an algorithm to compute, given an integer $n$ as input, the **minimum cost** in a basic arithmetic expression whose value is equal to $n$.

The cost of a basic arithmetic expression is the **number of 1s plus the number of multiplications**. Parentheses and addition signs do not count towards the cost.

**Requirement:** The running time of your algorithm should be bounded by $O(n^2)$ or better.

---

### Whiteboard Intuition: How Is an Expression Built?

Think about how any valid arithmetic expression evaluating to an integer $k$ is formed at its outermost operation:

1. **Base Case ($k = 1$):**
   The integer 1 is simply the literal character `'1'`.
   It contains one `1` and zero multiplications:
   $$\text{cost}[1] = 1$$

2. **Formed by Addition ($k = a + b$):**
   The expression is $(\text{expr}_a) + (\text{expr}_b)$, where $a \ge 1$, $b \ge 1$, and $a + b = k$.
   Addition signs cost 0, so the total cost is simply the sum of costs:
   $$\text{cost}[a] + \text{cost}[k - a]$$
   By symmetry ($a + b = b + a$), we only need to test $1 \le a \le \lfloor k / 2 \rfloor$.

3. **Formed by Multiplication ($k = a \times b$):**
   The expression is $(\text{expr}_a) \times (\text{expr}_b)$, where $a > 1$, $b > 1$, and $a \times b = k$.
   Here, the multiplication sign costs 1! Therefore, the cost is:
   $$\text{cost}[a] + \text{cost}[k / a] + 1$$
   We only need to test divisors $a$ such that $k \pmod a == 0$, with $2 \le a \le \lfloor \sqrt{k} \rfloor$.

Since optimal subexpressions make up an optimal overall expression, this problem exhibits **optimal substructure**. We can build the solution bottom-up from $1$ to $n$.

---

### Starter Code (Python)

```python
def min_cost_expression(n: int) -> int:
    # Step 1: Initialize DP table of size n + 1
    cost = [0] * (n + 1)
    cost[1] = 1

    # Step 2: Fill table from 2 up to n
    for i in range(2, n + 1):
        # Check all addition splits: a + (i - a)
        # Check all factor splits: a * (i // a)
        pass

    return cost[n]
```

<details>
<summary>Hints</summary>

1. Start by setting `cost[i]` to the best possible addition split: `min(cost[a] + cost[i - a] for a in range(1, i // 2 + 1))`.
2. Next, check if $i$ has any divisors $a \ge 2$. For every divisor, compare your current best cost against `cost[a] + cost[i // a] + 1`.
3. To keep the divisor loop fast, iterate $a$ from $2$ up to $\lfloor \sqrt{i} \rfloor$. If `i % a == 0`, you have found a pair of factors $(a, i // a)$.
</details>

<details>
<summary>Solution</summary>

### Python Solution

```python
def min_cost_expression(n: int) -> int:
    cost = [0] * (n + 1)
    cost[1] = 1

    for i in range(2, n + 1):
        # 1. Best cost via addition: i = a + (i - a)
        best = min(cost[a] + cost[i - a] for a in range(1, i // 2 + 1))

        # 2. Check multiplication splits: i = a * (i // a)
        for a in range(2, int(i**0.5) + 1):
            if i % a == 0:
                mult_cost = cost[a] + cost[i // a] + 1
                if mult_cost < best:
                    best = mult_cost

        cost[i] = best

    return cost[n]


# Verification with example from the exam
if __name__ == "__main__":
    print(f"n = 14: minimum cost = {min_cost_expression(14)}")  # 10
```

### C++ Solution

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int minCostExpression(int n) {
    vector<int> cost(n + 1, 0);
    cost[1] = 1;

    for (int i = 2; i <= n; i++) {
        int best = i; // worst-case upper bound (1 + 1 + ... + 1)

        // Try addition splits: i = a + (i - a)
        for (int a = 1; a <= i / 2; a++) {
            best = min(best, cost[a] + cost[i - a]);
        }

        // Try multiplication splits: i = a * (i / a)
        for (int a = 2; a * a <= i; a++) {
            if (i % a == 0) {
                best = min(best, cost[a] + cost[i / a] + 1);
            }
        }

        cost[i] = best;
    }

    return cost[n];
}

int main() {
    cout << "n = 14: " << minCostExpression(14) << endl; // 10
    return 0;
}
```

### Complexity Analysis

- **Time Complexity:**
  For each integer $i \in [2, n]$:
  - Checking addition pairs takes $\lfloor i / 2 \rfloor$ steps.
  - Checking factors takes $\lfloor \sqrt{i} \rfloor$ steps.
  Summing over all $i$:
  $$\sum_{i=2}^n \left( \frac{i}{2} + \sqrt{i} \right) \le \frac{1}{2} \sum_{i=2}^n i + \sum_{i=2}^n \sqrt{n} = O(n^2)$$
  This meets the exam's $O(n^2)$ time bound requirement.
- **Space Complexity:**
  $O(n)$ space for the 1D array `cost` of size $n + 1$.

</details>

</details>

---

<details>
<summary>2. Problem 2: Longest Increasing Subarray After Deleting At Most One Element</summary>

### Problem Statement

Find the maximum length of a **contiguous strictly increasing subarray** after deleting at most one element in array $A[0:n]$.

For example, for array `[1, 3, 2, 4, 5]`, after deleting `2`, we get `[1, 3, 4, 5]` with length 4, which is the answer.

**Requirement:** Your algorithm must run with worst case time complexity $O(n)$, where $n$ is the length of the input array $A[0:n]$.

---

### Whiteboard Intuition: Deleting an Element as a Bridge

Consider what happens if we delete element $A[i]$ from the array:
- The subarray to the left of $i$ ends at index $i - 1$.
- The subarray to the right of $i$ begins at index $i + 1$.
- When can these two pieces be joined into one strictly increasing subarray?
  **If and only if $A[i - 1] < A[i + 1]$!**

```text
Index:    0    1    2    3    4
Array:   [1,   3,   2,   4,   5]
                   ^
                delete 2
Can we bridge index 1 (value 3) and index 3 (value 4)?
Yes, because 3 < 4!
Left increasing length ending at index 1:  [1, 3] -> length 2
Right increasing length starting at index 3: [4, 5] -> length 2
Total bridged length: 2 + 2 = 4
```

### Deriving the $O(n)$ Algorithm

Instead of recalculating lengths from scratch (which would take $O(n^2)$), we precompute two arrays in linear time:

1. **`left[i]` (Forward DP):**
   The length of the strictly increasing subarray ending at index $i$.
   - `left[0] = 1`
   - For $i \ge 1$: if $A[i] > A[i - 1]$, `left[i] = left[i - 1] + 1`; else `left[i] = 1`.

2. **`right[i]` (Backward DP):**
   The length of the strictly increasing subarray starting at index $i$.
   - `right[n - 1] = 1`
   - For $i \le n - 2$: if $A[i] < A[i + 1]$, `right[i] = right[i + 1] + 1`; else `right[i] = 1`.

3. **Evaluating Possibilities:**
   - **Case 0 (No deletion):** The longest increasing subarray without deleting anything is $\max_{0 \le i < n} \text{left}[i]$.
   - **Case 1 (Delete an endpoint):**
     - Deleting $A[0]$ leaves a subarray starting at index 1 of length `right[1]`.
     - Deleting $A[n - 1]$ leaves a subarray ending at index $n - 2$ of length `left[n - 2]`.
   - **Case 2 (Delete an interior element $A[i]$):**
     For each $i \in [1, n - 2]$:
     If $A[i - 1] < A[i + 1]$, we can bridge across $A[i]$, achieving length:
     $$\text{left}[i - 1] + \text{right}[i + 1]$$

---

### Starter Code (Python)

```python
from typing import List


def max_increasing_after_one_deletion(nums: List[int]) -> int:
    n = len(nums)
    if n <= 1:
        return n

    # Step 1: Precalculate left array
    left = [1] * n
    # Your code here

    # Step 2: Precalculate right array
    right = [1] * n
    # Your code here

    # Step 3: Check max without deletion and bridging across each interior element
    ans = max(left)
    # Your code here

    return ans
```

<details>
<summary>Hints</summary>

1. Build `left` with a forward loop: if `nums[i] > nums[i - 1]`, set `left[i] = left[i - 1] + 1`.
2. Build `right` with a backward loop: if `nums[i] < nums[i + 1]`, set `right[i] = right[i + 1] + 1`.
3. Loop $i$ from $1$ to $n - 2$. Whenever `nums[i - 1] < nums[i + 1]`, update `ans = max(ans, left[i - 1] + right[i + 1])`.
</details>

<details>
<summary>Solution</summary>

### Python Solution

```python
from typing import List


def max_increasing_after_one_deletion(nums: List[int]) -> int:
    n = len(nums)
    if n <= 1:
        return n

    left = [1] * n
    for i in range(1, n):
        if nums[i] > nums[i - 1]:
            left[i] = left[i - 1] + 1

    right = [1] * n
    for i in range(n - 2, -1, -1):
        if nums[i] < nums[i + 1]:
            right[i] = right[i + 1] + 1

    # Base answer: maximum length without deleting any element
    ans = max(left)

    # Check deleting each interior element nums[i]
    for i in range(1, n - 1):
        if nums[i - 1] < nums[i + 1]:
            ans = max(ans, left[i - 1] + right[i + 1])

    return ans


# Verification with example from the exam
if __name__ == "__main__":
    print(max_increasing_after_one_deletion([1, 3, 2, 4, 5]))  # 4
    print(max_increasing_after_one_deletion([1, 2, 3, 4]))  # 4
    print(max_increasing_after_one_deletion([5, 4, 3, 2, 1]))  # 1
```

### C++ Solution

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int maxIncreasingAfterOneDeletion(const vector<int> &nums) {
    int n = nums.size();
    if (n <= 1) return n;

    vector<int> left(n, 1);
    for (int i = 1; i < n; i++) {
        if (nums[i] > nums[i - 1]) {
            left[i] = left[i - 1] + 1;
        }
    }

    vector<int> right(n, 1);
    for (int i = n - 2; i >= 0; i--) {
        if (nums[i] < nums[i + 1]) {
            right[i] = right[i + 1] + 1;
        }
    }

    int ans = 1;
    for (int x : left) ans = max(ans, x);

    for (int i = 1; i < n - 1; i++) {
        if (nums[i - 1] < nums[i + 1]) {
            ans = max(ans, left[i - 1] + right[i + 1]);
        }
    }

    return ans;
}

int main() {
    cout << maxIncreasingAfterOneDeletion({1, 3, 2, 4, 5}) << endl; // 4
    return 0;
}
```

### Complexity Analysis

- **Time Complexity:** $O(n)$. We perform three linear passes across the array of length $n$: one forward pass for `left`, one backward pass for `right`, and one pass to test interior deletions.
- **Space Complexity:** $O(n)$ auxiliary space to store the `left` and `right` arrays.

</details>

</details>

---

<details>
<summary>3. Problem 3: Interval Hitting Set (Greedy Choice Analysis)</summary>

### Problem Statement

You are given $n$ closed intervals $I$ on the real line (they might overlap). A **hitting set of points** is a set $P \subset \mathbb{R}$ (points on the line) such that every interval contains at least one point of $P$.

Our goal is to **minimize $|P|$** (the total number of points).

Consider two candidate greedy rules:
- **Rule A:** Repeatedly pick the interval of maximum length among those not yet hit; place a point at its left endpoint; remove all intervals hit; repeat.
- **Rule B:** Sort intervals by increasing right endpoint. Sweep left-to-right; when you encounter the first interval not yet hit, place a point at its right endpoint and remove all intervals that contain that point; continue.

**Task:** For each rule, **prove or disprove** its greedy choice property.

---

### Analysis of Rule A: Disproof via Counterexample

To disprove the greedy choice property for a candidate rule, we only need to provide a single concrete instance (counterexample) where following the rule results in a strictly suboptimal hitting set.

#### Counterexample Construction

Consider the following three intervals:
- $I_1 = [0, 10]$ (length $10$)
- $I_2 = [1, 5]$ (length $4$)
- $I_3 = [5, 9]$ (length $4$)

```text
Line coordinate:
0       1               5               9       10
|-----------------------I1----------------------|   length = 10
        |-------I2------|                           length = 4
                        |-------I3------|           length = 4
```

1. **Optimal Hitting Set:**
   Notice that the point $5$ lies inside all three intervals:
   - $5 \in [0, 10]$ ($I_1$)
   - $5 \in [1, 5]$ ($I_2$)
   - $5 \in [5, 9]$ ($I_3$)
   Therefore, a single point $P^* = \{5\}$ hits every interval. The minimum size is:
   $$|P^*| = 1$$

2. **Execution of Rule A:**
   - The interval of maximum length is $I_1 = [0, 10]$ (length 10).
   - Rule A places a point at its **left endpoint**: $p_1 = 0$.
   - Point $0$ hits $I_1$.
   - Does point $0$ hit $I_2$ or $I_3$?
     $0 \notin [1, 5]$ and $0 \notin [5, 9]$. Neither $I_2$ nor $I_3$ is hit!
   - Now the remaining unhit intervals are $\{I_2, I_3\}$, both of length 4.
   - Rule A picks one of them, say $I_2 = [1, 5]$, and places a point at its left endpoint: $p_2 = 1$.
   - Point $1$ hits $I_2$, but $1 \notin [5, 9]$, so $I_3$ remains unhit.
   - Finally, Rule A picks $I_3 = [5, 9]$ and places a point at its left endpoint: $p_3 = 5$.
   - Rule A outputs $P = \{0, 1, 5\}$, using **3 points**.

3. **Conclusion:**
   Because Rule A produces $|P| = 3$ points on an instance where $|P^*| = 1$, Rule A fails to find an optimal solution.
   **Rule A's greedy choice property is DISPROVED.**

---

### Analysis of Rule B: Proof via Exchange Argument

#### Claim
Rule B possesses the **greedy choice property**: there exists a minimum hitting set that includes the right endpoint of the interval with the smallest right endpoint.

#### Proof (Exchange Argument)

1. **Setup:**
   Let the intervals be ordered by increasing right endpoint:
   $$r_1 \le r_2 \le \dots \le r_n$$
   Let $I_1 = [l_1, r_1]$ denote the interval with the earliest right endpoint.
   Rule B selects the point $p = r_1$.

2. **Assume an Arbitrary Optimal Solution:**
   Let $P^*$ be any optimal hitting set.
   Because $P^*$ hits all intervals, it must hit $I_1$.
   Therefore, there exists at least one point $q \in P^*$ such that $q \in [l_1, r_1]$, which means:
   $$l_1 \le q \le r_1$$

3. **Case 1: $q = r_1$**
   If $q = r_1$, then $P^*$ already contains the greedy choice $r_1$. The property holds immediately.

4. **Case 2: $q < r_1$**
   Suppose $q < r_1$. We construct a modified set of points:
   $$P' = (P^* \setminus \{q\}) \cup \{r_1\}$$
   Notice that $|P'| \le |P^*|$. To prove $P'$ is an optimal hitting set, we show that $P'$ hits every interval that $P^*$ hit.
   - Any interval hit by a point in $P^* \setminus \{q\}$ is still hit in $P'$.
   - What about any interval $J = [l_J, r_J]$ that was hit by $q$?
     Since $q \in J$, we know:
     $$l_J \le q \le r_J$$
     Since $q < r_1$, it follows that $l_J \le r_1$.
     Furthermore, because $I_1 = [l_1, r_1]$ has the smallest right endpoint among all intervals, we know $r_1 \le r_J$.
     Combining these two inequalities gives:
     $$l_J \le r_1 \le r_J \implies r_1 \in J$$
     Hence, the greedy point $r_1$ also hits interval $J$!

5. **Conclusion:**
   Replacing $q$ with $r_1$ maintains the hitting property for all intervals while keeping the set size $\le |P^*|$. Therefore, $P'$ is also an optimal hitting set and contains the greedy choice $r_1$.
   By mathematical induction on the remaining intervals, Rule B always constructs a minimum hitting set.
   **Rule B's greedy choice property is PROVEN.**

---

### Python Implementation of Rule B

```python
from typing import List, Tuple


def min_hitting_set(intervals: List[Tuple[float, float]]) -> List[float]:
    if not intervals:
        return []

    # Sort intervals by increasing right endpoint
    sorted_intervals = sorted(intervals, key=lambda x: x[1])

    hitting_points = []
    current_point = float("-inf")

    for left, right in sorted_intervals:
        # If the interval is not yet hit by current_point
        if left > current_point:
            current_point = right
            hitting_points.append(current_point)

    return hitting_points


# Verification
if __name__ == "__main__":
    # Test on the Rule A counterexample: [0, 10], [1, 5], [5, 9]
    test_intervals = [(0, 10), (1, 5), (5, 9)]
    pts = min_hitting_set(test_intervals)
    print(f"Rule B points: {pts}")  # [5] -> exactly size 1!

    # Example from the PDF: [1, 5], [3, 8], [7, 10]
    exam_intervals = [(1, 5), (3, 8), (7, 10)]
    pts_exam = min_hitting_set(exam_intervals)
    print(f"Exam example points: {pts_exam}")  # [5, 10] -> size 2!
```

<details>
<summary>References</summary>

- LeetCode 452: Minimum Number of Arrows to Burst Balloons (identical mathematical formulation of Interval Hitting Set).
- COSC 3320 Midterm 2 Fall 2025 (`references/Wu-Fall2026/2025_midterm2.pdf`).
</details>

</details>
