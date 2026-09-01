class Solution:
    def char_exists_in_both_cases(self, c: str, s: str) -> bool:
        return c.upper() in s and c.lower() in s

    def solve(self, s: str) -> str:
        if len(s) == 0:
            return ""

        n = len(s)
        for i in range(n):
            if not self.char_exists_in_both_cases(s[i], s):
                # splitting around i

                # solve from 0 to i - 1
                left = self.solve(s[0:i])
                # solve from i + 1 to end
                right = self.solve(s[i + 1:n])

                return right if len(left) < len(right) else left

        return s

    def longestNiceSubstring(self, s: str) -> str:
        return self.solve(s)


if __name__ == "__main__":
    sol = Solution()
    s = "YazaAay"
    print(sol.longestNiceSubstring(s))
