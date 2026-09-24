def merge_and_count(a, aux, lo, mid, hi):
    """Merges the sorted a[lo:mid] and a[mid:hi], returns their cross inversions."""
    for k in range(lo, hi):
        aux[k] = a[k]

    i, j, k = lo, mid, lo
    inversions = 0
    while i < mid and j < hi:
        if aux[i] <= aux[j]:
            a[k] = aux[i]
            i += 1
        else:
            a[k] = aux[j]
            j += 1
            inversions += mid - i
        k += 1

    while i < mid:
        a[k] = aux[i]
        i += 1
        k += 1
    while j < hi:
        a[k] = aux[j]
        j += 1
        k += 1

    return inversions


def count_inversions(a, aux, lo, hi):
    """Counts inversions in a[lo:hi], sorting it in place along the way."""
    if hi - lo <= 1:
        return 0  # base case: 0 or 1 elements have no inversions

    mid = lo + (hi - lo) // 2
    inversions = count_inversions(a, aux, lo, mid)
    inversions += count_inversions(a, aux, mid, hi)
    inversions += merge_and_count(a, aux, lo, mid, hi)
    return inversions


def count(nums):
    a = list(nums)
    aux = [0] * len(a)
    return count_inversions(a, aux, 0, len(a))


if __name__ == "__main__":
    print(count([2, 4, 1, 3, 5]))
