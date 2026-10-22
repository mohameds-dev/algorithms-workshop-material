#include <algorithm>
#include <iostream>
#include <set>
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

bool compareIntervals(const Interval &a, const Interval &b) {
    return a.start < b.start or (a.start == b.start and a.end < b.end);
}

class Solution {
public:
    int minMeetingRooms(vector<Interval> &intervals) {
        sort(intervals.begin(), intervals.end(), compareIntervals);
        multiset<int, greater<>> room_available;

        for (auto &i : intervals) {
            auto it = room_available.lower_bound(i.start);
            // if room exists such that its next available time <= our start time
            // we book it, and update its next available time
            if (it != room_available.end()) {
                room_available.erase(it); // remove old available time
            }
            // else, we reserve anyway
            room_available.insert(i.end); // insert the end time of our class
        }
        return room_available.size();
    }
};

int main() {
    Solution sol;
    vector<Interval> t1 = {Interval(0, 30), Interval(5, 10), Interval(15, 20)};
    cout << sol.minMeetingRooms(t1) << endl; // 2

    vector<Interval> t2 = {Interval(2, 7)};
    cout << sol.minMeetingRooms(t2) << endl; // 1

    return 0;
}
