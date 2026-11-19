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


def test_solution():
    sol = Solution()
    res = sol.subsets([1, 2, 3])
    assert len(res) == 8
    assert [] in res
    assert [1, 2, 3] in res
    res_single = sol.subsets([0])
    assert len(res_single) == 2


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
