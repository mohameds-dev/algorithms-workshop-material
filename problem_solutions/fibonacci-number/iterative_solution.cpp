#include <cassert>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int fib(int n) {
        // LeetCode constrains n to 0..30
        int fibVals[31];

        // equivalent to the base case in the recursive solution
        fibVals[0] = 0;
        fibVals[1] = 1;

        for (int i = 2; i <= n; ++i) {
            // transition
            fibVals[i] = fibVals[i - 1] + fibVals[i - 2];
        }

        return fibVals[n];
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
