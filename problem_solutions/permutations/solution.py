from typing import List


class Solution:
    def backtrack(
        self,
        nums: List[int],
        used: List[bool],
        chosen: List[int],
        permutations: List[List[int]],
    ) -> None:
        if len(chosen) == len(nums):
            permutations.append(chosen.copy())
            return

        for i in range(len(nums)):
            if used[i]:
                continue

            used[i] = True
            chosen.append(nums[i])
            self.backtrack(nums, used, chosen, permutations)
            chosen.pop()
            used[i] = False

    def permute(self, nums: List[int]) -> List[List[int]]:
        result: List[List[int]] = []
        used = [False] * len(nums)
        self.backtrack(nums, used, [], result)
        return result


if __name__ == "__main__":
    sol = Solution()
    nums = [1, 2, 3]
    print(sol.permute(nums))
