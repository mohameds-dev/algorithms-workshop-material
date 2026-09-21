#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findRow(vector<vector<int>> &matrix, int target) {
        int left = 0, right = (int)matrix.size() - 1;
        int row = -1;

        while (left <= right) {
            int mid = (left + right) / 2;
            if (matrix[mid][0] <= target) {
                row = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return row;
    }

    int searchRow(vector<int> &row, int target) {
        int left = 0, right = (int)row.size() - 1;

        while (left <= right) {
            int mid = (left + right) / 2;
            if (row[mid] == target) return mid;
            else if (row[mid] < target) left = mid + 1;
            else right = mid - 1;
        }

        return -1;
    }

    bool searchMatrix(vector<vector<int>> &matrix, int target) {
        int row = findRow(matrix, target);
        if (row == -1) return false;

        return searchRow(matrix[row], target) != -1;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    int target = 3;
    cout << (sol.searchMatrix(matrix, target) ? "true" : "false") << endl;

    return 0;
}
