class Solution:
    def distanceLimitedPathsExist(
        self, n: int, edgeList: list[list[int]], queries: list[list[int]]
    ) -> list[bool]:
        parent = list(range(n))

        def find(i: int) -> int:
            path = []
            while parent[i] != i:
                path.append(i)
                i = parent[i]
            for p in path:
                parent[p] = i
            return i

        def union(u: int, v: int):
            root_u = find(u)
            root_v = find(v)
            if root_u != root_v:
                parent[root_v] = root_u

        # Sort edges by weight
        sorted_edges = sorted(edgeList, key=lambda x: x[2])

        # Sort queries by limit, tracking original index
        indexed_queries = sorted(
            enumerate(queries), key=lambda item: item[1][2]
        )

        answer = [False] * len(queries)
        edge_idx = 0
        num_edges = len(sorted_edges)

        for orig_idx, (p, q, limit) in indexed_queries:
            while edge_idx < num_edges and sorted_edges[edge_idx][2] < limit:
                union(sorted_edges[edge_idx][0], sorted_edges[edge_idx][1])
                edge_idx += 1
            answer[orig_idx] = find(p) == find(q)

        return answer


def test_solution():
    sol = Solution()
    edges1 = [[0, 1, 2], [1, 2, 4], [2, 0, 8], [1, 0, 16]]
    queries1 = [[0, 1, 2], [0, 2, 5]]
    assert sol.distanceLimitedPathsExist(3, edges1, queries1) == [False, True]

    edges2 = [[0, 1, 10], [1, 2, 5], [2, 3, 9], [3, 4, 13]]
    queries2 = [[0, 4, 14], [1, 4, 13]]
    assert sol.distanceLimitedPathsExist(5, edges2, queries2) == [True, False]


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
