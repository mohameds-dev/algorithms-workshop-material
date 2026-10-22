import heapq
from typing import List


class Interval:
    def __init__(self, start: int, end: int):
        self.start = start
        self.end = end


class Solution:
    def minMeetingRooms(self, intervals: List[Interval]) -> int:
        if not intervals:
            return 0

        intervals.sort(key=lambda i: (i.start, i.end))
        room_end_times = []  # min-heap storing end times

        for i in intervals:
            if room_end_times and room_end_times[0] <= i.start:
                heapq.heappop(room_end_times)
            heapq.heappush(room_end_times, i.end)

        return len(room_end_times)


if __name__ == "__main__":
    sol = Solution()
    t1 = [Interval(0, 30), Interval(5, 10), Interval(15, 20)]
    print(sol.minMeetingRooms(t1))  # 2

    t2 = [Interval(2, 7)]
    print(sol.minMeetingRooms(t2))  # 1
