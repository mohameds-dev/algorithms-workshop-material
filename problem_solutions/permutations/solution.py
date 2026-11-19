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


def test_solution():
    sol = Solution()
    res = sol.permute([1, 2, 3])
    assert len(res) == 6
    assert [1, 2, 3] in res
    assert [3, 2, 1] in res
    assert sol.permute([1]) == [[1]]


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
