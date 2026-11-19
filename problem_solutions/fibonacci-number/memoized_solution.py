class Solution:
    def fib(self, n: int) -> int:
        memo: dict[int, int] = {}

        def solve(k: int) -> int:
            if k == 0:
                return 0
            if k == 1:
                return 1
            if k in memo:
                return memo[k]

            memo[k] = solve(k - 1) + solve(k - 2)
            return memo[k]

        return solve(n)


def test_solution():
    sol = Solution()
    assert sol.fib(0) == 0
    assert sol.fib(1) == 1
    assert sol.fib(2) == 1
    assert sol.fib(3) == 2
    assert sol.fib(4) == 3


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
