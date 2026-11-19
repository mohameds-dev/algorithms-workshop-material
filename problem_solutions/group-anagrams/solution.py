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


def test_solution():
    sol = Solution()
    out = [sorted(g) for g in sol.groupAnagrams(["eat", "tea", "tan", "ate", "nat", "bat"])]
    out.sort()
    expected = [["ate", "eat", "tea"], ["bat"], ["nat", "tan"]]
    expected.sort()
    assert out == expected
    assert sol.groupAnagrams([""]) == [[""]]
    assert sol.groupAnagrams(["a"]) == [["a"]]


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
