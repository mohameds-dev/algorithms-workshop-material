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

        ans = 0
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] == "1" and (i, j) not in visited:
                    dfs(i, j)
                    ans += 1

        return ans


def test_solution():
    sol = Solution()
    grid1 = [
        ["1", "1", "1", "1", "0"],
        ["1", "1", "0", "1", "0"],
        ["1", "1", "0", "0", "0"],
        ["0", "0", "0", "0", "0"],
    ]
    assert sol.numIslands(grid1) == 1

    grid2 = [
        ["1", "1", "0", "0", "0"],
        ["1", "1", "0", "0", "0"],
        ["0", "0", "1", "0", "0"],
        ["0", "0", "0", "1", "1"],
    ]
    assert sol.numIslands(grid2) == 3


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
