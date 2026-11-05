#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
private:
    const vector<pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, 1}, {0, -1}
    };

    bool inBounds(int i, int j, int n, int m) {
        return i >= 0 && j >= 0 && i < n && j < m;
    }

public:
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> minuteRotten(n, vector<int>(m, INT_MAX));
        queue<pair<int, int>> q;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 2) {
                    minuteRotten[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        while (!q.empty()) {
            auto [i, j] = q.front();
            q.pop();
            int rotten = minuteRotten[i][j];

            for (const auto& [di, dj] : directions) {
                int ni = i + di;
                int nj = j + dj;
                if (inBounds(ni, nj, n, m) && grid[ni][nj] == 1 && minuteRotten[ni][nj] > rotten + 1) {
                    minuteRotten[ni][nj] = rotten + 1;
                    q.push({ni, nj});
                }
            }
        }

        int latestRotTime = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1) {
                    latestRotTime = max(latestRotTime, minuteRotten[i][j]);
                }
            }
        }

        return (latestRotTime == INT_MAX) ? -1 : latestRotTime;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> grid1 = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}
    };
    cout << sol.orangesRotting(grid1) << endl; // 4

    vector<vector<int>> grid2 = {
        {2, 1, 1},
        {0, 1, 1},
        {1, 0, 1}
    };
    cout << sol.orangesRotting(grid2) << endl; // -1

    vector<vector<int>> grid3 = {{0, 2}};
    cout << sol.orangesRotting(grid3) << endl; // 0

    return 0;
}
