# Road Reparation

CSES 1675: https://cses.fi/problemset/task/1675

- Difficulty: Medium
- Topics: Graph, Minimum Spanning Tree (MST), Kruskal's Algorithm, Disjoint Set Union (DSU)
- Discussed: [Week 13, Day 1](../../weekly_material/week13_day1.md)

## Summary

There are $n$ cities and $m$ roads between them. Each road has an associated repair cost. Determine the minimum total cost to repair a subset of roads such that all cities are mutually reachable. If it is impossible to connect all cities, print `IMPOSSIBLE`.

## Intuition: Kruskal's Algorithm via Greedy Edge Choice

This is the canonical Minimum Spanning Tree (MST) problem:
1. A spanning tree on $n$ vertices must contain exactly $n - 1$ edges and contain no cycles.
2. Kruskal's algorithm greedily considers edges in non-decreasing order of cost.
3. For each candidate edge $(u, v)$ with cost $c$:
   - Check if $u$ and $v$ belong to different connected components using `find_root(u) != find_root(v)`.
   - If they are already in the same component, adding the edge would form a cycle; discard it.
   - If they are in different components, greedily include the edge, add $c$ to `total_cost`, increment `edges_added`, and merge the sets using `union_sets(u, v)`.
4. If after checking all edges `edges_added == n - 1`, the graph is fully connected; output `total_cost`. Otherwise, print `IMPOSSIBLE`.

## Correctness Proof: Kruskal's Algorithm (Induction and Contradiction)

### 1. Observation from the Problem
- Any spanning tree connects all $n$ vertices with $n - 1$ edges and no cycles.
- When partitioned by any cut $(S, V - S)$, at least one crossing edge must be included.

### 2. The Cut Property via Exchange Argument
- **Claim:** The minimum-weight edge $e^*$ crossing any cut $(S, V - S)$ belongs to an MST.
- **Proof by Contradiction and Exchange:**
  1. Suppose an MST $T$ does not contain $e^* = (u, v)$.
  2. Adding $e^*$ to $T$ creates a unique cycle $C$.
  3. Because $u \in S$ and $v \in V - S$, cycle $C$ must cross back from $V - S$ to $S$ using another edge $e'$.
  4. Swapping $e'$ for $e^*$ yields $T' = (T - \{e'\}) \cup \{e^*\}$.
  5. Since $e^*$ is minimal on the cut, $cost(e^*) \le cost(e')$, so $cost(T') \le cost(T)$.
  6. Since $T$ was minimal, $cost(T') = cost(T)$, so $T'$ is also an MST containing $e^*$.

### 3. Kruskal's Correctness by Induction
- **Base Case:** 0 edges accepted is trivially a subset of an MST.
- **Inductive Step:** Suppose accepted set $T_k$ is a subset of an MST. The next cheapest edge $e = (u, v)$ connecting distinct components crosses the cut $(C_u, V - C_u)$, where $C_u$ is the component containing $u$. Because all cheaper edges have already been processed, $e$ is the minimum-weight crossing edge for this cut. By the Cut Property, $T_k \cup \{e\}$ is a subset of an MST.
- **Cycle Discard:** If $find(u) == find(v)$, adding $(u, v)$ would create a cycle where $(u, v)$ is the heaviest edge. By the Cycle Property, it cannot be in an MST and is safely discarded.

## Hints

<details>
<summary>Hints</summary>

1. Sort all roads ascending by cost.
2. Use DSU to keep track of connected components.
3. Keep a counter of how many edges you have accepted into the spanning tree.
4. Stop early once you have accepted $n - 1$ edges.
5. Watch out for integer overflow: edge costs can sum to $> 2 \cdot 10^{14}$, requiring a 64-bit integer (`long long` in C++).

</details>

## Solutions

- [Python Solution](solution.py)
- [C++ Solution](solution.cpp)

## Complexity Analysis

- **Time Complexity:** $O(m \log m)$ to sort the edges. The DSU operations take $O(m \log n)$, so sorting dominates. Total time is $O(m \log m)$.
- **Space Complexity:** $O(n + m)$ to store the edge list and the DSU parent/rank arrays.
