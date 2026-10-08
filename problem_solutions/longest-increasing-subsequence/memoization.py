class Solution:
    def lengthOfLIS(self, nums: list[int]) -> int:
        n = len(nums)
        memo = [[-1] * (n + 1) for _ in range(n)]

        def solve(index: int, prev_index: int) -> int:
            if index == n:
                return 0

            if memo[index][prev_index + 1] != -1:
                return memo[index][prev_index + 1]

            length = solve(index + 1, prev_index)
            if prev_index == -1 or nums[index] > nums[prev_index]:
                length = max(length, 1 + solve(index + 1, index))

            memo[index][prev_index + 1] = length
            return length

        return solve(0, -1)
