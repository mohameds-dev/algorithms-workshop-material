import sys


def min_repair_cost(n: int, edges: list[tuple[int, int, int]]) -> int:
    parent = list(range(n + 1))
    rank = [0] * (n + 1)

    def find_root(i: int) -> int:
        path = []
        curr = i
        while parent[curr] != curr:
            path.append(curr)
            curr = parent[curr]
        for p in path:
            parent[p] = curr
        return curr

    def union_sets(u: int, v: int) -> bool:
        root_u = find_root(u)
        root_v = find_root(v)

        if root_u == root_v:
            return False

        if rank[root_u] < rank[root_v]:
            root_u, root_v = root_v, root_u
        parent[root_v] = root_u
        if rank[root_u] == rank[root_v]:
            rank[root_u] += 1
        return True

    # edges: (u, v, cost)
    sorted_edges = sorted(edges, key=lambda x: x[2])

    total_cost = 0
    edges_added = 0

    for u, v, cost in sorted_edges:
        if union_sets(u, v):
            total_cost += cost
            edges_added += 1
            if edges_added == n - 1:
                break

    return total_cost if edges_added == n - 1 else -1


def main():
    input = sys.stdin.readline  # to avoid TLE on CSES
    n, m = map(int, input().split())

    edges = []
    for _ in range(m):
        u, v, cost = map(int, input().split())
        edges.append((u, v, cost))

    cost = min_repair_cost(n, edges)
    if cost == -1:
        print("IMPOSSIBLE")
    else:
        print(cost)


def test_solution():
    edges = [(1, 2, 3), (2, 3, 5), (2, 4, 2), (3, 4, 8), (5, 1, 7), (5, 4, 4)]
    assert min_repair_cost(5, edges) == 14
    assert min_repair_cost(3, [(1, 2, 10)]) == -1


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
    # main()
