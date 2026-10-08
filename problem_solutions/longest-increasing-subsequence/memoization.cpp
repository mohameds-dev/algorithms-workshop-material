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
