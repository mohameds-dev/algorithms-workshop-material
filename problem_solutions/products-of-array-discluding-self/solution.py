from typing import List


class Solution:
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        n = len(nums)
        product = 1
        prefix = [0] * n
        for i in range(n):
            product *= nums[i]
            prefix[i] = product

        product = 1
        suffix = [0] * n
        for i in range(n - 1, -1, -1):
            product *= nums[i]
            suffix[i] = product

        answer = [0] * n
        for i in range(n):
            answer[i] = (
                prefix[i - 1] * suffix[i + 1]
                if 0 < i < n - 1
                else suffix[i + 1] if i == 0 else prefix[i - 1]
            )

        return answer


if __name__ == "__main__":
    sol = Solution()
    print(sol.productExceptSelf([1, 2, 3, 4]))  # [24, 12, 8, 6]
    print(sol.productExceptSelf([-1, 1, 0, -3, 3]))  # [0, 0, 9, 0, 0]
