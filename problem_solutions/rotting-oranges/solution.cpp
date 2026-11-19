#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        const int INF = 1e9;
        vector<vector<int>> minute_rotten(n, vector<int>(m, INF));
        queue<pair<int, int>> q;

        vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 2) {
                    minute_rotten[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        while (!q.empty()) {
            auto [i, j] = q.front();
            q.pop();
            int rotten = minute_rotten[i][j];

            for (const auto& [di, dj] : dirs) {
                int ni = i + di;
                int nj = j + dj;

                if (ni >= 0 && ni < n && nj >= 0 && nj < m &&
                    grid[ni][nj] == 1 &&
                    minute_rotten[ni][nj] == INF) {
                    minute_rotten[ni][nj] = rotten + 1;
                    q.push({ni, nj});
                }
            }
        }

        int max_minutes = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1) {
                    if (minute_rotten[i][j] == INF) {
                        return -1;
                    }
                    max_minutes = max(max_minutes, minute_rotten[i][j]);
                }
            }
        }

        return max_minutes;
    }
};

void test_solution() {
    Solution sol;
    vector<vector<int>> grid1 = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
    assert(sol.orangesRotting(grid1) == 4);

    vector<vector<int>> grid2 = {{2, 1, 1}, {0, 1, 1}, {1, 0, 1}};
    assert(sol.orangesRotting(grid2) == -1);

    vector<vector<int>> grid3 = {{0, 2}};
    assert(sol.orangesRotting(grid3) == 0);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
