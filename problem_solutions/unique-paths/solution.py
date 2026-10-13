class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        dp = [1] * n
        for _ in range(1, m):
            for col in range(1, n):
                dp[col] += dp[col - 1]
        return dp[-1]


if __name__ == "__main__":
    sol = Solution()
    print(sol.uniquePaths(3, 7))  # 28
    print(sol.uniquePaths(3, 2))  # 3
    print(sol.uniquePaths(3, 3))  # 6
