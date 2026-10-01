class Solution:
    def tribonacci(self, n: int) -> int:
        if n <= 1:
            return n

        trib = [-1 for _ in range(n + 1)]
        trib[0] = 0
        trib[1] = 1
        trib[2] = 1

        for i in range(3, n + 1):
            trib[i] = trib[i - 1] + trib[i - 2] + trib[i - 3]

        return trib[n]


if __name__ == "__main__":
    sol = Solution()
    print(sol.tribonacci(4))  # 4
    print(sol.tribonacci(25))  # 1389537
