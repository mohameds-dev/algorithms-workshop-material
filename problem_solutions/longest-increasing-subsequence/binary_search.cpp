#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLIS(const vector<int>& nums) {
        vector<int> tails;

        for (int x : nums) {
            auto it = lower_bound(tails.begin(), tails.end(), x);
            if (it == tails.end()) {
                tails.push_back(x);
            } else {
                *it = x;
            }
        }

        return tails.size();
    }
};

#include <iostream>

void test_solution() {
    Solution sol;
    vector<int> nums1 = {10, 9, 2, 5, 3, 7, 101, 18};
    assert(sol.lengthOfLIS(nums1) == 4);
    vector<int> nums2 = {0, 1, 0, 3, 2, 3};
    assert(sol.lengthOfLIS(nums2) == 4);
    vector<int> nums3 = {7, 7, 7, 7, 7, 7, 7};
    assert(sol.lengthOfLIS(nums3) == 1);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
