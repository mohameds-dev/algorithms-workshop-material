#include <cassert>
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    vector<int> mem;

    int solve(int num) {
        if (num <= 2) {
            return (num > 0) ? 1 : 0;
        }

        if (mem[num] == -1) {
            mem[num] = solve(num - 1) + solve(num - 2) + solve(num - 3);
        }

        return mem[num];
    }

public:
    int tribonacci(int n) {
        if (n <= 1) return n;

        mem.assign(n + 1, -1);
        return solve(n);
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
