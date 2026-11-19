import heapq


def dijkstra(num_cities: int, adj: list[list[tuple[int, int]]], source: int = 1) -> list[int]:
    inf = float("inf")
    dist = [inf] * (num_cities + 1)
    dist[source] = 0

    pq = [(0, source)]

    while pq:
        curr_dist, city = heapq.heappop(pq)

        if curr_dist > dist[city]:
            continue

        for neighbor, flight_cost in adj[city]:
            new_dist = curr_dist + flight_cost
            if new_dist < dist[neighbor]:
                dist[neighbor] = new_dist
                heapq.heappush(pq, (new_dist, neighbor))

    return dist


def main():
    num_cities, num_flights = map(int, input().split())

    adj = [[] for _ in range(num_cities + 1)]
    for _ in range(num_flights):
        src, dst, cost = map(int, input().split())
        adj[src].append((dst, cost))

    dist = dijkstra(num_cities, adj, source=1)
    print(*(dist[1 : num_cities + 1]))


def test_solution():
    # CSES 1671 sample test case:
    # 3 cities, 3 flights: 1->2 (cost 6), 1->3 (cost 2), 3->2 (cost 1)
    num_cities = 3
    adj = [[] for _ in range(num_cities + 1)]
    adj[1].append((2, 6))
    adj[1].append((3, 2))
    adj[3].append((2, 1))

    dist = dijkstra(num_cities, adj, source=1)
    assert dist[1:4] == [0, 3, 2]


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
    # main()
