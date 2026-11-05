# Number of Islands

LeetCode 200: https://leetcode.com/problems/number-of-islands/

- Difficulty: Medium
- Topics: Array, Depth-First Search, Breadth-First Search, Union-Find, Matrix
- Discussed: [Week 11, Day 2](../../weekly_material/week11_day2.md)

## Summary

Given an `m x n` 2D binary grid `grid` which represents a map of `'1'`s (land) and `'0'`s (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are completely surrounded by water.

## Analogy: Counting Ink Blotches

Imagine looking at a grid of paper where ink drops have soaked into patches of paper. Each continuous blotch of ink that touches horizontally or vertically forms a single stain (an island). 

When you scan the paper from top to bottom, left to right, every time you discover an uncolored ink spot:
1. You say: "Aha, here is a brand-new island!" (increment your island counter).
2. You take a highlighter and trace every connected drop of ink in that entire blotch until the whole island is highlighted (visited).
3. You resume scanning. Any highlighted drop you encounter later is skipped because it belongs to an island you already counted.

## Hints

<details>
<summary>Hints</summary>

1. A 2D grid is an implicit graph where each cell `(i, j)` is a vertex, and orthogonal neighbors `(i +- 1, j)` and `(i, j +- 1)` are connected by edges if they are both land.
2. How do you find the number of connected components in a graph?
3. Scan every cell in the grid. Whenever you find an unvisited `'1'`, it must belong to a new island.
4. From that cell, launch a traversal (DFS or BFS) to visit all reachable connected land cells, marking them visited so they are not counted again.

</details>

## Solution

[`solution.py`](solution.py) / [`solution.cpp`](solution.cpp): Connected component counting using Depth-First Search (DFS).

We iterate through every cell `(i, j)` in the grid. If `grid[i][j] == '1'` and the cell has not yet been visited, we increment our island counter and invoke `dfs(i, j)`.

The recursive DFS visits `(i, j)`, adds it to our visited tracker, and recurses into all four orthogonal neighbors (up, down, left, right) that are inside grid boundaries, contain land `'1'`, and have not yet been visited. Once the traversal finishes, every cell in this connected component is marked visited.

## Correctness

- **Claim:** The final counter equals the exact number of connected components of `'1'`s in the grid.
- **Base case:** If the grid contains only water `'0'`, no DFS is triggered, returning 0.
- **Inductive step:** Every time the outer loop encounters an unvisited `'1'`, that cell cannot be connected to any previously visited component (otherwise it would have already been marked visited). Thus, it belongs to a new, distinct island. The DFS then exhausts all reachable land cells in that component before returning.
- **Termination:** The grid is finite ($m \times n$). Because each cell is marked visited on its first exploration and visited cells are never revisited, the traversal is guaranteed to terminate.

## Complexity

- **Time:** $O(m \cdot n)$, where $m$ is the number of rows and $n$ is the number of columns. Every cell is examined by the outer loop once, and each land cell is visited at most once during DFS.
- **Space:** $O(m \cdot n)$ to maintain the visited tracker and the recursion call stack in the worst case (e.g. a grid completely filled with land).
