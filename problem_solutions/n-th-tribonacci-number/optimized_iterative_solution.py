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


if __name__ == "__main__":
    sol = Solution()
    print(sol.tribonacci(4))  # 4
    print(sol.tribonacci(25))  # 1389537
