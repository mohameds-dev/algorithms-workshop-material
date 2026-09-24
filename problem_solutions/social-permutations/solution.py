def backtrack(n, index, p, used):
    if index == n:
        print(p)
        return

    for v in range(n):
        if used[v] or v == index:
            continue  # v already placed, or self-gift

        if v < index and p[v] == index:
            continue  # p[v] already points back to index: mutual gift

        p[index] = v
        used[v] = True
        backtrack(n, index + 1, p, used)
        used[v] = False


def print_social_permutations(n):
    p = [0] * n
    used = [False] * n
    backtrack(n, 0, p, used)


if __name__ == "__main__":
    print_social_permutations(3)
