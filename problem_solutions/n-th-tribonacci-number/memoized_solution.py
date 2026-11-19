class Solution:
    def tribonacci(self, n: int) -> int:
        if n <= 1:
            return n

        mem = [-1 for _ in range(n + 1)]

        def solve(num: int) -> int:
            if num <= 2:
                return 1 if num > 0 else 0

            if mem[num] == -1:
                mem[num] = solve(num - 1) + solve(num - 2) + solve(num - 3)

            return mem[num]

        return solve(n)


def test_solution():
    sol = Solution()
    assert sol.tribonacci(4) == 4
    assert sol.tribonacci(25) == 1389537


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
