import heapq


class Solution:
    def networkDelayTime(self, times: list[list[int]], n: int, k: int) -> int:
        INF = 10**18
        adj_list = [list() for _ in range(n + 1)]
        cost_to_reach = [INF for _ in range(n + 1)]

        for a, b, c in times:
            adj_list[a].append((b, c))

        pq = []  # priority queue (min heap)

        # let it sort by cost -> make it (cost, node)
        pq.append((0, k))
        cost_to_reach[k] = 0

        while pq:
            cur_node_cost, cur_node = heapq.heappop(pq)

            if cur_node_cost > cost_to_reach[cur_node]:
                continue

            for node, edge_cost in adj_list[cur_node]:
                new_cost = cur_node_cost + edge_cost

                if new_cost < cost_to_reach[node]:
                    cost_to_reach[node] = new_cost
                    heapq.heappush(pq, (new_cost, node))

        max_cost = max(cost_to_reach[1:])
        return max_cost if max_cost < INF else -1


def test_solution():
    sol = Solution()
    # Test case 1: Standard reachable network
    assert sol.networkDelayTime([[2, 1, 1], [2, 3, 1], [3, 4, 1]], 4, 2) == 2
    # Test case 2: Single directed edge with unreachable destination
    assert sol.networkDelayTime([[1, 2, 1]], 2, 2) == -1
    # Test case 3: Single directed edge reachable
    assert sol.networkDelayTime([[1, 2, 1]], 2, 1) == 1


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
