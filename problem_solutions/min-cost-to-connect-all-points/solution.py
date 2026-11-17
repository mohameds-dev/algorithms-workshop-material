class Solution:
    def minCostConnectPoints(self, points: list[list[int]]) -> int:
        n = len(points)
        min_dist = [float("inf")] * n
        min_dist[0] = 0
        in_mst = [False] * n
        total_cost = 0

        for _ in range(n):
            u = -1
            for i in range(n):
                if not in_mst[i] and (u == -1 or min_dist[i] < min_dist[u]):
                    u = i

            in_mst[u] = True
            total_cost += min_dist[u]

            ux, uy = points[u]
            for v in range(n):
                if not in_mst[v]:
                    vx, vy = points[v]
                    dist = abs(ux - vx) + abs(uy - vy)
                    if dist < min_dist[v]:
                        min_dist[v] = dist

        return total_cost
