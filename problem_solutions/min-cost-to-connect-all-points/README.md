# Min Cost to Connect All Points

LeetCode 1584: https://leetcode.com/problems/min-cost-to-connect-all-points/

- Difficulty: Medium
- Topics: Graph, Minimum Spanning Tree (MST), Prim's Algorithm, Kruskal's Algorithm, Disjoint Set Union (DSU)
- Discussed: [Week 13, Day 1](../../weekly_material/week13_day1.md)

## Summary

You are given an array `points` representing integer coordinates of some points on a 2D-plane, where `points[i] = [xi, yi]`.

The cost of connecting two points `[xi, yi]` and `[xj, yj]` is the Manhattan distance between them: $|x_i - x_j| + |y_i - y_j|$.

Return the minimum cost to make all points connected. All points are connected if there is exactly one simple path between any two points.

## Algorithm Choice: Kruskal's vs Prim's on Dense Graphs

This problem is defined on an **implicit complete graph**: every pair of points has an edge, so $E = \frac{V(V - 1)}{2} \approx \frac{V^2}{2}$. For $V = 1000$, there are roughly $5 \cdot 10^5$ edges.

### 1. Kruskal's Algorithm
- Must generate and store all $E \approx 5 \cdot 10^5$ edges.
- Sorting edges takes $O(E \log E) \approx O(V^2 \log V)$ time.
- Memory: $O(V^2)$ to store all edges in memory.

### 2. Dense Prim's Algorithm (Without Priority Queue)
- Rather than maintaining an explicit edge list or binary heap, maintain a single 1D array `min_dist[v]`, which records the minimum distance from node $v$ to any node already included in the MST.
- In each of the $V$ steps:
  1. Scan `min_dist` to find the unvisited node $u$ with minimum distance ($O(V)$ scan).
  2. Add $u$ to the MST and accumulate `min_dist[u]`.
  3. Update `min_dist[v] = min(min_dist[v], manhattan_dist(u, v))` for all unvisited nodes $v$ ($O(V)$ scan).
- Total time: $V \times O(V) = O(V^2)$.
- Total auxiliary space: $O(V)$ (only the `min_dist` and `in_mst` arrays).

On a dense graph ($E = \Theta(V^2)$), simple $O(V^2)$ Prim's is asymptotically faster and significantly more memory-efficient than $O(E \log E)$ Kruskal's or $O(E \log V)$ heap-based Prim's.

## Correctness Proof: Prim's Algorithm (Cut Property Induction)

### 1. Observation from the Problem
- Prim's algorithm starts with an arbitrary node $S = \{0\}$ and in each step connects one unvisited node $u \in V \setminus S$ to $S$.
- At step $k$, the cut $(S, V \setminus S)$ partitions the graph into visited and unvisited vertices.

### 2. Proof by Induction on Added Vertices
- **Base Case:** $S = \{0\}$ trivially has 0 edges and is a subset of an MST.
- **Inductive Step:** Suppose tree on $S$ is a subset of an MST. The algorithm picks $u \in V \setminus S$ minimizing distance to $S$. By definition, this edge is the minimum-weight edge crossing the cut $(S, V \setminus S)$. By the Cut Property, this edge belongs to an MST extending the current tree.
- **Termination:** After $V - 1$ steps, all vertices are included with $V - 1$ edges, forming a valid MST.

## Hints

<details>
<summary>Hints</summary>

1. Manhattan distance between points $(x_1, y_1)$ and $(x_2, y_2)$ is $|x_1 - x_2| + |y_1 - y_2|$.
2. This is an unrooted Minimum Spanning Tree on a complete graph with $n$ vertices.
3. Because every pair has an edge, generating all edges takes $O(n^2)$ space and $O(n^2 \log n)$ time with Kruskal's.
4. Can you compute distances on the fly? Prim's algorithm with an array `min_dist` of size $n$ requires only $O(n)$ space and runs in $O(n^2)$ time.

</details>

## Solutions

- [Python Solution](solution.py)
- [C++ Solution](solution.cpp)

## Complexity Analysis

- **Time Complexity:** $O(V^2)$ where $V = n$ is the number of points. In each of the $V$ iterations, we scan $V$ points to find the minimum distance node, and scan $V$ points to relax neighbor distances.
- **Space Complexity:** $O(V)$ to store `min_dist` and `in_mst` arrays. No edge list is stored in memory.
