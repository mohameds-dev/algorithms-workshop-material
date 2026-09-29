from typing import List


class Solution:
    def solveNQueens(self, n: int) -> List[List[str]]:
        board = [["." for _ in range(n)] for _ in range(n)]
        col_reserved = [False for _ in range(n)]
        main_diagonal_reserved = [False for _ in range(2 * n - 1)]
        anti_diagonal_reserved = [False for _ in range(2 * n - 1)]
        answer: List[List[str]] = []

        def is_attacked(row: int, col: int) -> bool:
            main_diagonal_index = row - col + (n - 1)
            anti_diagonal_index = row + col
            return (
                col_reserved[col]
                or main_diagonal_reserved[main_diagonal_index]
                or anti_diagonal_reserved[anti_diagonal_index]
            )

        def backtrack(current_row: int) -> None:
            if current_row == n:
                answer.append(["".join(r) for r in board])
                return

            for col in range(n):
                if not is_attacked(current_row, col):
                    main_diagonal_index = current_row - col + (n - 1)
                    anti_diagonal_index = current_row + col

                    board[current_row][col] = "Q"
                    col_reserved[col] = True
                    main_diagonal_reserved[main_diagonal_index] = True
                    anti_diagonal_reserved[anti_diagonal_index] = True

                    backtrack(current_row + 1)

                    board[current_row][col] = "."
                    col_reserved[col] = False
                    main_diagonal_reserved[main_diagonal_index] = False
                    anti_diagonal_reserved[anti_diagonal_index] = False

        backtrack(0)
        return answer


if __name__ == "__main__":
    sol = Solution()
    for b in sol.solveNQueens(4):
        for r in b:
            print(r)
        print()
