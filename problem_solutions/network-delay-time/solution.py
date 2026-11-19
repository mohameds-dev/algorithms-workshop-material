import heapq


class Solution:
    def networkDelayTime(
        self, times: list[list[int]], n: int, k: int
    ) -> int:
        num_nodes = n
        source = k

        adj = [[] for _ in range(num_nodes + 1)]
        for src, dst, travel_time in times:
            adj[src].append((dst, travel_time))

        inf = float("inf")
        dist = [inf] * (num_nodes + 1)
        dist[source] = 0

        pq = [(0, source)]

        while pq:
            curr_dist, node = heapq.heappop(pq)

            if curr_dist > dist[node]:
                continue

            for neighbor, travel_time in adj[node]:
                new_dist = curr_dist + travel_time
                if new_dist < dist[neighbor]:
                    dist[neighbor] = new_dist
                    heapq.heappush(pq, (new_dist, neighbor))

        max_time = max(dist[1 : num_nodes + 1])
        return max_time if max_time < inf else -1
