#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct Class {
    int start, end;
};

bool compare_classes(const Class &a, const Class &b) {
    if (a.end == b.end)
        return a.start < b.start;

    return a.end < b.end;
}

int max_scheduled_activities(int num_rooms, vector<Class> classes) {
    sort(classes.begin(), classes.end(), compare_classes);

    // Track when each occupied room becomes free
    multiset<int, greater<>> room_end_times;
    int answer = 0;
    for (const auto &c : classes) {
        auto it = room_end_times.upper_bound(c.start);

        if (it == room_end_times.end()) {
            if ((int)room_end_times.size() < num_rooms) {
                room_end_times.insert(c.end);
                answer++;
            }
        } else {
            room_end_times.erase(it);
            room_end_times.insert(c.end);
            answer++;
        }
    }

    return answer;
}

void test_solution() {
    // 3 activities, 2 classrooms: [1, 2], [2, 3], [1, 3] -> 2
    assert(max_scheduled_activities(2, {{1, 2}, {2, 3}, {1, 3}}) == 2);
    // Single room, strictly disjoint activities (start > prev end)
    assert(max_scheduled_activities(1, {{1, 4}, {2, 5}, {5, 6}}) == 2);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    /*
    int num_classes, num_rooms;
    if (cin >> num_classes >> num_rooms) {
        vector<Class> classes(num_classes);
        for (int i = 0; i < num_classes; ++i) {
            cin >> classes[i].start >> classes[i].end;
        }
        cout << max_scheduled_activities(num_rooms, classes) << "\n";
    }
    */
    return 0;
}
