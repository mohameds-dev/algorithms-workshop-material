class Solution:
    def tribonacci(self, n: int) -> int:
        # Space-optimized bottom-up DP: O(n) time, O(1) space
        if n <= 1:
            return n

        a0 = 0
        a1 = 1
        a2 = 1

        for i in range(3, n + 1):
            a0, a1, a2 = a1, a2, a0 + a1 + a2

        return a2

    def tribonacciTabulation(self, n: int) -> int:
        # Full bottom-up tabulation: O(n) time, O(n) space
        if n <= 1:
            return n

        trib = [-1 for _ in range(n + 1)]
        trib[0] = 0
        trib[1] = 1
        trib[2] = 1

        for i in range(3, n + 1):
            trib[i] = trib[i - 1] + trib[i - 2] + trib[i - 3]

        return trib[n]

    def tribonacciMemo(self, n: int) -> int:
        # Top-down memoization: O(n) time, O(n) space
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
    print("Optimized:", sol.tribonacci(4))
    print("Tabulation:", sol.tribonacciTabulation(4))
    print("Memoization:", sol.tribonacciMemo(4))
