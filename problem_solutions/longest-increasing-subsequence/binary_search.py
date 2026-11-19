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


def test_solution():
    sol = Solution()
    assert sol.lengthOfLIS([10, 9, 2, 5, 3, 7, 101, 18]) == 4
    assert sol.lengthOfLIS([0, 1, 0, 3, 2, 3]) == 4
    assert sol.lengthOfLIS([7, 7, 7, 7, 7, 7, 7]) == 1


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
