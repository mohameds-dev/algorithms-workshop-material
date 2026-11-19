# Path with Minimum Effort

LeetCode 1631: https://leetcode.com/problems/path-with-minimum-effort/

- Difficulty: Medium
- Topics: Array, Binary Search, Depth-First Search, Breadth-First Search, Union-Find, Heap, Matrix
- Discussed: [Week 13, Day 2](../../weekly_material/week13_day2__dijkstra.md)

## Summary

You are a hiker preparing for an upcoming hike. You are given `heights`, a 2D array of size `rows x columns`, where `heights[row][col]` represents the height of cell `(row, col)`.

A route's **effort** is the maximum absolute difference in heights between two consecutive cells of the route.

Return the minimum effort required to travel from the top-left cell `(0, 0)` to the bottom-right cell `(rows - 1, columns - 1)`.

## Intuition: Minimax Shortest Path via Modified Dijkstra

In standard Dijkstra, the distance metric accumulates by addition:
$$dist[v] = dist[u] + weight(u, v)$$

Here, the metric is **minimax bottleneck path**:
$$effort[v] = \max(effort[u], |height[u] - height[v]|)$$

Does Dijkstra still work?
**Yes!** Dijkstra works on any path metric where:
1. Extending a path never decreases its cost:
   $$\max(effort[u], \Delta) \ge effort[u]$$
2. Subpaths of optimal paths maintain the greedy ordering.

Because taking another step can only maintain or increase the maximum difference seen so far, the non-negative property holds, and a min-heap guarantees that cell $(r, c)$ is settled as soon as it is popped.

## Hints

<details>
<summary>Hints</summary>

1. Treat the 2D grid as a graph where each cell is a vertex, and adjacent orthogonal cells share an edge of weight $|height[r_1][c_1] - height[r_2][c_2]|$.
2. Instead of summing edge weights, track the maximum edge weight on the path.
3. Use a priority queue storing `(effort, row, col)` starting from `(0, 0, 0)`.
4. As soon as you pop the target cell `(rows - 1, cols - 1)`, return the popped effort immediately.

</details>

## Solutions

- [Python Solution](solution.py)
- [C++ Solution](solution.cpp)

## Complexity Analysis

- **Time Complexity:** $O((V + E) \log V)$ where $V = R \cdot C$ and $E \approx 4 \cdot R \cdot C$. Each cell is popped once from the priority queue, and each grid transition is evaluated at most 4 times ($O(R \cdot C \log(R \cdot C))$).
- **Space Complexity:** $O(R \cdot C)$ to store the 2D effort matrix and the min-heap.
