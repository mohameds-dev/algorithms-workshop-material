from typing import List


class Interval:
    def __init__(self, start: int, end: int):
        self.start = start
        self.end = end


class Solution:
    def canAttendMeetings(self, intervals: List[Interval]) -> bool:
        intervals.sort(key=lambda i: i.start)
        for i in range(len(intervals) - 1):
            if intervals[i].end > intervals[i + 1].start:
                return False

        return True


def test_solution():
    sol = Solution()
    test1 = [Interval(0, 30), Interval(5, 10), Interval(15, 20)]
    assert sol.canAttendMeetings(test1) is False

    test2 = [Interval(5, 8), Interval(9, 15)]
    assert sol.canAttendMeetings(test2) is True


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
