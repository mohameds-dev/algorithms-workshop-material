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
                    and minute_rotten[ni][nj] > rotten
                ):
                    minute_rotten[ni][nj] = rotten + 1
                    q.append((ni, nj))

        latest_rot_time = 0
        for i in range(n):
            for j in range(m):
                if grid[i][j] == 1:
                    latest_rot_time = max(latest_rot_time, minute_rotten[i][j])

        return -1 if latest_rot_time == float("inf") else latest_rot_time


if __name__ == "__main__":
    sol = Solution()
    grid1 = [
        [2, 1, 1],
        [1, 1, 0],
        [0, 1, 1],
    ]
    print(sol.orangesRotting(grid1))  # 4

    grid2 = [
        [2, 1, 1],
        [0, 1, 1],
        [1, 0, 1],
    ]
    print(sol.orangesRotting(grid2))  # -1

    grid3 = [[0, 2]]
    print(sol.orangesRotting(grid3))  # 0
