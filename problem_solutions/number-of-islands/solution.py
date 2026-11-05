from typing import List


class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
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

            for di, dj in directions:
                ni = i + di
                nj = j + dj
                if in_grid(ni, nj) and grid[ni][nj] == "1" and (ni, nj) not in visited:
                    dfs(ni, nj)

        islands_counter = 0
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] == "1" and (i, j) not in visited:
                    islands_counter += 1
                    dfs(i, j)

        return islands_counter


if __name__ == "__main__":
    sol = Solution()
    grid1 = [
        ["1", "1", "1", "1", "0"],
        ["1", "1", "0", "1", "0"],
        ["1", "1", "0", "0", "0"],
        ["0", "0", "0", "0", "0"],
    ]
    print(sol.numIslands(grid1))  # 1

    grid2 = [
        ["1", "1", "0", "0", "0"],
        ["1", "1", "0", "0", "0"],
        ["0", "0", "1", "0", "0"],
        ["0", "0", "0", "1", "1"],
    ]
    print(sol.numIslands(grid2))  # 3
