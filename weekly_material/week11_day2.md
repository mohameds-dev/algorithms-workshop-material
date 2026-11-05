# Week 11, Day 2 (November 5, 2026)

## Today

Today we continue our journey into **Graph Theory**, moving from static representations to dynamic graph traversal algorithms:
1. **Core Graph Traversal:** Depth-First Search (DFS) and Breadth-First Search (BFS) on standard Adjacency Lists. We explore pseudocode, Python, and C++ implementations (using clean class member functions).
2. **Implicit Grid Graphs:** Modeling 2D matrices as graphs where cells are vertices and adjacent cardinal steps (up, down, left, right) are edges.
3. **Connected Components on Grids:** [Number of Islands](https://leetcode.com/problems/number-of-islands/) (LeetCode 200) via DFS.
4. **Measuring Component Sizes:** [Max Area of Island](https://leetcode.com/problems/max-area-of-island/) (LeetCode 695) via return-value DFS accumulation, highlighting its direct structural similarity to Number of Islands.
5. **Leveling Up to Multi-Source BFS:** [Rotting Oranges](https://leetcode.com/problems/rotting-oranges/) (LeetCode 994) to model simultaneous, layer-by-layer spread across time.

---

## Session Resources

- **Number of Islands:** [LeetCode 200](https://leetcode.com/problems/number-of-islands/)
- **Max Area of Island:** [LeetCode 695](https://leetcode.com/problems/max-area-of-island/)
- **Rotting Oranges:** [LeetCode 994](https://leetcode.com/problems/rotting-oranges/)
- **Graph Visualizer:** [CS Academy Graph Editor](https://csacademy.com/app/graph_editor/)
- **Algorithm Animations:** [VisuAlgo Graph Traversal (DFS/BFS)](https://visualgo.net/en/dfsbfs)
- **Online IDE:** [Online IDE Guide](../misc_references/online-ide.md) ([Judge0 IDE](https://ide.judge0.com/))

---

<details>
<summary>1. Graph Traversal on Adjacency Lists: DFS vs BFS</summary>

Once a graph is represented as an adjacency list, we need systematic ways to explore its vertices and edges without getting trapped in cycles. The two foundational traversal strategies are **Depth-First Search (DFS)** and **Breadth-First Search (BFS)**.

### Depth-First Search (DFS)

- **Mental Model:** A maze explorer who follows a single hallway as deep as possible until hitting a dead end, then backtracks to explore unexplored forks.
- **Underlying Mechanism:** Last-In, First-Out (`LIFO`) order, powered by the program's recursive call stack (or an explicit stack).
- **Primary Use Cases:** Cycle detection, topological sorting, finding connected components, and path existence.

#### Pseudocode

```text
function DFS(u, adj, visited):
    mark u as visited
    process vertex u

    for each neighbor v in adj[u]:
        if v is not visited:
            DFS(v, adj, visited)
```

#### Python Implementation

```python
def dfs(start_node: int, adj: dict[int, list[int]]) -> list[int]:
    visited = set()
    traversal_order = []

    def dfs_helper(u: int):
        visited.add(u)
        traversal_order.append(u)
        for v in adj.get(u, []):
            if v not in visited:
                dfs_helper(v)

    dfs_helper(start_node)
    return traversal_order
```

#### C++ Implementation (C++20 Class Functions)

```cpp
#include <iostream>
#include <vector>

using namespace std;

class GraphTraversal {
private:
    void dfsHelper(int u, const vector<vector<int>>& adj, vector<bool>& visited, vector<int>& order) {
        visited[u] = true;
        order.push_back(u);

        for (int v : adj[u]) {
            if (!visited[v]) {
                dfsHelper(v, adj, visited, order);
            }
        }
    }

public:
    vector<int> dfs(int startNode, const vector<vector<int>>& adj) {
        vector<bool> visited(adj.size(), false);
        vector<int> order;
        dfsHelper(startNode, adj, visited, order);
        return order;
    }
};
```

---

### Breadth-First Search (BFS)

- **Mental Model:** A pebble dropped into still water, creating concentric ripples that expand outwards layer by layer. Every node at distance 1 is visited before any node at distance 2.
- **Underlying Mechanism:** First-In, First-Out (`FIFO`) order, powered by a queue.
- **Primary Use Cases:** Shortest path in unweighted graphs, level-order traversal, and multi-source flood fills.

#### Pseudocode

```text
function BFS(start, adj):
    initialize empty queue Q
    initialize visited set

    mark start as visited
    push start into Q

    while Q is not empty:
        pop u from front of Q
        process vertex u

        for each neighbor v in adj[u]:
            if v is not visited:
                mark v as visited
                push v into Q
```

#### Python Implementation

```python
from collections import deque


def bfs(start_node: int, adj: dict[int, list[int]]) -> list[int]:
    visited = {start_node}
    traversal_order = []
    q = deque([start_node])

    while q:
        u = q.popleft()
        traversal_order.append(u)

        for v in adj.get(u, []):
            if v not in visited:
                visited.add(v)
                q.append(v)

    return traversal_order
```

#### C++ Implementation (C++20 Class Functions)

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class GraphTraversal {
public:
    vector<int> bfs(int startNode, const vector<vector<int>>& adj) {
        vector<bool> visited(adj.size(), false);
        vector<int> order;
        queue<int> q;

        visited[startNode] = true;
        q.push(startNode);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);

            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        return order;
    }
};
```

---

### Traversal Comparison

| Property | Depth-First Search (DFS) | Breadth-First Search (BFS) |
| :--- | :--- | :--- |
| **Data Structure** | Call stack / recursion (`LIFO`) | Queue (`FIFO`) |
| **Search Order** | Plunges deep down one path first | Expands evenly in concentric layers |
| **Shortest Path (Unweighted)** | No guarantee | Guaranteed minimal edges |
| **Time Complexity** | $O(V + E)$ | $O(V + E)$ |
| **Space Complexity** | $O(V)$ (recursion depth) | $O(V)$ (queue width) |

</details>

---

<details>
<summary>2. Implicit Grid Graphs</summary>

Many graph problems in interviews and competitions do not hand you an explicit `adj` list. Instead, they give you a 2D matrix (like an island map or a chess board).

You can model any 2D grid as a graph by treating:
1. **Each cell `(i, j)`** as a vertex.
2. **Cardinal transitions** (up, down, left, right) as edges connecting adjacent cells:
   ```python
   directions = ((-1, 0), (1, 0), (0, -1), (0, 1))
   for di, dj in directions:
       ni, nj = i + di, j + dj
   ```
3. **Boundary checking:** A neighbor `(ni, nj)` is valid only if $0 \le ni < \text{rows}$ and $0 \le nj < \text{cols}$.
4. **Visited Tracking:** Prevent infinite recursion or duplicate visits either with a hash set of coordinate pairs `visited = set()`, or a 2D boolean array `visited[rows][cols]`.

</details>

---

<details>
<summary>3. Problem 1: Number of Islands (LeetCode 200)</summary>

### Problem Statement

Given an `m x n` 2D binary grid `grid` representing a map of `'1'`s (land) and `'0'`s (water), return the number of islands. An island is surrounded by water and formed by connecting adjacent lands horizontally or vertically.

[LeetCode 200: Number of Islands](https://leetcode.com/problems/number-of-islands/)

### Analogy: Counting Ink Blotches

Imagine looking at a grid sheet of paper with accidental ink drops. Whenever neighboring squares soak up ink together, they form a single continuous stain (an island).

To count how many stains there are:
1. Scan the sheet square by square (row by row, column by column).
2. The moment your eyes hit an uncolored ink mark, say: *"Found one new island!"* and increment your counter.
3. Immediately pick up a highlighter (launch DFS) and color every connected square of that entire stain until no connected ink remains uncolored (mark visited).
4. Keep scanning. Any previously highlighted square is ignored because you already counted its parent stain.

### Starter Code

```python
class Solution:
    def numIslands(self, grid: list[list[str]]) -> int:
        # Your code here
        pass
```

### Hints

<details>
<summary>Hints</summary>

1. Treat the 2D grid as an undirected graph where each `'1'` is a vertex connected to its 4 cardinal land neighbors.
2. The problem asks for the number of connected components in this graph.
3. Iterate over every cell `(i, j)`. If `grid[i][j] == "1"` and has not been visited, you have discovered a new connected component.
4. Launch DFS from `(i, j)` to explore and mark all reachable land cells as visited before continuing the scan.

</details>

### Solution Idea

<details>
<summary>Solution Idea</summary>

We loop through all cells in the grid. When we find an unvisited cell with value `'1'`:
1. Increment `islands_counter` by 1.
2. Call `dfs(i, j)`.
3. Inside `dfs`, mark `(i, j)` as visited, then inspect all 4 directions `(-1, 0)`, `(1, 0)`, `(0, -1)`, and `(0, 1)`. If a neighbor is in-bounds, contains land `'1'`, and has not been visited, recurse into it.

This completely consumes that component, ensuring each island is counted exactly once in $O(m \cdot n)$ time.

</details>

### Code Links

- [Problem Explanation and Complexity Analysis](../problem_solutions/number-of-islands/README.md)
- [Python Solution](../problem_solutions/number-of-islands/solution.py)
- [C++ Solution (Class Functions)](../problem_solutions/number-of-islands/solution.cpp)

</details>

---

<details>
<summary>4. Problem 2: Max Area of Island (LeetCode 695)</summary>

### Problem Statement

Given an `m x n` binary matrix `grid`, return the maximum area of an island. If there is no island, return `0`.

[LeetCode 695: Max Area of Island](https://leetcode.com/problems/max-area-of-island/)

### Analogy: Measuring Land Parcels

In Number of Islands, your job was simply to count how many distinct farms existed. 

Now, each land square is a 1-acre plot of farmland, and you want to buy the single largest continuous farm available. 

When you discover an unvisited plot of land, you do not just check it off and walk away: you walk across every connecting acre, counting them all up. You compare the total acreage of this farm against your running record:
```python
max_area = max(max_area, area)
```

### Note the Structural Similarity to Problem 1

Notice how almost every line of code is identical to [Number of Islands](#3-problem-1-number-of-islands-leetcode-200):
- **Identical Navigation:** The same 4-directional offsets, the same `in_grid` boundary check, and the same `visited` tracker.
- **Identical Outer Loop:** Both scan every cell `(i, j)` in `grid`.
- **The Only Difference:**
  - In Number of Islands, `dfs(i, j)` had no return value (`void`). It simply marked cells visited so the outer loop could count calls (`islands_counter += 1`).
  - In Max Area of Island, `dfs(i, j)` **accumulates and returns an integer area**:
    ```python
    return 1 + sum(dfs(ni, nj) for ni, nj in nbrs if valid)
    ```
    The current cell contributes `1`, plus the area returned by each valid neighbor branch. The outer loop tracks `max_area = max(max_area, area)`.

### Starter Code

```python
class Solution:
    def maxAreaOfIsland(self, grid: list[list[int]]) -> int:
        # Your code here
        pass
```

### Hints

<details>
<summary>Hints</summary>

1. This uses the exact same DFS connected component engine as Number of Islands.
2. Instead of returning nothing from DFS, what should each call return?
3. A cell contributes 1 (itself) plus whatever area is reachable through its unvisited land neighbors.
4. Mark the cell visited before recursing into neighbors to avoid infinite cycles.

</details>

### Solution Idea

<details>
<summary>Solution Idea</summary>

Iterate through every cell `(i, j)` in `grid`. If `grid[i][j] == 1` and `(i, j)` is not yet visited:
1. Call `area = dfs(i, j)`.
2. Inside `dfs(i, j)`:
   - Add `(i, j)` to `visited`.
   - Calculate candidate neighbors `(i + di, j + dj)`.
   - Return `1 + sum(dfs(ni, nj) for valid unvisited land neighbors)`.
3. Update `max_area = max(max_area, area)`.
4. Return `max_area` after scanning all cells.

</details>

### Code Links

- [Problem Explanation and Complexity Analysis](../problem_solutions/max-area-of-island/README.md)
- [Python Solution](../problem_solutions/max-area-of-island/solution.py)
- [C++ Solution (Class Functions)](../problem_solutions/max-area-of-island/solution.cpp)

</details>

---

<details>
<summary>5. Problem 3: Rotting Oranges (LeetCode 994)</summary>

### Problem Statement

You are given an `m x n` grid where:
- `0` represents an empty cell,
- `1` represents a fresh orange, and
- `2` represents a rotten orange.

Every minute, any fresh orange 4-directionally adjacent to a rotten orange turns rotten. Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return `-1`.

[LeetCode 994: Rotting Oranges](https://leetcode.com/problems/rotting-oranges/)

### Why DFS Fails Here: The Need for BFS

In the island problems, we only needed to know which cells were connected together. DFS worked because traversal order did not matter; any order visits all nodes in the component.

In Rotting Oranges, **time is uniform across all outbreak centers**. 
- If you used DFS, it would chase one rot path deep across the grid, recording artificially inflated minutes (minute 1, minute 2, minute 3...) along a single line, while ignoring that other rotten oranges across the grid were rotting their neighbors at minute 1 as well!
- We need a traversal that expands in concentric circles simultaneously: **Multi-Source Breadth-First Search (BFS)**.

### Analogy: Simultaneous Multi-Point Wildfire Outbreak

Imagine a dry forest where lightning strikes five different trees simultaneously at $t = 0$.

At minute 1, all five burning trees ignite all of their immediate neighbors at the exact same time. At minute 2, that entire outer perimeter expands outward together in a wave. 

By pushing all initially rotten oranges into our queue at minute 0, BFS simulates physical time step by step. When the queue runs empty, the time recorded at the very last infected tree is our answer. If an unburned tree sits isolated across a clearing, it never catches fire, so we return `-1`.

### Starter Code

```python
class Solution:
    def orangesRotting(self, grid: list[list[int]]) -> int:
        # Your code here
        pass
```

### Hints

<details>
<summary>Hints</summary>

1. Because the rot spreads to all adjacent fresh oranges simultaneously at each minute step, this is a shortest path problem on an unweighted graph. That means BFS is required.
2. There can be multiple rotten oranges at the start ($t = 0$). How do you handle multiple starting points in BFS?
3. Enqueue all cells with `grid[i][j] == 2` at the very beginning with time 0.
4. When popping `(i, j)` at time $t$, each adjacent fresh orange becomes rotten at time $t + 1$. Update its time and enqueue it.
5. After BFS finishes, check if any fresh orange still has an infinite rot time. If so, return `-1`. Otherwise, return the maximum rot time observed.

</details>

### Solution Idea

<details>
<summary>Solution Idea</summary>

1. Maintain a 2D distance matrix `minute_rotten` initialized with $\infty$.
2. Scan the grid. For every cell with `grid[i][j] == 2`, set `minute_rotten[i][j] = 0` and push `(i, j)` to a queue `q`.
3. Process the queue:
   - Pop `(i, j)`.
   - For each neighbor `(ni, nj)` in 4 cardinal directions:
     - If `(ni, nj)` is within bounds, contains fresh orange (`grid[ni][nj] == 1`), and `minute_rotten[ni][nj] > rotten + 1`:
       - Set `minute_rotten[ni][nj] = rotten + 1`.
       - Push `(ni, nj)` to `q`.
4. Scan all fresh orange locations (`grid[i][j] == 1`). If any still has `minute_rotten[i][j] == inf`, return `-1`. Otherwise, return the maximum recorded time.

</details>

### Code Links

- [Problem Explanation and Complexity Analysis](../problem_solutions/rotting-oranges/README.md)
- [Python Solution](../problem_solutions/rotting-oranges/solution.py)
- [C++ Solution (Class Functions)](../problem_solutions/rotting-oranges/solution.cpp)

</details>
