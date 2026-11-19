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
