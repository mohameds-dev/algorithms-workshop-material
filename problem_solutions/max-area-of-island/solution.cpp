#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    const vector<pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };

    bool inGrid(int i, int j, int rows, int cols) {
        return i >= 0 && i < rows && j >= 0 && j < cols;
    }

    int dfs(int i, int j, const vector<vector<int>>& grid, vector<vector<bool>>& visited) {
        visited[i][j] = true;
        int area = 1;
        int rows = grid.size();
        int cols = grid[0].size();

        for (const auto& [di, dj] : directions) {
            int ni = i + di;
            int nj = j + dj;
            if (inGrid(ni, nj, rows, cols) && grid[ni][nj] == 1 && !visited[ni][nj]) {
                area += dfs(ni, nj, grid, visited);
            }
        }

        return area;
    }

public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        int rows = grid.size();
        int cols = grid[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        int maxArea = 0;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    maxArea = max(maxArea, dfs(i, j, grid, visited));
                }
            }
        }

        return maxArea;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> grid1 = {
        {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}
    };
    cout << sol.maxAreaOfIsland(grid1) << endl; // 6

    vector<vector<int>> grid2 = {{0, 0, 0, 0, 0, 0, 0, 0}};
    cout << sol.maxAreaOfIsland(grid2) << endl; // 0

    return 0;
}
