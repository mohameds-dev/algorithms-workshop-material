#include <bits/stdc++.h>
using namespace std;

// Fills p[index:] and, once every position is filled, prints one social
// permutation. used[v] marks whether value v is already assigned to an
// earlier position.
void backtrack(int n, int index, vector<int> &p, vector<bool> &used) {
    if (index == n) {
        cout << "[";
        for (int i = 0; i < n; i++) {
            cout << p[i];
            if (i + 1 < n) cout << ", ";
        }
        cout << "]" << endl;
        return;
    }

    for (int v = 0; v < n; v++) {
        if (used[v] || v == index) continue;       // v already placed, or self-gift
        if (v < index && p[v] == index) continue;  // p[v] already points back: mutual gift

        p[index] = v;
        used[v] = true;
        backtrack(n, index + 1, p, used);
        used[v] = false;
    }
}

void printSocialPermutations(int n) {
    vector<int> p(n);
    vector<bool> used(n, false);
    backtrack(n, 0, p, used);
}

int main() {
    printSocialPermutations(3);

    return 0;
}
