from collections import deque
import sys


def find_order(n: int, prerequisites: list[tuple[int, int]]) -> list[int]:
    in_degree = [0] * (n + 1)
    adj_list = [[] for _ in range(n + 1)]

    for a, b in prerequisites:
        adj_list[a].append(b)
        in_degree[b] += 1

    q = deque([i for i in range(1, n + 1) if in_degree[i] == 0])
    top_sorted = []

    while q:
        current = q.popleft()
        top_sorted.append(current)

        for child in adj_list[current]:
            in_degree[child] -= 1
            if in_degree[child] == 0:
                q.append(child)

    if len(top_sorted) < n:
        return []
    return top_sorted


def main():
    input = sys.stdin.readline  # to avoid TLE on CSES
    n, m = map(int, input().split())

    edges = []
    for _ in range(m):
        a, b = map(int, input().split())
        edges.append((a, b))

    order = find_order(n, edges)
    if not order:
        print("IMPOSSIBLE")
    else:
        print(*(order))


def test_solution():
    assert find_order(4, [(1, 2), (2, 3), (3, 4)]) == [1, 2, 3, 4]
    assert find_order(2, [(1, 2), (2, 1)]) == []


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
    # main()
