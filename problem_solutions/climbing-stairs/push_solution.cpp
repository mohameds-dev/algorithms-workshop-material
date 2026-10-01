#include <bits/stdc++.h>
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

int main() {
    Solution sol;
    cout << sol.climbStairs(5) << "\n";  // 8
    return 0;
}
