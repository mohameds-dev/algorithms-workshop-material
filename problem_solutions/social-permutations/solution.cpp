#include <bits/stdc++.h>
#include <cassert>
using namespace std;

// Fills p[index:] and, once every position is filled, stores one social
// permutation. used[v] marks whether value v is already assigned.
void backtrack(int n, int index, vector<int> &p, vector<bool> &used, vector<vector<int>> &results) {
    if (index == n) {
        results.push_back(p);
        return;
    }

    for (int v = 0; v < n; v++) {
        if (used[v] || v == index) continue;       // v already placed, or self-gift
        if (v < index && p[v] == index) continue;  // p[v] already points back: mutual gift

        p[index] = v;
        used[v] = true;
        backtrack(n, index + 1, p, used, results);
        used[v] = false;
    }
}

vector<vector<int>> getSocialPermutations(int n) {
    vector<int> p(n);
    vector<bool> used(n, false);
    vector<vector<int>> results;
    backtrack(n, 0, p, used, results);
    return results;
}

void printSocialPermutations(int n) {
    for (const auto &p : getSocialPermutations(n)) {
        cout << "[";
        for (int i = 0; i < n; i++) {
            cout << p[i];
            if (i + 1 < n) cout << ", ";
        }
        cout << "]\n";
    }
}

void test_solution() {
    vector<vector<int>> perms3 = getSocialPermutations(3);
    vector<vector<int>> expected3 = {{1, 2, 0}, {2, 0, 1}};
    assert(perms3 == expected3);
    assert(getSocialPermutations(2).empty());
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    // printSocialPermutations(3);
    return 0;
}
