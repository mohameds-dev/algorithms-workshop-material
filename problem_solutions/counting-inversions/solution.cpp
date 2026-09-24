#include <bits/stdc++.h>
using namespace std;

// Merges the two already-sorted ranges a[lo, mid) and a[mid, hi) into a
// single sorted range a[lo, hi), using aux as scratch space, and returns the
// number of cross inversions: pairs (i, j) with lo <= i < mid <= j < hi and
// a[i] > a[j].
long long mergeAndCount(vector<int> &a, vector<int> &aux, int lo, int mid, int hi) {
    for (int k = lo; k < hi; k++) aux[k] = a[k];

    long long inversions = 0;
    int i = lo, j = mid, k = lo;
    while (i < mid && j < hi) {
        if (aux[i] <= aux[j]) a[k++] = aux[i++];
        else {
            a[k++] = aux[j++];
            inversions += mid - i;
        }
    }
    while (i < mid) a[k++] = aux[i++];
    while (j < hi) a[k++] = aux[j++];

    return inversions;
}

// Counts inversions in a[lo, hi), sorting it in place along the way.
long long countInversions(vector<int> &a, vector<int> &aux, int lo, int hi) {
    if (hi - lo <= 1) return 0; // base case: 0 or 1 elements have no inversions

    int mid = lo + (hi - lo) / 2;
    long long inversions = countInversions(a, aux, lo, mid);
    inversions += countInversions(a, aux, mid, hi);
    inversions += mergeAndCount(a, aux, lo, mid, hi);
    return inversions;
}

long long countInversions(vector<int> a) {
    vector<int> aux(a.size());
    return countInversions(a, aux, 0, (int)a.size());
}

int main() {
    vector<int> a = {2, 4, 1, 3, 5};
    cout << countInversions(a) << endl;

    return 0;
}
