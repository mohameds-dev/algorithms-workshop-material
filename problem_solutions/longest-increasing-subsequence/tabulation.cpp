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
