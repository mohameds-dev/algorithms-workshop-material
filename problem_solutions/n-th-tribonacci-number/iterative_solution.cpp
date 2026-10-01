#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int tribonacci(int n) {
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

int main() {
    Solution sol;
    cout << sol.tribonacci(4) << "\n";   // 4
    cout << sol.tribonacci(25) << "\n";  // 1389537
    return 0;
}
