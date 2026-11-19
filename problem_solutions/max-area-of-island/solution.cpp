#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    vector<pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };

    bool inGrid(int i, int j, int rows, int cols) {
        return i >= 0 && i < rows && j >= 0 && j < cols;
    }

    int dfs(int i, int j, vector<vector<int>>& grid, vector<vector<bool>>& visited) {
        visited[i][j] = true;
        int area = 1;

        for (const auto& [di, dj] : directions) {
            int ni = i + di;
            int nj = j + dj;

            if (inGrid(ni, nj, grid.size(), grid[0].size()) &&
                grid[ni][nj] == 1 &&
                !visited[ni][nj]) {
                area += dfs(ni, nj, grid, visited);
            }
        }

        return area;
    }

public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        if (grid.empty()) return 0;

        int rows = grid.size();
        int cols = grid[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        int max_area = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    max_area = max(max_area, dfs(i, j, grid, visited));
                }
            }
        }

        return max_area;
    }
};

void test_solution() {
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
    assert(sol.maxAreaOfIsland(grid1) == 6);
    vector<vector<int>> grid2 = {{0, 0, 0, 0, 0, 0, 0, 0}};
    assert(sol.maxAreaOfIsland(grid2) == 0);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
