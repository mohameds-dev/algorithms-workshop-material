# Additional Practice: Trees and Directed Acyclic Graphs (DAGs)

This practice handout extends the core concepts covered in [Week 12, Day 1](../weekly_material/week12_day1.md) (Tree Diameter) and [Week 12, Day 2](../weekly_material/week12_day2.md) (Topological Sort and Kahn's Algorithm).

---

## Part A: Tree Algorithms and Distances

### 1. Tree Distances I (CSES 1132)

- **Source:** [CSES 1132: Tree Distances I](https://cses.fi/problemset/task/1132)
- **Problem Statement:** You are given a tree of $n$ nodes. For each node $u \in \{1, \dots, n\}$, determine the maximum distance to any other node in the tree.
- **Key Insight (Diameter Endpoint Property):**
  - In any unweighted tree, the farthest node from any arbitrary vertex $u$ is guaranteed to be one of the two diameter endpoints, $x$ or $y$.
  - Therefore, you do not need to run an $O(n)$ search for every single vertex (which would take $O(n^2)$ time).
- **Algorithm ($O(n)$ time):**
  1. Find one diameter endpoint $x$ by running BFS from node 1.
  2. Find the other diameter endpoint $y$ by running BFS from $x$, recording array $dist_x$ where $dist_x[u] = d(x, u)$.
  3. Run a third BFS from $y$, recording array $dist_y$ where $dist_y[u] = d(y, u)$.
  4. For each node $u \in \{1, \dots, n\}$, output $\max(dist_x[u], dist_y[u])$.

---

### 2. Diameter of Binary Tree (LeetCode 543)

- **Source:** [LeetCode 543: Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/)
- **Problem Statement:** Given the root of a binary tree, return the length of the diameter (the number of edges along the longest path between any two nodes).
- **Key Insight:**
  - In a rooted binary tree, the longest path that has node $u$ as its highest point has length equal to $(left\_height + right\_height)$.
  - A single post-order traversal (`DFS`) calculates the height of each subtree while maintaining a global `max_diameter`:
    ```python
    def height(node):
        if not node:
            return 0
        lh = height(node.left)
        rh = height(node.right)
        diameter = max(diameter, lh + rh)
        return 1 + max(lh, rh)
```

---

### 3. Minimum Height Trees (LeetCode 310)

- **Source:** [LeetCode 310: Minimum Height Trees](https://leetcode.com/problems/minimum-height-trees/)
- **Problem Statement:** Given an undirected tree of $n$ nodes, find all possible root nodes that minimize tree height (the tree centroids).
- **Key Insight (Leaf-Peeling BFS):**
  - Any tree has at most two centroids (the middle node or two middle nodes of any diameter path).
  - Just like Kahn's algorithm peels vertices with in-degree 0, we can peel leaves (nodes with `degree <= 1`) layer by layer.
  - When only 1 or 2 nodes remain in the graph, those remaining nodes are the centroids.

---

## Part B: Topological Sort and DAG Dynamic Programming

### 4. Course Schedule (LeetCode 207)

- **Source:** [LeetCode 207: Course Schedule](https://leetcode.com/problems/course-schedule/)
- **Problem Statement:** Given $n$ courses and a list of prerequisites, determine if it is possible to finish all courses (return `true` if yes, `false` if circular dependencies exist).
- **Key Insight:**
  - This is the pure decision problem of topological sorting: a directed graph has a valid ordering if and only if it is a DAG.
  - Run Kahn's algorithm: if `len(top_sorted) == n`, return `true`; otherwise return `false`.

---

### 5. Game Routes (CSES 1681)

- **Source:** [CSES 1681: Game Routes](https://cses.fi/problemset/task/1681)
- **Problem Statement:** A game has $n$ levels and $m$ teleporters forming a DAG. Count the number of distinct routes from level 1 to level $n$, modulo $10^9 + 7$.
- **Key Insight (Forward DP on Topological Order):**
  - Define `dp[u]` as the number of paths from node 1 to node $u$.
  - Initialize `dp[1] = 1`, all other `dp[i] = 0`.
  - Process nodes in topological order using Kahn's algorithm. When popping node $u$:
    - For each directed edge $u \to v$:
      $$dp[v] = (dp[v] + dp[u]) \pmod{10^9 + 7}$$
  - Because vertices are processed in topological order, by the time we process node $v$, all incoming paths to $v$ have already been fully aggregated.

---

### 6. Longest Flight Route (CSES 1680)

- **Source:** [CSES 1680: Longest Flight Route](https://cses.fi/problemset/task/1680)
- **Problem Statement:** Find the longest directed path from city 1 to city $n$ in a DAG, or output `IMPOSSIBLE` if city $n$ is not reachable from city 1.
- **Key Insight:**
  - Finding the longest path in a general graph is NP-hard, but on a DAG it runs in $O(V + E)$ time using topological DP.
  - Maintain `dist[u]` (initialized to $-\infty$ except `dist[1] = 0`) and `parent[u]` for reconstructing the path.
  - Process nodes in topological order. For each edge $u \to v$, if `dist[u] != -inf` and `dist[u] + 1 > dist[v]`:
    - `dist[v] = dist[u] + 1`
    - `parent[v] = u`
  - After processing all nodes, if `dist[n] < 0`, print `IMPOSSIBLE`; otherwise backtrack from $n$ using `parent` to print the flight route.

---

### 7. Alien Dictionary (LeetCode 269 / LintCode 892)

- **Source:** [LintCode 892: Alien Dictionary](https://www.lintcode.com/problem/892/) (LeetCode 269)
- **Problem Statement:** Given a list of words sorted lexicographically in an alien alphabet, derive the alphabetical ordering of the letters.
- **Key Insight (Two-Phase Pipeline):**
  1. **Phase 1: Build the Directed Graph:**
     - Compare each pair of adjacent words `words[i]` and `words[i+1]`.
     - Find the first index where their characters differ: `c1 = words[i][k]` and `c2 = words[i+1][k]`.
     - This establishes the dependency edge $c_1 \to c_2$ ($c_1$ must appear before $c_2$). Increment `in_degree[c2] += 1`.
     - Edge case: If `words[i+1]` is a proper prefix of `words[i]` (e.g. `["abc", "ab"]`), no valid alphabet can exist; return `""`.
  2. **Phase 2: Topological Sort:**
     - Run Kahn's algorithm across all unique characters.
     - If the result contains all unique characters, join and return the string; otherwise, return `""` (cycle detected).
