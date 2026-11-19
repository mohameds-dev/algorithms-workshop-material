#include <cassert>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int fib(int n) {
        // base case
        if (n == 0) return 0;
        if (n == 1) return 1;

        // transition
        return fib(n - 1) + fib(n - 2);
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
