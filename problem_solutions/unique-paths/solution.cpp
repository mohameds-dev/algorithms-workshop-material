#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);
        for (int row = 1; row < m; row++) {
            for (int col = 1; col < n; col++) {
                dp[col] += dp[col - 1];
            }
        }
        return dp[n - 1];
    }
};

int main() {
    Solution sol;
    cout << sol.uniquePaths(3, 7) << endl; // 28
    cout << sol.uniquePaths(3, 2) << endl; // 3
    cout << sol.uniquePaths(3, 3) << endl; // 6
    return 0;
}
