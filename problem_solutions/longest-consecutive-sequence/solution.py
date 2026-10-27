from typing import List


class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        my_set = set(nums)
        answer = 0
        for num in nums:
            if num - 1 in my_set:
                continue
            i = 1
            while num + i in my_set:
                i += 1
            answer = max(answer, i)
        return answer


if __name__ == "__main__":
    sol = Solution()
    print(sol.longestConsecutive([100, 4, 200, 1, 3, 2]))  # 4
    print(sol.longestConsecutive([0, 3, 7, 2, 5, 8, 4, 6, 0, 1]))  # 9
    print(sol.longestConsecutive([]))  # 0
