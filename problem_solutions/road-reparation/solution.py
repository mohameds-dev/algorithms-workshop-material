import sys


def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    n = int(input_data[0])
    m = int(input_data[1])

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

    edges = []
    idx = 2
    for _ in range(m):
        u = int(input_data[idx])
        v = int(input_data[idx + 1])
        cost = int(input_data[idx + 2])
        edges.append((cost, u, v))
        idx += 3

    edges.sort()

    total_cost = 0
    edges_added = 0

    for cost, u, v in edges:
        if union_sets(u, v):
            total_cost += cost
            edges_added += 1
            if edges_added == n - 1:
                break

    if edges_added == n - 1:
        print(total_cost)
    else:
        print("IMPOSSIBLE")


if __name__ == "__main__":
    main()
