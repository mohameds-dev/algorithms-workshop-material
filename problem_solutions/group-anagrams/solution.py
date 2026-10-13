from collections import defaultdict
from typing import List


class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        groups = defaultdict(list)
        for s in strs:
            counts = [0] * 26
            for char in s:
                counts[ord(char) - ord("a")] += 1
            groups[tuple(counts)].append(s)
        return list(groups.values())


if __name__ == "__main__":
    sol = Solution()
    print(sol.groupAnagrams(["eat", "tea", "tan", "ate", "nat", "bat"]))
    print(sol.groupAnagrams([""]))
    print(sol.groupAnagrams(["a"]))
