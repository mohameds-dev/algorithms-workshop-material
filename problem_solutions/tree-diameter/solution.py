import sys

# CSES trees can be up to 200,000 nodes deep
sys.setrecursionlimit(300000)


def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    n = int(input_data[0])
    adj_list = [[] for _ in range(n + 1)]

    idx = 1
    for _ in range(n - 1):
        a = int(input_data[idx])
        b = int(input_data[idx + 1])
        adj_list[a].append(b)
        adj_list[b].append(a)
        idx += 2

    farthest_node = 0
    max_distance = 0
    visited = [False] * (n + 1)

    def dfs(node: int, distance: int):
        nonlocal farthest_node, max_distance
        visited[node] = True

        if distance > max_distance:
            max_distance = distance
            farthest_node = node

        for child in adj_list[node]:
            if not visited[child]:
                dfs(child, distance + 1)

    dfs(1, 0)
    first_farthest = farthest_node

    visited = [False] * (n + 1)
    dfs(first_farthest, 0)

    print(max_distance)


if __name__ == "__main__":
    main()
