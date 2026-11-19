#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int> &nums) {
        unordered_set<int> my_set(nums.begin(), nums.end());
        int answer = 0;

        for (int num : nums) {
            if (my_set.find(num - 1) != my_set.end()) {
                continue;
            }

            int i = 1;
            while (my_set.find(num + i) != my_set.end()) {
                i++;
            }
            answer = max(answer, i);
        }

        return answer;
    }
};

void test_solution() {
    Solution sol;
    vector<int> nums1 = {100, 4, 200, 1, 3, 2};
    assert(sol.longestConsecutive(nums1) == 4);

    vector<int> nums2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    assert(sol.longestConsecutive(nums2) == 9);

    vector<int> nums3 = {};
    assert(sol.longestConsecutive(nums3) == 0);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
