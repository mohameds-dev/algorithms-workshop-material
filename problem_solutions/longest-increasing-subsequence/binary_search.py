from bisect import bisect_left


class Solution:
    def lengthOfLIS(self, nums: list[int]) -> int:
        tails: list[int] = []

        for x in nums:
            index = bisect_left(tails, x)
            if index == len(tails):
                tails.append(x)
            else:
                tails[index] = x

        return len(tails)
