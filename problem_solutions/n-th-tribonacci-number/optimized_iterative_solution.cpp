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

int main() {
    Solution sol;
    cout << sol.tribonacci(4) << "\n";   // 4
    cout << sol.tribonacci(25) << "\n";  // 1389537
    return 0;
}
