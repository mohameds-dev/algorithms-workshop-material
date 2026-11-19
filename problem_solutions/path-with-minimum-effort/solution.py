import heapq


class Solution:
    def minimumEffortPath(self, heights: list[list[int]]) -> int:
        rows = len(heights)
        cols = len(heights[0])

        inf = float("inf")
        dist = [[inf] * cols for _ in range(rows)]
        dist[0][0] = 0

        pq = [(0, 0, 0)]  # (effort, row, col)
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

        while pq:
            effort, row, col = heapq.heappop(pq)

            if row == rows - 1 and col == cols - 1:
                return effort

            if effort > dist[row][col]:
                continue

            for row_offset, col_offset in directions:
                next_row = row + row_offset
                next_col = col + col_offset

                if 0 <= next_row < rows and 0 <= next_col < cols:
                    edge_effort = abs(heights[row][col] - heights[next_row][next_col])
                    next_effort = max(effort, edge_effort)

                    if next_effort < dist[next_row][next_col]:
                        dist[next_row][next_col] = next_effort
                        heapq.heappush(pq, (next_effort, next_row, next_col))

        return 0


def test_solution():
    sol = Solution()
    # Test case 1: Standard 3x3 grid with bottleneck path
    assert sol.minimumEffortPath([[1, 2, 2], [3, 8, 2], [5, 3, 5]]) == 2
    # Test case 2: Grid with effort 1
    assert sol.minimumEffortPath([[1, 2, 3], [3, 8, 4], [5, 3, 5]]) == 1
    # Test case 3: Flat paths
    assert sol.minimumEffortPath([[1, 2, 1, 1, 1], [1, 2, 1, 2, 1], [1, 2, 1, 2, 1], [1, 2, 1, 2, 1], [1, 1, 1, 2, 1]]) == 0


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
