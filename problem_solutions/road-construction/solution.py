import sys


def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    n = int(input_data[0])
    m = int(input_data[1])

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

    idx = 2
    output = []
    for _ in range(m):
        a = int(input_data[idx])
        b = int(input_data[idx + 1])
        union_sets(a, b)
        output.append(f"{total_components} {max_component_size}")
        idx += 2

    sys.stdout.write("\n".join(output) + "\n")


if __name__ == "__main__":
    main()
