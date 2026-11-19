#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Interval {
public:
    int start, end;
    Interval(int start, int end) {
        this->start = start;
        this->end = end;
    }
};

class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        if (intervals.empty()) {
            return 0;
        }

        sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {
            return a.start < b.start;
        });

        priority_queue<int, vector<int>, greater<int>> room_end_times;

        for (const auto& i : intervals) {
            if (!room_end_times.empty() && room_end_times.top() <= i.start) {
                room_end_times.pop();
            }
            room_end_times.push(i.end);
        }

        return room_end_times.size();
    }
};

void test_solution() {
    Solution sol;
    vector<Interval> t1 = {{0, 30}, {5, 10}, {15, 20}};
    assert(sol.minMeetingRooms(t1) == 2);

    vector<Interval> t2 = {{2, 7}};
    assert(sol.minMeetingRooms(t2) == 1);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
