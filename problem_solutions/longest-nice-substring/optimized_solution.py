class Solution:
    def solve(self, s: str) -> str:
        # one pass to remember every character in s, so the checks below cost O(1) each
        chars_in_s = set(s)

        for i in range(len(s)):
            if s[i].upper() not in chars_in_s or s[i].lower() not in chars_in_s:
                left = self.solve(s[0:i])
                right = self.solve(s[i + 1:len(s)])

                return right if len(left) < len(right) else left

        return s

    def longestNiceSubstring(self, s: str) -> str:
        return self.solve(s)


if __name__ == "__main__":
    sol = Solution()
    s = "YazaAay"
    print(sol.longestNiceSubstring(s))
