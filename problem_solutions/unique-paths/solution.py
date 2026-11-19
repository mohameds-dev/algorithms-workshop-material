class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        dp = [1] * n
        for _ in range(1, m):
            for col in range(1, n):
                dp[col] += dp[col - 1]
        return dp[-1]


def test_solution():
    sol = Solution()
    assert sol.uniquePaths(3, 7) == 28
    assert sol.uniquePaths(3, 2) == 3
    assert sol.uniquePaths(3, 3) == 6


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
