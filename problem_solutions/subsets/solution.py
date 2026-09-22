from typing import List


class Solution:
    def backtrack(
        self, nums: List[int], index: int, chosen: List[int], subsets: List[List[int]]
    ) -> None:
        if index == len(nums):
            subsets.append(chosen.copy())
            return

        self.backtrack(nums, index + 1, chosen, subsets)

        chosen.append(nums[index])
        self.backtrack(nums, index + 1, chosen, subsets)
        chosen.pop()

    def subsets(self, nums: List[int]) -> List[List[int]]:
        result: List[List[int]] = []
        self.backtrack(nums, 0, [], result)
        return result


if __name__ == "__main__":
    sol = Solution()
    nums = [1, 2, 3]
    print(sol.subsets(nums))
