#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    int solve(int index, int prev_index, const vector<int>& nums, vector<vector<int>>& memo) {
        if (index == (int)nums.size()) {
            return 0;
        }

        if (memo[index][prev_index + 1] != -1) {
            return memo[index][prev_index + 1];
        }

        int length = solve(index + 1, prev_index, nums, memo);
        if (prev_index == -1 || nums[index] > nums[prev_index]) {
            length = max(length, 1 + solve(index + 1, index, nums, memo));
        }

        return memo[index][prev_index + 1] = length;
    }

public:
    int lengthOfLIS(const vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> memo(n, vector<int>(n + 1, -1));
        return solve(0, -1, nums, memo);
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
