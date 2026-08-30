class Solution:
    def fib(self, n: int) -> int:
        # base case
        if n == 0:
            return 0
        if n == 1:
            return 1

        # transition
        return self.fib(n - 1) + self.fib(n - 2)


if __name__ == "__main__":
    sol = Solution()
    n = 7
    print(sol.fib(n))
