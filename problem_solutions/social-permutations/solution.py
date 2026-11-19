def backtrack(n, index, p, used, results):
    if index == n:
        results.append(p.copy())
        return

    for v in range(n):
        if used[v] or v == index:
            continue  # v already placed, or self-gift

        if v < index and p[v] == index:
            continue  # p[v] already points back to index: mutual gift

        p[index] = v
        used[v] = True
        backtrack(n, index + 1, p, used, results)
        used[v] = False


def get_social_permutations(n: int) -> list[list[int]]:
    p = [0] * n
    used = [False] * n
    results = []
    backtrack(n, 0, p, used, results)
    return results


def print_social_permutations(n: int):
    for p in get_social_permutations(n):
        print(p)


def test_solution():
    perms3 = get_social_permutations(3)
    assert perms3 == [[1, 2, 0], [2, 0, 1]]
    assert len(get_social_permutations(2)) == 0


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
    # print_social_permutations(3)
