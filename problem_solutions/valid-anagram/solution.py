class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        if len(s) != len(t):
            return False

        counts = [0] * 26
        for char_s, char_t in zip(s, t):
            counts[ord(char_s) - ord("a")] += 1
            counts[ord(char_t) - ord("a")] -= 1

        return all(count == 0 for count in counts)


def test_solution():
    sol = Solution()
    assert sol.isAnagram("anagram", "nagaram") is True
    assert sol.isAnagram("rat", "car") is False


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
