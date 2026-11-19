class Solution:
    def tribonacci(self, n: int) -> int:
        if n <= 1:
            return n

        a0 = 0
        a1 = 1
        a2 = 1

        for i in range(3, n + 1):
            a0, a1, a2 = a1, a2, a0 + a1 + a2

        return a2


def test_solution():
    sol = Solution()
    assert sol.tribonacci(4) == 4
    assert sol.tribonacci(25) == 1389537


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
