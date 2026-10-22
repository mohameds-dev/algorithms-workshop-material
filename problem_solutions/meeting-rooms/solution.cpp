#include <algorithm>
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
    bool canAttendMeetings(vector<Interval> &intervals) {
        sort(intervals.begin(), intervals.end(), [](const Interval &a, const Interval &b) {
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

int main() {
    Solution sol;
    vector<Interval> t1 = {Interval(0, 30), Interval(5, 10), Interval(15, 20)};
    cout << boolalpha << sol.canAttendMeetings(t1) << endl; // false

    vector<Interval> t2 = {Interval(5, 8), Interval(9, 15)};
    cout << boolalpha << sol.canAttendMeetings(t2) << endl; // true

    return 0;
}
