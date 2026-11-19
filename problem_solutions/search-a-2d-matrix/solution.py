from typing import List


class Solution:
    def find_row(self, matrix: List[List[int]], target: int) -> int:
        left, right = 0, len(matrix) - 1
        row = -1

        while left <= right:
            mid = (left + right) // 2
            if matrix[mid][0] <= target:
                row = mid
                left = mid + 1
            else:
                right = mid - 1

        return row

    def search_row(self, row: List[int], target: int) -> int:
        left, right = 0, len(row) - 1

        while left <= right:
            mid = (left + right) // 2
            if row[mid] == target:
                return mid
            elif row[mid] < target:
                left = mid + 1
            else:
                right = mid - 1

        return -1

    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        row = self.find_row(matrix, target)
        if row == -1:
            return False

        return self.search_row(matrix[row], target) != -1


def test_solution():
    sol = Solution()
    matrix = [[1, 3, 5, 7], [10, 11, 16, 20], [23, 30, 34, 60]]
    assert sol.searchMatrix(matrix, 3) is True
    assert sol.searchMatrix(matrix, 13) is False


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
