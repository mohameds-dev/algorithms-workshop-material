#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char, int> count_map;
        for (char task : tasks) {
            count_map[task]++;
        }

        priority_queue<int> max_heap;
        for (auto const& [task, count] : count_map) {
            max_heap.push(count);
        }

        queue<pair<int, int>> wait_q; // pair of (remaining_count, ready_time)
        int cur_time = 0;

        while (!max_heap.empty() || !wait_q.empty()) {
            if (!max_heap.empty()) {
                int count = max_heap.top();
                max_heap.pop();
                count--;
                if (count > 0) {
                    wait_q.push({count, cur_time + n});
                }
            }

            if (!wait_q.empty() && wait_q.front().second == cur_time) {
                max_heap.push(wait_q.front().first);
                wait_q.pop();
            }

            cur_time++;
        }

        return cur_time;
    }
};

void test_solution() {
    Solution sol;
    vector<char> tasks1 = {'A', 'A', 'A', 'B', 'B', 'B'};
    assert(sol.leastInterval(tasks1, 2) == 8);

    vector<char> tasks2 = {'A', 'C', 'A', 'B', 'D', 'B'};
    assert(sol.leastInterval(tasks2, 1) == 6);

    vector<char> tasks3 = {'A', 'A', 'A', 'B', 'B', 'B'};
    assert(sol.leastInterval(tasks3, 3) == 10);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
