# Rotting Oranges

LeetCode 994: https://leetcode.com/problems/rotting-oranges/

- Difficulty: Medium
- Topics: Breadth-First Search, Array, Matrix
- Discussed: [Week 11, Day 2](../../weekly_material/week11_day2.md)

## Summary

You are given an `m x n` grid where each cell can have one of three values:
- `0` representing an empty cell,
- `1` representing a fresh orange, or
- `2` representing a rotten orange.

Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return `-1`.

## Analogy: Multi-Point Wildfire Outbreak

Imagine a dry forest grid where fresh trees are ready to burn, and lightning has simultaneously struck several trees in different locations at time $t = 0$.

- If you simulated fire spreading using DFS, you would follow one spark deep down a narrow path for miles, pretending minutes pass linearly, while ignoring that all the other lightning fires were spreading simultaneously!
- BFS (Breadth-First Search) models physical time properly: every burning tree spreads fire to all of its immediate neighbors in minute 1. In minute 2, that entire outer perimeter ignites the next ring, rippling outward in concentric waves.
- By seeding your queue with **all** initial outbreak points at time 0 (Multi-Source BFS), the clock ticks forward evenly for the entire forest. The total time taken is the time the very last fresh tree catches fire. If any fresh tree is isolated across an empty clearing, it never burns, and we return `-1`.

## Hints

<details>
<summary>Hints</summary>

1. Why is DFS unsuitable for this problem? Because DFS dives deep down a single branch, whereas all rotten oranges rot adjacent neighbors simultaneously at each minute step.
2. Shortest distance and simultaneous layer-by-layer spreading in an unweighted graph is the signature of Breadth-First Search (BFS).
3. Instead of starting BFS from a single source, initialize the queue with all cells containing rotten oranges (`grid[i][j] == 2`) at time 0.
4. When a rotten orange infects a fresh neighbor, record the neighbor's rot time as `current_time + 1` and push it into the queue.
5. After the queue empties, inspect all originally fresh oranges. If any remain unreached (distance still infinity), return `-1`. Otherwise, return the maximum time recorded.

</details>

## Solution

[`solution.py`](solution.py) / [`solution.cpp`](solution.cpp): Multi-Source Breadth-First Search (BFS).

1. Initialize a 2D distance table `minute_rotten` with infinity for all cells.
2. Scan the grid and push all initial rotten oranges (`grid[i][j] == 2`) into a queue with `minute_rotten[i][j] = 0`.
3. While the queue is not empty, pop `(i, j)`. For each of its 4 orthogonal neighbors `(ni, nj)`:
   - If `(ni, nj)` is within bounds, contains a fresh orange (`grid[ni][nj] == 1`), and its recorded rot time is strictly greater than `rotten + 1`:
     - Update `minute_rotten[ni][nj] = rotten + 1`.
     - Push `(ni, nj)` to the queue.
4. Find the maximum rot time among all fresh oranges (`grid[i][j] == 1`). If any fresh orange was never reached (`minute_rotten[i][j] == float('inf')`), return `-1`. Otherwise, return the maximum rot time.

## Correctness

- **Claim:** Multi-source BFS computes the shortest unweighted distance (in minutes) from any initial rotten orange to every fresh orange.
- **Initialization:** All sources at minute 0 are in the queue.
- **Maintenance (BFS invariant):** The queue always contains vertices ordered non-decreasingly by distance. Because edge weights are uniform (1 minute per step), when a fresh orange is first popped or updated with distance $d + 1$, no shorter path from any initial rotten orange exists.
- **Termination:** The grid is finite. Each fresh orange is enqueued at most once when its distance drops from infinity to a finite number. When the queue is empty, all reachable fresh oranges have their minimum infection time determined.

## Complexity

- **Time:** $O(m \cdot n)$, where $m$ is rows and $n$ is columns. Every cell is enqueued and dequeued at most once, and each cell explores 4 orthogonal neighbors.
- **Space:** $O(m \cdot n)$ auxiliary space for the `minute_rotten` table and the queue.
