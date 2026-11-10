from collections import deque
import sys


def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    n = int(input_data[0])
    m = int(input_data[1])

    in_degree = [0] * (n + 1)
    adj_list = [[] for _ in range(n + 1)]

    idx = 2
    for _ in range(m):
        a = int(input_data[idx])
        b = int(input_data[idx + 1])
        adj_list[a].append(b)
        in_degree[b] += 1
        idx += 2

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
        print("IMPOSSIBLE")
    else:
        print(*(top_sorted))


if __name__ == "__main__":
    main()
