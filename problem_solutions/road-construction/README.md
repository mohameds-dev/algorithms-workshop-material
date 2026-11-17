# Road Construction

CSES 1676: https://cses.fi/problemset/task/1676

- Difficulty: Medium
- Topics: Graph, Disjoint Set Union (DSU), Connected Components
- Discussed: [Week 13, Day 1](../../weekly_material/week13_day1.md)

## Summary

There are $n$ cities and initially no roads. A total of $m$ roads are built one by one. After each road is added, output two values:
1. The total number of connected components.
2. The size of the largest connected component.

## Intuition: Disjoint Set Union with Metadata Tracking

This problem is the foundational template for Disjoint Set Union (DSU / Union-Find).

Each city starts in its own component:
- `total_components = n`
- `component_size[i] = 1` for all $i \in \{1, \dots, n\}$
- `max_component_size = 1`

When a road connects city $a$ and city $b$:
1. We query their component representatives using `find_root(a)` and `find_root(b)`.
2. If `root_a == root_b`, the cities are already connected; adding this road creates a cycle and does not alter components or sizes.
3. If `root_a != root_b`, we merge the smaller component into the larger component:
   - `component_size[root_a] += component_size[root_b]`
   - `total_components -= 1`
   - `max_component_size = max(max_component_size, component_size[root_a])`

## Hints

<details>
<summary>Hints</summary>

1. You do not need to construct an adjacency list or run BFS/DFS on every query. DSU maintains dynamic connectivity in near-constant time.
2. Maintain `parent[i]` for path compression and `size[i]` for union by size.
3. Track two global variables: `total_components` (initialized to $n$) and `max_size` (initialized to 1).
4. When `union(a, b)` successfully joins two distinct sets, decrement `total_components` by 1 and update `max_size`.

</details>

## Solutions

- [Python Solution](solution.py)
- [C++ Solution](solution.cpp)

## Complexity Analysis

- **Time Complexity:** $O(m \log n)$ across all $m$ road additions. Path compression and union by size keep tree depth bounded by $O(\log n)$, running well within the 1.0 second limit for $m = 2 \cdot 10^5$.
- **Space Complexity:** $O(n)$ to store `parent_node` and `component_size` arrays.
