#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Cell {
    int effort;
    int row;
    int col;

    // Custom comparator for min-heap: smaller effort pops first
    bool operator<(const Cell& other) const {
        return effort > other.effort;
    }
};

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int rows = heights.size();
        int cols = heights[0].size();

        const int INF = 1e9;
        vector<vector<int>> dist(rows, vector<int>(cols, INF));
        priority_queue<Cell> pq;

        dist[0][0] = 0;
        pq.push({0, 0, 0});

        const int row_offsets[4] = {-1, 1, 0, 0};
        const int col_offsets[4] = {0, 0, -1, 1};

        while (!pq.empty()) {
            auto [effort, row, col] = pq.top();
            pq.pop();

            if (row == rows - 1 && col == cols - 1) {
                return effort;
            }

            if (effort > dist[row][col]) {
                continue;
            }

            for (int dir = 0; dir < 4; ++dir) {
                int next_row = row + row_offsets[dir];
                int next_col = col + col_offsets[dir];

                if (next_row >= 0 && next_row < rows && next_col >= 0 && next_col < cols) {
                    int edge_effort = abs(heights[row][col] - heights[next_row][next_col]);
                    int next_effort = max(effort, edge_effort);

                    if (next_effort < dist[next_row][next_col]) {
                        dist[next_row][next_col] = next_effort;
                        pq.push({next_effort, next_row, next_col});
                    }
                }
            }
        }

        return 0;
    }
};

void test_solution() {
    Solution sol;
    // Test case 1: Standard 3x3 grid with bottleneck path
    vector<vector<int>> heights1 = {{1, 2, 2}, {3, 8, 2}, {5, 3, 5}};
    assert(sol.minimumEffortPath(heights1) == 2);

    // Test case 2: Grid with effort 1
    vector<vector<int>> heights2 = {{1, 2, 3}, {3, 8, 4}, {5, 3, 5}};
    assert(sol.minimumEffortPath(heights2) == 1);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
