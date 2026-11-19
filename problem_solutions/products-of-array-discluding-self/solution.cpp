#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        int product = 1;
        vector<int> prefix(n, 0);
        for (int i = 0; i < n; i++) {
            product *= nums[i];
            prefix[i] = product;
        }

        product = 1;
        vector<int> suffix(n, 0);
        for (int i = n - 1; i >= 0; i--) {
            product *= nums[i];
            suffix[i] = product;
        }

        vector<int> answer(n, 0);
        for (int i = 0; i < n; i++) {
            if (i > 0 && i < n - 1) {
                answer[i] = prefix[i - 1] * suffix[i + 1];
            } else if (i == 0) {
                answer[i] = suffix[i + 1];
            } else {
                answer[i] = prefix[i - 1];
            }
        }

        return answer;
    }
};

void test_solution() {
    Solution sol;
    vector<int> nums1 = {1, 2, 3, 4};
    vector<int> expected1 = {24, 12, 8, 6};
    assert(sol.productExceptSelf(nums1) == expected1);

    vector<int> nums2 = {-1, 1, 0, -3, 3};
    vector<int> expected2 = {0, 0, 9, 0, 0};
    assert(sol.productExceptSelf(nums2) == expected2);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
