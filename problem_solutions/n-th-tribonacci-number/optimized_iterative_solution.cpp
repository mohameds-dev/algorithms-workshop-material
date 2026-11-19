#include <cassert>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int tribonacci(int n) {
        if (n <= 1) return n;

        int a0 = 0;
        int a1 = 1;
        int a2 = 1;

        for (int i = 3; i <= n; ++i) {
            int next_val = a0 + a1 + a2;
            a0 = a1;
            a1 = a2;
            a2 = next_val;
        }

        return a2;
    }
};

void test_solution() {
    Solution sol;
    assert(sol.tribonacci(4) == 4);
    assert(sol.tribonacci(25) == 1389537);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
