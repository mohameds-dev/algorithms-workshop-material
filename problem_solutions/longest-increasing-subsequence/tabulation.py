class Solution:
    def lengthOfLIS(self, nums: list[int]) -> int:
        if not nums:
            return 0

        lis = [1 for _ in nums]
        n = len(nums)

        for i in range(n):
            for j in range(i):
                if nums[i] > nums[j]:
                    lis[i] = max(lis[i], lis[j] + 1)

        return max(lis)


def test_solution():
    sol = Solution()
    assert sol.lengthOfLIS([10, 9, 2, 5, 3, 7, 101, 18]) == 4
    assert sol.lengthOfLIS([0, 1, 0, 3, 2, 3]) == 4
    assert sol.lengthOfLIS([7, 7, 7, 7, 7, 7, 7]) == 1


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
