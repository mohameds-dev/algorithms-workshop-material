#include <bits/stdc++.h>
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

int main() {
    Solution sol;
    vector<int> nums = {-1, 0, 3, 5, 9, 12};
    int target = 9;
    cout << sol.search(nums, target) << endl;

    return 0;
}
