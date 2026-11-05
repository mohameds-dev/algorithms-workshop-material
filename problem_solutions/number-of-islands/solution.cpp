#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    const vector<pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };

    bool inGrid(int i, int j, int rows, int cols) {
        return i >= 0 && i < rows && j >= 0 && j < cols;
    }

    void dfs(int i, int j, const vector<vector<char>>& grid, vector<vector<bool>>& visited) {
        visited[i][j] = true;
        int rows = grid.size();
        int cols = grid[0].size();

        for (const auto& [di, dj] : directions) {
            int ni = i + di;
            int nj = j + dj;
            if (inGrid(ni, nj, rows, cols) && grid[ni][nj] == '1' && !visited[ni][nj]) {
                dfs(ni, nj, grid, visited);
            }
        }
    }

public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        int rows = grid.size();
        int cols = grid[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        int islandsCounter = 0;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    islandsCounter++;
                    dfs(i, j, grid, visited);
                }
            }
        }

        return islandsCounter;
    }
};

int main() {
    Solution sol;
    vector<vector<char>> grid1 = {
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}
    };
    cout << sol.numIslands(grid1) << endl; // 1

    vector<vector<char>> grid2 = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}
    };
    cout << sol.numIslands(grid2) << endl; // 3

    return 0;
}
