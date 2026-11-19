import sys


def process_roads(n: int, roads: list[tuple[int, int]]) -> list[tuple[int, int]]:
    parent_node = list(range(n + 1))
    component_size = [1] * (n + 1)
    total_components = n
    max_component_size = 1

    def find_root(node: int) -> int:
        path = []
        curr = node
        while parent_node[curr] != curr:
            path.append(curr)
            curr = parent_node[curr]
        for p in path:
            parent_node[p] = curr
        return curr

    def union_sets(u: int, v: int) -> bool:
        nonlocal total_components, max_component_size
        root_u = find_root(u)
        root_v = find_root(v)

        if root_u == root_v:
            return False

        if component_size[root_u] < component_size[root_v]:
            root_u, root_v = root_v, root_u

        parent_node[root_v] = root_u
        component_size[root_u] += component_size[root_v]
        if component_size[root_u] > max_component_size:
            max_component_size = component_size[root_u]
        total_components -= 1
        return True

    history = []
    for a, b in roads:
        union_sets(a, b)
        history.append((total_components, max_component_size))

    return history


def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    n = int(input_data[0])
    m = int(input_data[1])

    roads = []
    idx = 2
    for _ in range(m):
        roads.append((int(input_data[idx]), int(input_data[idx + 1])))
        idx += 2

    history = process_roads(n, roads)
    for comps, max_sz in history:
        print(f"{comps} {max_sz}")


def test_solution():
    roads = [(1, 2), (3, 4), (2, 3)]
    assert process_roads(4, roads) == [(3, 2), (2, 2), (1, 4)]


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
    # main()
