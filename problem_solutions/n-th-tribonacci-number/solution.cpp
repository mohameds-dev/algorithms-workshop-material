#include <cassert>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Space-optimized bottom-up DP: O(n) time, O(1) space
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

    // Full bottom-up tabulation: O(n) time, O(n) space
    int tribonacciTabulation(int n) {
        if (n <= 1) return n;

        vector<int> trib(n + 1, -1);
        trib[0] = 0;
        trib[1] = 1;
        trib[2] = 1;

        for (int i = 3; i <= n; ++i) {
            trib[i] = trib[i - 1] + trib[i - 2] + trib[i - 3];
        }

        return trib[n];
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
