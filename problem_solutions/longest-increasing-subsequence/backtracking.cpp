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
