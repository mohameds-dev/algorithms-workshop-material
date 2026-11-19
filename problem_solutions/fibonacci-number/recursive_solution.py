class Solution:
    def fib(self, n: int) -> int:
        # base case
        if n == 0:
            return 0
        if n == 1:
            return 1

        # transition
        return self.fib(n - 1) + self.fib(n - 2)


def test_solution():
    sol = Solution()
    assert sol.fib(0) == 0
    assert sol.fib(1) == 1
    assert sol.fib(2) == 1
    assert sol.fib(3) == 2
    assert sol.fib(4) == 3


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
