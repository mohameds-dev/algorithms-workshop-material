# Checking Existence of Edge Length Limited Paths

LeetCode 1697: https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths/

- Difficulty: Hard
- Topics: Graph, Disjoint Set Union (DSU), Sorting, Offline Queries
- Discussed: [Week 13, Day 1](../../weekly_material/week13_day1__dsu_and_mst.md)

## Summary

An undirected graph of $n$ nodes is given, with edge weights in `edgeList`. You are also given an array of queries, where each query `queries[j] = [p, q, limit]` asks: is there a path between node $p$ and node $q$ such that every edge on the path has length strictly less than `limit`?

Return a boolean array of answers corresponding to each query.

## Intuition: Offline Query Processing with Monotonic DSU

Standard DSU supports adding edges, but does not support removing edges efficiently (rollbacks are expensive).

Notice the key insight:
- We do not need to answer queries in the exact order they are given (we can process them **offline**).
- If we sort all queries by their `limit` in increasing order, the set of allowable edges only ever grows!
- For a query with limit $L$, any edge with weight $< L$ is allowed. When moving to the next query with a larger limit $L'$, we only need to add the new edges whose weights fall between $L$ and $L'$.
- Edges that were valid for limit $L$ remain valid for limit $L'$.

### Algorithm Pipeline

1. Sort `edgeList` ascending by edge weight.
2. Store each query along with its original index `(p, q, limit, orig_idx)` and sort ascending by `limit`.
3. Maintain a DSU over $n$ elements and an edge pointer `edge_idx = 0`.
4. For each sorted query `(p, q, limit, orig_idx)`:
   - While `edgeList[edge_idx].weight < limit`:
     - Union `edgeList[edge_idx].u` and `edgeList[edge_idx].v`.
     - Advance `edge_idx`.
   - Query answer: `ans[orig_idx] = (find(p) == find(q))`.
5. Return `ans`.

## Correctness Proof: Monotonic Subgraph Growth (Induction)

### 1. Observation from the Problem
- A path satisfies query $j = [u, v, limit]$ if and only if all its edges belong to the subgraph $G_{limit} = (V, \{e \in E \mid weight(e) < limit\})$.
- If queries are sorted by limit: $L_1 \le L_2 \le \dots \le L_Q$, the valid edge sets grow monotonically: $G_{L_1} \subseteq G_{L_2} \subseteq \dots \subseteq G_{L_Q}$.

### 2. Proof by Induction on Query Limit
- **Base Case:** Before query 1, all edges with weight $< L_1$ are unioned. By DSU properties, `find(u) == find(v)` if and only if $u$ and $v$ are connected in $G_{L_1}$.
- **Inductive Step:** Assuming DSU matches $G_{L_k}$, for query $k + 1$ with $L_{k+1} \ge L_k$, we only insert edges with $L_k \le weight < L_{k+1}$. Because edges are sorted, all valid edges are present and no invalid edge ($\ge L_{k+1}$) is added. Thus, DSU matches $G_{L_{k+1}}$.

## Hints

<details>
<summary>Hints</summary>

1. Answering each query independently with BFS/DFS would take $O(Q \cdot (V + E))$ time, which TLEs for $10^5$ queries.
2. DSU is great at answering reachability queries dynamically as edges are added.
3. Can you reorder the queries so that edges are only ever added and never removed?
4. Sort both the edges by weight and the queries by limit.
5. Remember to restore the answers back to their original query indices before returning.

</details>

## Solutions

- [Python Solution](solution.py)
- [C++ Solution](solution.cpp)

## Complexity Analysis

- **Time Complexity:** $O(E \log E + Q \log Q + (E + Q) \log V)$. Sorting edges takes $O(E \log E)$ and sorting queries takes $O(Q \log Q)$. Each edge insertion and query takes amortized $O(\log V)$ via DSU.
- **Space Complexity:** $O(V + Q)$ to store the DSU parent/rank arrays, indexed queries, and answer array.
