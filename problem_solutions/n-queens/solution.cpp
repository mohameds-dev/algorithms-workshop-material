#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int n;
    vector<string> board;
    vector<bool> col_reserved;
    vector<bool> main_diagonal_reserved;
    vector<bool> anti_diagonal_reserved;
    vector<vector<string>> answer;

    void initialize_fields(int board_size) {
        n = board_size;
        board = vector<string>(n, string(n, '.'));
        col_reserved = vector<bool>(n, false);
        main_diagonal_reserved = vector<bool>(2 * n - 1, false);
        anti_diagonal_reserved = vector<bool>(2 * n - 1, false);
        answer.clear();
    }

    bool is_attacked(int row, int col) {
        int main_diagonal_index = row - col + (n - 1);
        int anti_diagonal_index = row + col;
        return col_reserved[col] ||
               main_diagonal_reserved[main_diagonal_index] ||
               anti_diagonal_reserved[anti_diagonal_index];
    }

    void backtrack(int current_row) {
        if (current_row == n) {
            answer.push_back(board);
            return;
        }

        for (int col = 0; col < n; col++) {
            if (!is_attacked(current_row, col)) {
                int main_diagonal_index = current_row - col + (n - 1);
                int anti_diagonal_index = current_row + col;

                board[current_row][col] = 'Q';
                col_reserved[col] = true;
                main_diagonal_reserved[main_diagonal_index] = true;
                anti_diagonal_reserved[anti_diagonal_index] = true;

                backtrack(current_row + 1);

                board[current_row][col] = '.';
                col_reserved[col] = false;
                main_diagonal_reserved[main_diagonal_index] = false;
                anti_diagonal_reserved[anti_diagonal_index] = false;
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        initialize_fields(n);
        backtrack(0);
        return answer;
    }
};

int main() {
    Solution sol;
    auto answer = sol.solveNQueens(4);
    for (const auto &board : answer) {
        for (const auto &row : board) {
            cout << row << "\n";
        }
        cout << "\n";
    }
    return 0;
}
