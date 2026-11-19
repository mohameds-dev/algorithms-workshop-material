#include <bits/stdc++.h>
#include <cassert>
using namespace std;

class Solution {
public:
    int searchRecursive(vector<int> &nums, int target, int left, int right) {
        if (left > right) return -1;

        if (left == right) return nums[left] == target ? left : -1;

        int mid = (left + right) / 2;
        if (target >= nums[left] and target <= nums[mid]) {
            return searchRecursive(nums, target, left, mid);
        }

        return searchRecursive(nums, target, mid + 1, right);
    }

    int search(vector<int> &nums, int target) {
        return searchRecursive(nums, target, 0, (int)nums.size() - 1);
    }
};

void test_solution() {
    Solution sol;
    vector<int> nums1 = {-1, 0, 3, 5, 9, 12};
    assert(sol.search(nums1, 9) == 4);
    assert(sol.search(nums1, 2) == -1);
    vector<int> nums2 = {5};
    assert(sol.search(nums2, 5) == 0);
    assert(sol.search(nums2, -5) == -1);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
