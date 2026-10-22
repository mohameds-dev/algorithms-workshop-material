#include <algorithm>
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

int main() {
    int num_classes, num_rooms;
    cin >> num_classes >> num_rooms;

    vector<Class> classes(num_classes);

    for (int i = 0; i < num_classes; ++i) {
        int a, b;
        cin >> a >> b;
        classes[i] = {a, b};
    }

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

    cout << answer << "\n";
    return 0;
}
