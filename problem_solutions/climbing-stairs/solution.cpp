#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Pull DP: look backward to previous steps
    int climbStairs(int n) {
        vector<int> mem(n + 2, 0);
        mem[0] = 1;
        mem[1] = 1;

        for (int i = 2; i <= n; ++i) {
            mem[i] = mem[i - 1] + mem[i - 2];
        }

        return mem[n];
    }

    // Push DP: look forward and distribute ways to reachable steps
    int climbStairsPush(int n) {
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
    cout << "Pull: " << sol.climbStairs(5) << "\n";
    cout << "Push: " << sol.climbStairsPush(5) << "\n";
    return 0;
}
