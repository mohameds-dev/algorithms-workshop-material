from typing import List


class Solution:
    def solveNQueens(self, n: int) -> List[List[str]]:
        board = [["." for _ in range(n)] for _ in range(n)]
        column_attacked = [False for _ in range(n)]

        answer = []

        def is_attacked(row: int, col: int) -> bool:
            if column_attacked[col]:
                return True

            steps = 1
            while row - steps >= 0 and col - steps >= 0:
                if board[row - steps][col - steps] == 'Q':
                    return True
                steps += 1

            steps = 1
            while row - steps >= 0 and col + steps < n:
                if board[row - steps][col + steps] == 'Q':
                    return True
                steps += 1
            

            return False

        def backtrack(current_row):
            if current_row == n:
                answer.append(["".join(row) for row in board])
                return

            for column in range(n):
                if not is_attacked(current_row, column):
                    board[current_row][column] = 'Q'
                    column_attacked[column] = True

                    backtrack(current_row + 1)

                    board[current_row][column] = '.'
                    column_attacked[column] = False

        backtrack(0)
        return answer

