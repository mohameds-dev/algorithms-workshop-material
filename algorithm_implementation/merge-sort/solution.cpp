#include <bits/stdc++.h>
#include <cassert>
using namespace std;

// Merges the two already-sorted ranges a[lo, mid) and a[mid, hi) into a
// single sorted range a[lo, hi), using aux as scratch space.
void merge(vector<int> &a, vector<int> &aux, int lo, int mid, int hi) {
    for (int k = lo; k < hi; k++) aux[k] = a[k];

    int i = lo, j = mid, k = lo;
    while (i < mid && j < hi) {
        if (aux[i] <= aux[j]) a[k++] = aux[i++];
        else a[k++] = aux[j++];
    }
    while (i < mid) a[k++] = aux[i++];
    while (j < hi) a[k++] = aux[j++];
}

// Sorts a[lo, hi) in place.
void mergeSort(vector<int> &a, vector<int> &aux, int lo, int hi) {
    if (hi - lo <= 1) return; // base case: 0 or 1 elements are already sorted

    int mid = lo + (hi - lo) / 2;
    mergeSort(a, aux, lo, mid);
    mergeSort(a, aux, mid, hi);
    merge(a, aux, lo, mid, hi);
}

vector<int> mergeSort(vector<int> a) {
    vector<int> aux(a.size());
    mergeSort(a, aux, 0, (int)a.size());
    return a;
}

void test_solution() {
    vector<int> a = {5, 2, 3, 1, 4, 4, -1};
    vector<int> expected = {-1, 1, 2, 3, 4, 4, 5};
    assert(mergeSort(a) == expected);
    assert(mergeSort(vector<int>{}).empty());
    assert(mergeSort(vector<int>{1}) == vector<int>{1});
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
