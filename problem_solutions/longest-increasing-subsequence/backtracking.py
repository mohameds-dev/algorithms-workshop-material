class Solution:
    def lengthOfLIS(self, nums: list[int]) -> int:
        n = len(nums)

        def solve(index: int, prev_index: int) -> int:
            if index == n:
                return 0

            # Option 1: Leave nums[index]
            length = solve(index + 1, prev_index)

            # Option 2: Take nums[index] if it is strictly greater than nums[prev_index]
            if prev_index == -1 or nums[index] > nums[prev_index]:
                length = max(length, 1 + solve(index + 1, index))

            return length

        return solve(0, -1)
