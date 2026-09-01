def merge(a, aux, lo, mid, hi):
    """Merges the already-sorted ranges a[lo:mid] and a[mid:hi] into a[lo:hi]."""
    for k in range(lo, hi):
        aux[k] = a[k]

    i, j, k = lo, mid, lo
    # pick the minimum of the two and move it
    while i < mid and j < hi:
        if aux[i] <= aux[j]:
            a[k] = aux[i]
            i += 1
        else:
            a[k] = aux[j]
            j += 1
        k += 1

    # if there's still leftovers in first half, pick them
    while i < mid:
        a[k] = aux[i]
        i += 1
        k += 1
    # if there's still leftovers in second half, pick them
    while j < hi:
        a[k] = aux[j]
        j += 1
        k += 1


def merge_sort(a, aux, lo, hi):
    """Sorts a[lo:hi] in place."""
    if hi - lo <= 1:
        return  # base case: 0 or 1 elements are already sorted

    mid = lo + (hi - lo) // 2
    merge_sort(a, aux, lo, mid)
    merge_sort(a, aux, mid, hi)
    merge(a, aux, lo, mid, hi)


def sort(a):
    a = list(a)
    aux = [0] * len(a)
    merge_sort(a, aux, 0, len(a))
    return a


if __name__ == "__main__":
    a = [5, 2, 3, 1, 4, 4, -1]
    print(sort(a))
