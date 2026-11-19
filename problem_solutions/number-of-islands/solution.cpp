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

    void dfs(int i, int j, vector<vector<char>>& grid, vector<vector<bool>>& visited) {
        visited[i][j] = true;

        for (const auto& [di, dj] : directions) {
            int ni = i + di;
            int nj = j + dj;

            if (inGrid(ni, nj, grid.size(), grid[0].size()) &&
                grid[ni][nj] == '1' &&
                !visited[ni][nj]) {
                dfs(ni, nj, grid, visited);
            }
        }
    }

public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;

        int rows = grid.size();
        int cols = grid[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        int ans = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    dfs(i, j, grid, visited);
                    ans++;
                }
            }
        }

        return ans;
    }
};

void test_solution() {
    Solution sol;
    vector<vector<char>> grid1 = {
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}
    };
    assert(sol.numIslands(grid1) == 1);

    vector<vector<char>> grid2 = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}
    };
    assert(sol.numIslands(grid2) == 3);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
