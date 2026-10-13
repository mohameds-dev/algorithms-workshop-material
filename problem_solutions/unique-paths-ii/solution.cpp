#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
        if (obstacleGrid.empty() || obstacleGrid[0][0] == 1) {
            return 0;
        }

        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        vector<long long> dp(n, 0);
        dp[0] = 1;

        for (int row = 0; row < m; row++) {
            for (int col = 0; col < n; col++) {
                if (obstacleGrid[row][col] == 1) {
                    dp[col] = 0;
                } else if (col > 0) {
                    dp[col] += dp[col - 1];
                }
            }
        }

        return dp[n - 1];
    }
};

int main() {
    Solution sol;
    vector<vector<int>> grid1 = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    cout << sol.uniquePathsWithObstacles(grid1) << endl; // 2

    vector<vector<int>> grid2 = {{0, 1}, {0, 0}};
    cout << sol.uniquePathsWithObstacles(grid2) << endl; // 1

    vector<vector<int>> grid3 = {{1}};
    cout << sol.uniquePathsWithObstacles(grid3) << endl; // 0
    return 0;
}
