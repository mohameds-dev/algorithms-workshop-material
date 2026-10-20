#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    int leastInterval(vector<char> &tasks, int n) {
        vector<int> freq(26, 0);
        for (char task : tasks) {
            freq[task - 'A']++;
        }

        priority_queue<int> maxHeap;
        for (int count : freq) {
            if (count > 0) {
                maxHeap.push(count);
            }
        }

        queue<pair<int, int>> waitQueue;
        int curTime = 0;

        while (!maxHeap.empty() || !waitQueue.empty()) {
            if (!maxHeap.empty()) {
                int count = maxHeap.top() - 1;
                maxHeap.pop();
                if (count > 0) {
                    waitQueue.push({count, curTime + n});
                }
            }

            if (!waitQueue.empty() && waitQueue.front().second == curTime) {
                int count = waitQueue.front().first;
                waitQueue.pop();
                maxHeap.push(count);
            }

            curTime++;
        }

        return curTime;
    }
};

int main() {
    Solution sol;
    vector<char> tasks1 = {'A', 'A', 'A', 'B', 'B', 'B'};
    cout << sol.leastInterval(tasks1, 2) << endl; // 8

    vector<char> tasks2 = {'A', 'C', 'A', 'B', 'D', 'B'};
    cout << sol.leastInterval(tasks2, 1) << endl; // 6

    vector<char> tasks3 = {'A', 'A', 'A', 'B', 'B', 'B'};
    cout << sol.leastInterval(tasks3, 3) << endl; // 10

    return 0;
}
