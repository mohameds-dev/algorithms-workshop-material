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
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    n = int(input_data[0])
    m = int(input_data[1])

    edges = []
    idx = 2
    for _ in range(m):
        a = int(input_data[idx])
        b = int(input_data[idx + 1])
        edges.append((a, b))
        idx += 2

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
