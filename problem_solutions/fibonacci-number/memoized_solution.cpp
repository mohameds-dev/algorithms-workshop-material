#include <cassert>
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    vector<int> memo;

    int solve(int k) {
        if (k == 0) return 0;
        if (k == 1) return 1;
        if (memo[k] != -1) return memo[k];

        memo[k] = solve(k - 1) + solve(k - 2);
        return memo[k];
    }

public:
    int fib(int n) {
        memo.assign(n + 2, -1);
        return solve(n);
    }
};

void test_solution() {
    Solution sol;
    assert(sol.fib(0) == 0);
    assert(sol.fib(1) == 1);
    assert(sol.fib(2) == 1);
    assert(sol.fib(3) == 2);
    assert(sol.fib(4) == 3);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
