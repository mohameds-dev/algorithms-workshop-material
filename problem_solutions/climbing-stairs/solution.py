class Solution:
    def climbStairs(self, n: int) -> int:
        # Pull DP: look backward to previous steps
        mem = [0 for _ in range(n + 2)]
        mem[0] = 1
        mem[1] = 1

        for i in range(2, n + 1):
            mem[i] = mem[i - 1] + mem[i - 2]

        return mem[n]

    def climbStairsPush(self, n: int) -> int:
        # Push DP: look forward and distribute ways to reachable steps
        mem = [0 for _ in range(n + 2)]
        mem[0] = 1

        for i in range(0, n):
            mem[i + 1] += mem[i]
            mem[i + 2] += mem[i]

        return mem[n]


if __name__ == "__main__":
    sol = Solution()
    print("Pull:", sol.climbStairs(5))
    print("Push:", sol.climbStairsPush(5))
