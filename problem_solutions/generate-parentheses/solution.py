from typing import List


class Solution:
    def backtrack(
        self,
        n: int,
        open_count: int,
        close_count: int,
        current: List[str],
        result: List[str],
    ) -> None:
        if len(current) == 2 * n:
            result.append("".join(current))
            return

        if open_count < n:
            current.append("(")
            self.backtrack(n, open_count + 1, close_count, current, result)
            current.pop()

        if close_count < open_count:
            current.append(")")
            self.backtrack(n, open_count, close_count + 1, current, result)
            current.pop()

    def generateParenthesis(self, n: int) -> List[str]:
        result: List[str] = []
        self.backtrack(n, 0, 0, [], result)
        return result


if __name__ == "__main__":
    sol = Solution()
    print(sol.generateParenthesis(1))
    print(sol.generateParenthesis(2))
    print(sol.generateParenthesis(3))
