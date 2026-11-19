#include <algorithm>
#include <cassert>
#include <iostream>
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
    bool canAttendMeetings(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {
            return a.start < b.start;
        });

        for (size_t i = 0; i + 1 < intervals.size(); i++) {
            if (intervals[i].end > intervals[i + 1].start) {
                return false;
            }
        }
        return true;
    }
};

void test_solution() {
    Solution sol;
    vector<Interval> test1 = {{0, 30}, {5, 10}, {15, 20}};
    assert(sol.canAttendMeetings(test1) == false);

    vector<Interval> test2 = {{5, 8}, {9, 15}};
    assert(sol.canAttendMeetings(test2) == true);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
