class Solution:
    def fib(self, n: int) -> int:
        memo: dict[int, int] = {}

        def helper(k: int) -> int:
            if k == 0:
                return 0
            if k == 1:
                return 1
            if k in memo:
                return memo[k]

            memo[k] = helper(k - 1) + helper(k - 2)
            return memo[k]

        return helper(n)


if __name__ == "__main__":
    sol = Solution()
    n = 7
    print(sol.fib(n))
