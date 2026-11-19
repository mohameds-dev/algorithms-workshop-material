from typing import List


class Solution:
    def uniquePathsWithObstacles(self, obstacleGrid: List[List[int]]) -> int:
        if not obstacleGrid or obstacleGrid[0][0] == 1:
            return 0

        m = len(obstacleGrid)
        n = len(obstacleGrid[0])
        dp = [0] * n
        dp[0] = 1

        for row in range(m):
            for col in range(n):
                if obstacleGrid[row][col] == 1:
                    dp[col] = 0
                elif col > 0:
                    dp[col] += dp[col - 1]

        return dp[-1]


def test_solution():
    sol = Solution()
    assert sol.uniquePathsWithObstacles([[0, 0, 0], [0, 1, 0], [0, 0, 0]]) == 2
    assert sol.uniquePathsWithObstacles([[0, 1], [0, 0]]) == 1


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
