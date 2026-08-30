class Solution:
    def fib(self, n: int) -> int:
        # LeetCode constrains n to 0..30
        fib_vals = [0] * 31

        # equivalent to the base case in the recursive solution
        fib_vals[0] = 0
        fib_vals[1] = 1

        for i in range(2, n + 1):
            # transition
            fib_vals[i] = fib_vals[i - 1] + fib_vals[i - 2]

        return fib_vals[n]


if __name__ == "__main__":
    sol = Solution()
    n = 7
    print(sol.fib(n))
