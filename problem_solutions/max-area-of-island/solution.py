from typing import List


class Solution:
    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        directions = (
            (-1, 0),
            (+1, 0),
            (0, -1),
            (0, +1),
        )

        visited = set()

        def in_grid(i, j):
            return i >= 0 and i < len(grid) and j >= 0 and j < len(grid[0])

        def dfs(i, j):
            visited.add((i, j))
            nbrs = [(i + di, j + dj) for di, dj in directions]

            return 1 + sum(
                dfs(ni, nj)
                for ni, nj in nbrs
                if in_grid(ni, nj) and grid[ni][nj] == 1 and (ni, nj) not in visited
            )

        max_area = 0
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] == 1 and (i, j) not in visited:
                    area = dfs(i, j)
                    max_area = max(max_area, area)

        return max_area


if __name__ == "__main__":
    sol = Solution()
    grid1 = [
        [0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0],
        [0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0],
        [0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0],
    ]
    print(sol.maxAreaOfIsland(grid1))  # 6

    grid2 = [[0, 0, 0, 0, 0, 0, 0, 0]]
    print(sol.maxAreaOfIsland(grid2))  # 0
