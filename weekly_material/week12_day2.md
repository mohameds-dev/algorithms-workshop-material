# Week 12, Day 2 (November 12, 2026)

## Today

Today we dive deep into dependency resolution, directed acyclic graphs (DAGs), and topological sorting (rolled over from Day 1 to ensure full, dedicated coverage):
1. **Directed Acyclic Graphs (DAGs) and Topological Sort:** Linear ordering of tasks with prerequisite constraints.
2. **Kahn's Algorithm and the Exchange Argument:** Why greedily selecting any in-degree 0 vertex preserves validity, inductive graph shrinkage, and cycle detection.
3. **Problem: Course Schedule** ([CSES 1679](https://cses.fi/problemset/task/1679) / [LeetCode 210](https://leetcode.com/problems/course-schedule-ii/description/)).
4. **Curated Practice Problems:** Recommended follow-up problems on trees and topological sorting ([Practice Handout](../misc_references/trees-and-dags-practice.md)).

You can write and test your code without local setup using the [Online IDE Guide](../misc_references/online-ide.md) ([Judge0 IDE](https://ide.judge0.com/)).

---

## Session Resources

- **Course Schedule:** [CSES 1679](https://cses.fi/problemset/task/1679)
- **Course Schedule II:** [LeetCode 210](https://leetcode.com/problems/course-schedule-ii/description/)
- **Tree Diameter (Day 1 Review):** [CSES 1131](https://cses.fi/problemset/task/1131) ([Week 12, Day 1](./week12_day1.md))
- **Additional Practice Handout:** [Trees and DAGs Practice](../misc_references/trees-and-dags-practice.md)
- **Graph Visualizer:** [CS Academy Graph Editor](https://csacademy.com/app/graph_editor/)
- **Algorithm Animations:** [VisuAlgo Graph Traversal](https://visualgo.net/en/dfsbfs)
- **Online IDE:** [Online IDE Guide](../misc_references/online-ide.md) ([Judge0 IDE](https://ide.judge0.com/))

---

<details>
<summary>1. Directed Acyclic Graphs (DAGs) and Topological Sort</summary>

### What is a Topological Sort?

Given a directed graph $G = (V, E)$, a **topological sort** is a linear ordering of vertices such that for every directed edge $u \to v$, vertex $u$ comes before vertex $v$ in the ordering.

Think of vertices as college courses and edges $u \to v$ as prerequisites ("you must take course $u$ before course $v$"). A topological sort is any valid sequence of taking all courses one by one without violating prerequisites.

```mermaid
flowchart LR
    CS1["CS 101"] --> CS2["CS 201"]
    CS1 --> Math1["Math 101"]
    CS2 --> Algo["CS 301: Algorithms"]
    Math1 --> Algo
```

Valid orders:
- `[CS 101, Math 101, CS 201, CS 301]`
- `[CS 101, CS 201, Math 101, CS 301]`

### The Core Theorem: DAG Equivalence

A directed graph has a topological sort **if and only if** it contains no directed cycles. Such a graph is called a **Directed Acyclic Graph (DAG)**.

If a graph contains a cycle (e.g. $A \to B \to C \to A$), then $A$ must come before $B$, $B$ before $C$, and $C$ before $A$, which is impossible in any linear sequence.

---

### Kahn's Algorithm (BFS via In-Degrees)

Kahn's algorithm greedily peels away nodes that are ready to be scheduled:

1. **Compute In-Degrees:** For each node $v$, count how many incoming edges enter $v$.
2. **Collect Sources:** Any node with `in_degree == 0` has no remaining prerequisites. Push all such nodes into a queue.
3. **Peel Vertices:** While the queue is not empty:
   - Pop a node $u$ from the queue and append it to our topological order.
   - For each neighbor $v$ of $u$ (edges $u \to v$):
     - Decrement `in_degree[v]` by 1.
     - If `in_degree[v] == 0`, all prerequisites for $v$ have been satisfied. Push $v$ into the queue.
4. **Detect Cycles:** If the output order contains all $V$ nodes, return the order. If fewer than $V$ nodes were processed, a cycle prevented the remaining nodes from ever reaching `in_degree == 0`.

</details>

---

<details>
<summary>2. Kahn's Algorithm Proof: The Exchange Argument and Cycle Detection</summary>

### Where Does the Exchange Argument Plug In?

Kahn's algorithm is fundamentally a **greedy algorithm**: whenever several vertices have `in_degree == 0`, it arbitrarily chooses any of them to place next.

A classic exam question is:
> *"Does making this greedy choice right now risk getting us stuck later? Could choosing vertex $u$ first make it impossible to finish a valid topological sort, even if one existed?"*

We prove that Kahn's greedy choice is safe using an **exchange argument**.

---

### 1. Existence: Every Finite DAG Has an In-Degree 0 Vertex

- **Claim:** Every finite DAG has at least one vertex with in-degree 0.
- **Proof:** Suppose for contradiction that every vertex in a DAG of $n$ vertices has in-degree $\ge 1$.
  - Start at any vertex $v_1$. Because its in-degree is at least 1, choose an incoming edge $(v_2, v_1)$.
  - Move to $v_2$. It also has an incoming edge $(v_3, v_2)$.
  - Continue walking backward along incoming edges: $v_1 \leftarrow v_2 \leftarrow v_3 \leftarrow \dots$
  - Because the graph has only $n$ vertices, by the Pigeonhole Principle, we must revisit a previously visited vertex within $n$ steps.
  - Reversing that cycle of backward steps reveals a forward directed cycle:
    $$v_k \to v_{k-1} \to \dots \to v_j \to v_k$$
  - This contradicts the assumption that the graph is acyclic.
  - Therefore, at least one vertex must have in-degree 0.

---

### 2. The Exchange Argument: Greedily Picking In-Degree 0 Is Always Safe

- **Claim:** If a graph $G$ has a valid topological sort, and vertex $u$ has in-degree 0 in $G$, then there exists a valid topological sort of $G$ that starts with $u$.
- **Proof via Exchange Argument:**
  - Let $O = [v_1, v_2, \dots, v_k, \dots, v_n]$ be any valid topological sort of $G$.
  - If $v_1 = u$, then $O$ already starts with $u$, and we are done.
  - Suppose $u$ appears later at index $k > 1$:
    $$O = [v_1, v_2, \dots, v_{k-1}, u, v_{k+1}, \dots, v_n]$$
  - Construct an exchanged order $O'$ by moving $u$ to the very front:
    $$O' = [u, v_1, v_2, \dots, v_{k-1}, v_{k+1}, \dots, v_n]$$
  - Let us check if $O'$ violates any directed edge:
    1. **Edges between other vertices:** The relative order among all vertices other than $u$ has not changed. Any edge between $v_i$ and $v_j$ remains satisfied.
    2. **Incoming edges to $u$:** An edge could only be violated if it points into $u$ from some vertex that was placed before $u$ in $O$ (i.e. an edge $v_i \to u$ for $i < k$). But $u$ has **in-degree 0 in $G$**, which means **there are no edges pointing into $u$ at all**.
    3. **Outgoing edges from $u$:** Since $u$ is now at the very front of $O'$, all its outgoing edges point forward to vertices that appear after $u$.
  - Therefore, $O'$ is a completely valid topological sort that begins with $u$.
  - This proves that greedily choosing any in-degree 0 vertex never destroys our ability to reach a valid topological ordering.

---

### 3. Inductive Step: Graph Shrinkage and DAG Invariant

We formalize the inductive argument on the number of vertices $n$:

- **Base Case ($n = 1$):** A single vertex with no self-loops trivially has in-degree 0. It is placed into the order, satisfying all dependencies.
- **Inductive Hypothesis:** Assume Kahn's algorithm correctly outputs a valid topological sort for any DAG containing fewer than $n$ vertices.
- **Inductive Step (for $n$ vertices):**
  1. By Step 1, graph $G$ has at least one vertex $u$ with `in_degree == 0`.
  2. By the Exchange Argument (Step 2), placing $u$ first is guaranteed to be safe and extendable to a valid topological sort.
  3. When Kahn's algorithm processes $u$, it removes $u$ and all its outgoing edges $u \to v$ from the graph:
     - For each neighbor $v$, removing the directed edge $u \to v$ decrements `in_degree[v]` by 1.
     - This simulates that prerequisite $u$ has been completed, potentially freeing up new vertices whose in-degrees now reach 0.
  4. Let the resulting remaining subgraph be $G' = G \setminus \{u\}$.
  5. **Why must $G'$ remain a valid DAG?**
     - Deleting vertices and edges can never create new cycles. If $G'$ contained a cycle, that cycle must have already existed in $G$, which contradicts our premise that $G$ is acyclic.
     - Therefore, $G'$ is guaranteed to remain a valid DAG on $n - 1$ vertices.
  6. By the inductive hypothesis, Kahn's algorithm correctly produces a valid topological sort for $G'$, say $[v_2, v_3, \dots, v_n]$.
  7. Prepending $u$ produces $[u, v_2, v_3, \dots, v_n]$, which is a valid topological sort for the entire $n$-vertex graph $G$.

---

### 4. Cycle Detection

If the queue runs empty while the number of scheduled vertices is strictly less than $n$:
- Every remaining unscheduled vertex must have `in_degree > 0`.
- By Step 1, any finite graph where every vertex has in-degree $\ge 1$ contains a cycle.
- Therefore, the remaining vertices form one or more cycles, and no valid topological sort can exist.

</details>

---

<details>
<summary>3. Problem: Course Schedule (CSES 1679 / LeetCode 210)</summary>

### Problem Statements

#### CSES 1679: Course Schedule
You are given $n$ courses and $m$ requirements of the form "course $a$ has to be completed before course $b$". Find an order in which you can take the courses so that all requirements are satisfied. If there are multiple solutions, print any of them. If it is impossible, print `IMPOSSIBLE`.
- Input: $1 \le n \le 10^5$, $1 \le m \le 2 \cdot 10^5$. Edges $a \to b$ are 1-indexed.
- [CSES 1679: Course Schedule](https://cses.fi/problemset/task/1679)

#### LeetCode 210: Course Schedule II
There are a total of `numCourses` courses you have to take, labeled from $0$ to `numCourses - 1`. You are given an array `prerequisites` where `prerequisites[i] = [a, b]` indicates you must take course $b$ first if you want to take course $a$ ($b \to a$). Return any valid ordering, or `[]` if impossible.
- [LeetCode 210: Course Schedule II](https://leetcode.com/problems/course-schedule-ii/description/)

### Starter Code (CSES 1679)

```python
from collections import deque
import sys


def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    n = int(input_data[0])
    m = int(input_data[1])

    # Step 1: Build adjacency list and compute in-degrees (1-indexed)

    # Step 2: Push all nodes with in_degree == 0 into a queue

    # Step 3: Process queue, append to top_sorted, decrement neighbor in-degrees

    # Step 4: If len(top_sorted) < n, print IMPOSSIBLE; otherwise print the order
    pass


if __name__ == "__main__":
    main()
```

### Hints

<details>
<summary>Hints</summary>

1. Be careful with edge directions! In LeetCode 210, `[a, b]` means $b$ must be taken before $a$, so the edge is $b \to a$. In CSES 1679, $a$ must be taken before $b$, so the edge is $a \to b$.
2. Maintain an array `in_degree` of size $n$, initialized to 0.
3. Every time you add directed edge $u \to v$, increment `in_degree[v] += 1`.
4. Initialize your queue with all vertices whose `in_degree == 0`.
5. When popping $u$, loop through each neighbor $v$ in `adj[u]`, decrement `in_degree[v] -= 1`, and if it reaches 0, push $v$ into the queue.
6. If the length of the result equals $n$, return it. Otherwise, return `[]` (or print `IMPOSSIBLE`).

</details>

### Solution Idea

<details>
<summary>Solution Idea</summary>

1. Build an adjacency list `adj` and an `in_degree` array.
2. Push all nodes with `in_degree[i] == 0` into a `collections.deque`.
3. Initialize an empty list `order`.
4. While the queue has elements:
   - Pop `u = q.popleft()`.
   - Append `u` to `order`.
   - For each neighbor $v$ in `adj[u]`:
     - `in_degree[v] -= 1`
     - If `in_degree[v] == 0`:
       - `q.append(v)`
5. If `len(order) == numCourses`, return `order`. Otherwise, return `[]`.

</details>

### Visual Examples and Test Cases

<details>
<summary>Examples, Diagrams, and Test Inputs</summary>

You can paste the edge list directly into the [CS Academy Graph Editor](https://csacademy.com/app/graph_editor/) (set graph type to directed) to visualize course dependencies.

#### Example 1: Valid DAG with Multiple Branches (CSES Sample)

```mermaid
flowchart LR
    3((3)) --> 1((1))
    1 --> 2((2))
    4((4)) --> 5((5))
```

- **Input:**
  ```text
  5 3
  1 2
  3 1
  4 5
  ```
- **Expected Output:**
  ```text
  3 4 1 5 2
  ```
- **Explanation:** Courses 3 and 4 have in-degree 0; taking 3 unlocks 1, taking 1 unlocks 2, and taking 4 unlocks 5 (any valid topological order such as `4 3 1 5 2` is also accepted).

---

#### Example 2: Directed Cycle (Impossible)

```mermaid
flowchart LR
    1((1)) --> 2((2))
    2 --> 1
```

- **Input:**
  ```text
  2 2
  1 2
  2 1
  ```
- **Expected Output:**
  ```text
  IMPOSSIBLE
  ```
- **Explanation:** Courses 1 and 2 depend on each other in a cycle, so neither course can ever reach in-degree 0.

---

#### Example 3: Diamond DAG

```mermaid
flowchart LR
    1((1)) --> 2((2))
    1 --> 3((3))
    2 --> 4((4))
    3 --> 4
```

- **Input:**
  ```text
  4 4
  1 2
  1 3
  2 4
  3 4
  ```
- **Expected Output:**
  ```text
  1 2 3 4
  ```
- **Explanation:** Course 1 must be taken first, courses 2 and 3 can follow in either order, and course 4 must be taken last once both 2 and 3 are finished.

</details>

### Code Links

- [Problem Explanation and Complexity Analysis](../problem_solutions/course-schedule/README.md)
- [Python Solution](../problem_solutions/course-schedule/solution.py)
- [C++ Solution](../problem_solutions/course-schedule/solution.cpp)

</details>


