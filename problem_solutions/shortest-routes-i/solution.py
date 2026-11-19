import heapq


def main():
    num_cities, num_flights = map(int, input().split())

    adj = [[] for _ in range(num_cities + 1)]
    for _ in range(num_flights):
        src, dst, cost = map(int, input().split())
        adj[src].append((dst, cost))

    inf = float("inf")
    dist = [inf] * (num_cities + 1)
    dist[1] = 0

    pq = [(0, 1)]

    while pq:
        curr_dist, city = heapq.heappop(pq)

        if curr_dist > dist[city]:
            continue

        for neighbor, flight_cost in adj[city]:
            new_dist = curr_dist + flight_cost
            if new_dist < dist[neighbor]:
                dist[neighbor] = new_dist
                heapq.heappush(pq, (new_dist, neighbor))

    print(*(dist[1 : num_cities + 1]))


if __name__ == "__main__":
    main()
