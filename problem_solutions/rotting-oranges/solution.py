from collections import deque
from typing import List


class Solution:
    def orangesRotting(self, grid: List[List[int]]) -> int:
        n, m = len(grid), len(grid[0])
        in_bounds = lambda i, j: i >= 0 and j >= 0 and i < n and j < m
        minute_rotten = [[float("inf") for _ in range(m)] for _ in range(n)]
        dirs = ((-1, 0), (+1, 0), (0, +1), (0, -1))
        q = deque()

        for i in range(n):
            for j in range(m):
                if grid[i][j] == 2:
                    minute_rotten[i][j] = 0
                    q.append((i, j))

        while q:
            i, j = q.popleft()
            rotten = minute_rotten[i][j]

            for di, dj in dirs:
                ni, nj = i + di, j + dj
                if (
                    in_bounds(ni, nj)
                    and grid[ni][nj] == 1
                    and minute_rotten[ni][nj] == float("inf")
                ):
                    minute_rotten[ni][nj] = rotten + 1
                    q.append((ni, nj))

        max_minutes = 0
        for i in range(n):
            for j in range(m):
                if grid[i][j] == 1:
                    if minute_rotten[i][j] == float("inf"):
                        return -1
                    max_minutes = max(max_minutes, minute_rotten[i][j])

        return max_minutes


def test_solution():
    sol = Solution()
    assert sol.orangesRotting([[2, 1, 1], [1, 1, 0], [0, 1, 1]]) == 4
    assert sol.orangesRotting([[2, 1, 1], [0, 1, 1], [1, 0, 1]]) == -1
    assert sol.orangesRotting([[0, 2]]) == 0


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
