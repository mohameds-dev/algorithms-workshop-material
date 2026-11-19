import heapq
import sys


def dijkstra(n: int, adj_list: list[list[tuple[int, int]]], source: int = 1) -> list[int]:
    cost_to_reach = [float("inf") for _ in range(n + 1)]
    pq = []  # priority queue (min heap)

    # city 1 is Syrjälä -> we get to the source with cost = 0
    # let it sort by cost -> make it (cost, node)
    pq.append((0, source))
    cost_to_reach[source] = 0

    while pq:
        cur_node_cost, cur_node = heapq.heappop(pq)

        if cur_node_cost > cost_to_reach[cur_node]:
            continue

        for node, edge_cost in adj_list[cur_node]:
            new_cost = cur_node_cost + edge_cost

            if new_cost < cost_to_reach[node]:
                cost_to_reach[node] = new_cost
                heapq.heappush(pq, (new_cost, node))

    return cost_to_reach


def main():
    input = sys.stdin.readline  # to avoid TLE on CSES
    n, m = map(int, input().split())

    adj_list = [list() for _ in range(n + 1)]
    # for each node of n nodes -> list of edges
    # each edge is a tuple -> (node, cost)
    for _ in range(m):
        a, b, c = map(int, input().split())
        adj_list[a].append((b, c))

    cost_to_reach = dijkstra(n, adj_list, source=1)
    for i in range(1, n + 1):
        print(cost_to_reach[i], end=" ")


def test_solution():
    # CSES 1671 sample test case:
    # 3 cities, 3 flights: 1->2 (cost 6), 1->3 (cost 2), 3->2 (cost 1)
    n = 3
    adj_list = [list() for _ in range(n + 1)]
    adj_list[1].append((2, 6))
    adj_list[1].append((3, 2))
    adj_list[3].append((2, 1))

    cost_to_reach = dijkstra(n, adj_list, source=1)
    assert cost_to_reach[1:4] == [0, 3, 2]


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
    # main()
