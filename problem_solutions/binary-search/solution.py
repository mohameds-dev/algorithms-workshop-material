from typing import List


class Solution:
    def search_recursive(self, nums: List[int], target: int, left: int, right: int) -> int:
        if left > right:
            return -1

        if left == right:
            return left if nums[left] == target else -1

        mid = (left + right) // 2
        if target >= nums[left] and target <= nums[mid]:
            return self.search_recursive(nums, target, left, mid)

        return self.search_recursive(nums, target, mid + 1, right)

    def search(self, nums: List[int], target: int) -> int:
        return self.search_recursive(nums, target, 0, len(nums) - 1)


if __name__ == "__main__":
    sol = Solution()
    nums = [-1, 0, 3, 5, 9, 12]
    target = 9
    print(sol.search(nums, target))
