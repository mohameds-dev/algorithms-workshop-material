#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
private:
    vector<vector<string>> answer;
    vector<bool> col_reserved;
    vector<bool> main_diagonal_reserved;
    vector<bool> anti_diagonal_reserved;

    bool is_attacked(int row, int col, int n) {
        int main_diagonal_index = row - col + (n - 1);
        int anti_diagonal_index = row + col;
        return col_reserved[col] ||
               main_diagonal_reserved[main_diagonal_index] ||
               anti_diagonal_reserved[anti_diagonal_index];
    }

    void backtrack(int row, int n, vector<string> &board) {
        if (row == n) {
            answer.push_back(board);
            return;
        }

        for (int col = 0; col < n; ++col) {
            if (is_attacked(row, col, n)) {
                continue;
            }

            int main_diagonal_index = row - col + (n - 1);
            int anti_diagonal_index = row + col;

            board[row][col] = 'Q';
            col_reserved[col] = true;
            main_diagonal_reserved[main_diagonal_index] = true;
            anti_diagonal_reserved[anti_diagonal_index] = true;

            backtrack(row + 1, n, board);

            board[row][col] = '.';
            col_reserved[col] = false;
            main_diagonal_reserved[main_diagonal_index] = false;
            anti_diagonal_reserved[anti_diagonal_index] = false;
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        answer.clear();
        col_reserved.assign(n, false);
        main_diagonal_reserved.assign(2 * n - 1, false);
        anti_diagonal_reserved.assign(2 * n - 1, false);

        vector<string> board(n, string(n, '.'));
        backtrack(0, n, board);
        return answer;
    }
};

void test_solution() {
    Solution sol;
    assert(sol.solveNQueens(4).size() == 2);
    vector<vector<string>> expected1 = {{"Q"}};
    assert(sol.solveNQueens(1) == expected1);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
