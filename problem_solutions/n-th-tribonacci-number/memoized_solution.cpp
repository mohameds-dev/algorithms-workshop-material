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

int main() {
    Solution sol;
    cout << sol.tribonacci(4) << "\n";   // 4
    cout << sol.tribonacci(25) << "\n";  // 1389537
    return 0;
}
