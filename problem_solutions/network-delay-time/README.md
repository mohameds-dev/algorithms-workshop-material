# Network Delay Time

LeetCode 743: https://leetcode.com/problems/network-delay-time/

- Difficulty: Medium
- Topics: Graph, Shortest Path, Dijkstra's Algorithm, Priority Queue, Heap
- Discussed: [Week 13, Day 2](../../weekly_material/week13_day2__dijkstra.md)

## Summary

You are given a network of $n$ nodes labeled from $1$ to $n$. You are also given `times`, a list of directed edges `times[i] = [ui, vi, wi]`, where $w_i$ is the time it takes for a signal to travel from $u_i$ to $v_i$.

We send a signal from a given node $k$. Return the minimum time it takes for all $n$ nodes to receive the signal. If it is impossible for all $n$ nodes to receive the signal, return `-1`.

## Intuition

Since all signals travel simultaneously along outgoing edges:
1. The time it takes for node $v$ to receive the signal is the length of the shortest path from source node $k$ to $v$.
2. Once the signal reaches all nodes, the total elapsed time before the very last node receives the signal is the **maximum of all shortest path distances**:
   $$\text{answer} = \max_{1 \le i \le n} dist[i]$$
3. If any node $v$ has $dist[v] == \infty$, the signal never reached $v$, so return `-1`.

## Correctness Proof

### 1. Observation from the Problem
- All travel times are non-negative ($w_i \ge 0$).
- When a signal propagates out from $k$, each node $u$ receives the signal at its shortest path distance from $k$.
- The entire network is fully notified at time $\max_u dist[u]$.

### 2. Step-by-Step Proof
- **Claim:** Running Dijkstra from source $k$ yields exact shortest path distances for all reachable nodes.
- **Proof:**
  1. All edge weights are $\ge 0$.
  2. Because we always pop the minimum distance node first and edge weights cannot be negative, no unexplored detour through unvisited nodes can reach an already-popped node with a smaller cost.
  3. Therefore, every popped node has its final shortest distance settled upon extraction.
  4. Taking $\max_{1 \le i \le n} dist[i]$ gives the arrival time at the latest receiving node. If any $dist[i] = \infty$, that node is unreachable from $k$, correctly yielding `-1`.

## Hints

<details>
<summary>Hints</summary>

1. Signals travel simultaneously outward from node $k$. The time a node receives the signal is its shortest path distance from $k$.
2. Run Dijkstra's algorithm starting from source $k$.
3. Check the maximum value in your `dist` array from index $1$ to $n$.
4. If the maximum is $\infty$, at least one node was unreachable; return `-1`. Otherwise, return the maximum.

</details>

## Solutions

- [Python Solution](solution.py)
- [C++ Solution](solution.cpp)

## Complexity Analysis

- **Time Complexity:** $O((V + E) \log V)$ where $V = n$ and $E = \text{len}(times)$. Building the adjacency list takes $O(V + E)$. Dijkstra extracts each vertex from the priority queue and relaxes each directed edge at most once ($O(E \log V)$).
- **Space Complexity:** $O(V + E)$ to store the adjacency list, distance array, and priority queue.
