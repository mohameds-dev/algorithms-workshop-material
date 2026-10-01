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


if __name__ == "__main__":
    sol = Solution()
    print(sol.tribonacci(4))  # 4
    print(sol.tribonacci(25))  # 1389537
