#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);
        for (int row = 1; row < m; ++row) {
            for (int col = 1; col < n; ++col) {
                dp[col] += dp[col - 1];
            }
        }
        return dp[n - 1];
    }
};

void test_solution() {
    Solution sol;
    assert(sol.uniquePaths(3, 7) == 28);
    assert(sol.uniquePaths(3, 2) == 3);
    assert(sol.uniquePaths(3, 3) == 6);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
