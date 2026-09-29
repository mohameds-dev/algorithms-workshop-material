from typing import List


class Solution:
    def solveNQueens(self, n: int) -> List[List[str]]:
        board = [["." for _ in range(n)] for _ in range(n)]
        col_reserved = [False for _ in range(n)]
        answer: List[List[str]] = []

        def queen_in_diagonal(row: int, col: int) -> bool:
            # Only need to check previous rows
            directions = (
                (-1, -1),
                (-1, +1),
            )
            for d_row, d_col in directions:
                new_row, new_col = row + d_row, col + d_col
                while new_row >= 0 and 0 <= new_col < n:
                    if board[new_row][new_col] == "Q":
                        return True
                    new_row += d_row
                    new_col += d_col
            return False

        def is_attacked(row: int, col: int) -> bool:
            return col_reserved[col] or queen_in_diagonal(row, col)

        def backtrack(current_row: int) -> None:
            if current_row == n:
                answer.append(["".join(r) for r in board])
                return

            for col in range(n):
                if not is_attacked(current_row, col):
                    board[current_row][col] = "Q"
                    col_reserved[col] = True

                    backtrack(current_row + 1)

                    col_reserved[col] = False
                    board[current_row][col] = "."

        backtrack(0)
        return answer


if __name__ == "__main__":
    sol = Solution()
    for b in sol.solveNQueens(4):
        for r in b:
            print(r)
        print()