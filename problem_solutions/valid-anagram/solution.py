class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        if len(s) != len(t):
            return False

        counts = [0] * 26
        for char_s, char_t in zip(s, t):
            counts[ord(char_s) - ord("a")] += 1
            counts[ord(char_t) - ord("a")] -= 1

        return all(count == 0 for count in counts)


if __name__ == "__main__":
    sol = Solution()
    print(sol.isAnagram("anagram", "nagaram"))  # True
    print(sol.isAnagram("rat", "car"))          # False
