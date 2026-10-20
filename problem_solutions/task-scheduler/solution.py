from collections import Counter, deque
import heapq


class Solution:
    def leastInterval(self, tasks: list[str], n: int) -> int:
        counts = [-c for c in Counter(tasks).values()]
        heapq.heapify(counts)
        wait_q = deque()  # (-count, ready_time)

        cur_time = 0

        while counts or wait_q:
            if counts:
                count = heapq.heappop(counts) + 1
                if count != 0:
                    wait_q.append((count, cur_time + n))

            if wait_q and wait_q[0][1] == cur_time:
                count, ready_time = wait_q.popleft()
                heapq.heappush(counts, count)

            cur_time += 1

        return cur_time


if __name__ == "__main__":
    sol = Solution()
    print(sol.leastInterval(["A", "A", "A", "B", "B", "B"], 2))  # 8
    print(sol.leastInterval(["A", "C", "A", "B", "D", "B"], 1))  # 6
    print(sol.leastInterval(["A", "A", "A", "B", "B", "B"], 3))  # 10
