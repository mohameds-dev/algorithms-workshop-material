class Solution:
    def both_cases_exist(self, c: str, chars_in_s: set[str]) -> bool:
        return c.upper() in chars_in_s and c.lower() in chars_in_s

    def first_single_case_char(self, s: str) -> int:
        # one pass up front, so every check in the loop below is a hash lookup instead of a scan
        chars_in_s = set(s)
        for i, c in enumerate(s):
            if not self.both_cases_exist(c, chars_in_s):
                return i
        return -1

    def split_around_index(self, s: str, i: int) -> tuple[str, str]:
        return s[:i], s[i + 1:]

    def longest_nice_substring(self, s: str) -> str:
        i = self.first_single_case_char(s)
        if i == -1:
            return s

        left, right = self.split_around_index(s, i)
        left_result = self.longest_nice_substring(left)
        right_result = self.longest_nice_substring(right)
        return left_result if len(left_result) >= len(right_result) else right_result

    def longestNiceSubstring(self, s: str) -> str:
        return self.longest_nice_substring(s)


if __name__ == "__main__":
    sol = Solution()
    s = "YazaAay"
    print(sol.longestNiceSubstring(s))
