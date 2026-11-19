#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    int solve(int index, int prev_index, const vector<int>& nums) {
        if (index == (int)nums.size()) {
            return 0;
        }

        int length = solve(index + 1, prev_index, nums);
        if (prev_index == -1 || nums[index] > nums[prev_index]) {
            length = max(length, 1 + solve(index + 1, index, nums));
        }

        return length;
    }

public:
    int lengthOfLIS(const vector<int>& nums) {
        return solve(0, -1, nums);
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
