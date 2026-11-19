import sys

# CSES trees can be up to 200,000 nodes deep
sys.setrecursionlimit(300000)


def find_tree_diameter(n: int, edges: list[tuple[int, int]]) -> int:
    if n <= 1:
        return 0

    adj_list = [[] for _ in range(n + 1)]
    for a, b in edges:
        adj_list[a].append(b)
        adj_list[b].append(a)

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
    max_distance = 0
    dfs(first_farthest, 0)

    return max_distance


def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    n = int(input_data[0])
    edges = []
    idx = 1
    for _ in range(n - 1):
        edges.append((int(input_data[idx]), int(input_data[idx + 1])))
        idx += 2

    print(find_tree_diameter(n, edges))


def test_solution():
    assert find_tree_diameter(5, [(1, 2), (1, 3), (3, 4), (3, 5)]) == 3
    assert find_tree_diameter(1, []) == 0


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
    # main()
