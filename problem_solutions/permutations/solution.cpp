#include <bits/stdc++.h>
#include <cassert>
using namespace std;

class Solution {
public:
    void backtrack(vector<int> &nums, vector<bool> &used, vector<int> &chosen, vector<vector<int>> &permutations) {
        if (chosen.size() == nums.size()) {
            permutations.push_back(chosen);
            return;
        }

        for (int i = 0; i < (int)nums.size(); i++) {
            if (used[i]) continue;

            used[i] = true;
            chosen.push_back(nums[i]);
            backtrack(nums, used, chosen, permutations);
            chosen.pop_back();
            used[i] = false;
        }
    }

    vector<vector<int>> permute(vector<int> &nums) {
        vector<vector<int>> result;
        vector<bool> used(nums.size(), false);
        vector<int> chosen;
        backtrack(nums, used, chosen, result);
        return result;
    }
};

void test_solution() {
    Solution sol;
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> res = sol.permute(nums);
    assert(res.size() == 6);
    vector<int> single = {1};
    assert(sol.permute(single) == vector<vector<int>>{{1}});
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
