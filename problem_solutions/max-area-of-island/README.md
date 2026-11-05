# Max Area of Island

LeetCode 695: https://leetcode.com/problems/max-area-of-island/

- Difficulty: Medium
- Topics: Array, Depth-First Search, Breadth-First Search, Union-Find, Matrix
- Discussed: [Week 11, Day 2](../../weekly_material/week11_day2.md)

## Summary

You are given an `m x n` binary matrix `grid`. An island is a group of `1`s (representing land) connected 4-directionally (horizontal or vertical). You may assume all four edges of the grid are surrounded by water.

The **area** of an island is the number of cells with a value `1` in the island.

Return the maximum area of an island in `grid`. If there is no island, return `0`.

## Analogy: Measuring Land Parcels

In [Number of Islands](../number-of-islands/README.md), your task was simply to count the number of separate ink stains on paper.

Now, imagine each cell of land is a 1-acre plot of farmland. You want to buy the single biggest continuous farm available. 

Whenever you find an unvisited plot of land, you do not just tag the island and walk away: you walk across every connecting acre, counting them up one by one. You compare the total acreage of this farm against your running record (`max_area = max(max_area, area)`).

## Structural Similarity to Number of Islands

Notice how identical the scaffolding is to [Number of Islands](../number-of-islands/README.md):
- **Traversal Engine:** Both use 4-directional DFS with boundaries check and a `visited` set (or array).
- **Outer Loop:** Both iterate through every `(i, j)` in `grid`.
- **The Only Difference:**
  - In Number of Islands, `dfs(i, j)` has return type `void`. The outer loop simply counts how many times DFS is initiated (`islands_counter += 1`).
  - In Max Area of Island, `dfs(i, j)` returns an integer representing the size of the subtree. It returns `1` (for itself) plus the sum of the areas of its unvisited land neighbors (`1 + sum(...)`). The outer loop tracks the maximum returned value.

## Hints

<details>
<summary>Hints</summary>

1. This is the exact same connected component traversal as Number of Islands.
2. Instead of merely marking cells visited, how can your recursive function return the count of cells it visits?
3. The area of an island starting at `(i, j)` is `1` (the current cell) plus the area reachable through each of its 4 orthogonal neighbors.
4. Keep a running maximum `max_area = max(max_area, dfs(i, j))` across every newly discovered island.

</details>

## Solution

[`solution.py`](solution.py) / [`solution.cpp`](solution.cpp): Component area accumulation via recursive DFS.

We iterate through all coordinates `(i, j)` in the grid. If `grid[i][j] == 1` and `(i, j)` is unvisited, we trigger `area = dfs(i, j)` and update `max_area = max(max_area, area)`.

In `dfs(i, j)`, we mark `(i, j)` as visited, and recursively evaluate every neighbor `(ni, nj)` that is in-bounds, contains `1`, and is not yet in `visited`. Each call returns `1 + sum(...)` of the areas returned by its branches.

## Correctness

- **Claim:** For any unvisited land cell `(i, j)`, `dfs(i, j)` visits every land cell in its connected component exactly once and returns the total number of cells in that component.
- **Base case:** A single isolated land cell with no adjacent land neighbors has no valid neighbor branches, returning $1 + 0 = 1$.
- **Inductive step:** By the inductive hypothesis, each recursive call on an unvisited neighbor `(ni, nj)` correctly explores its remaining sub-component and returns its exact size. Since all visited cells are marked immediately upon entry, no cell is counted more than once. Summing these values plus 1 yields the total area of the component.
- **Termination:** Because the grid is finite and each cell is marked visited on entry, every branch reaches visited cells or boundaries and terminates.

## Complexity

- **Time:** $O(m \cdot n)$, where $m$ is rows and $n$ is columns. Every grid cell is processed by the outer loop once and traversed by DFS at most once.
- **Space:** $O(m \cdot n)$ auxiliary space for the visited tracking structure and the recursion stack in the worst case (when the grid is entirely land).
