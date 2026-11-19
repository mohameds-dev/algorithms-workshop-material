#include <bits/stdc++.h>
#include <cassert>
using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        vector<int> mem(n + 2, 0);
        mem[0] = 1;

        for (int i = 0; i < n; ++i) {
            mem[i + 1] += mem[i];
            mem[i + 2] += mem[i];
        }

        return mem[n];
    }
};

void test_solution() {
    Solution sol;
    assert(sol.climbStairs(2) == 2);
    assert(sol.climbStairs(3) == 3);
    assert(sol.climbStairs(5) == 8);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
