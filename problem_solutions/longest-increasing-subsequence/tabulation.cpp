#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLIS(const vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        int n = nums.size();
        vector<int> lis(n, 1);
        int max_len = 1;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {
                    lis[i] = max(lis[i], lis[j] + 1);
                }
            }
            max_len = max(max_len, lis[i]);
        }

        return max_len;
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
