#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int> &nums) {
        int n = nums.size();
        vector<int> prefix(n, 0);
        int product = 1;
        for (int i = 0; i < n; i++) {
            product *= nums[i];
            prefix[i] = product;
        }

        vector<int> suffix(n, 0);
        product = 1;
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

int main() {
    Solution sol;
    vector<int> nums1 = {1, 2, 3, 4};
    for (int x : sol.productExceptSelf(nums1)) {
        cout << x << " ";
    }
    cout << endl;

    vector<int> nums2 = {-1, 1, 0, -3, 3};
    for (int x : sol.productExceptSelf(nums2)) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
