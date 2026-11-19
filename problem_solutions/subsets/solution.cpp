#include <bits/stdc++.h>
#include <cassert>
using namespace std;

class Solution {
public:
    void backtrack(vector<int> &nums, int index, vector<int> &chosen, vector<vector<int>> &subsets) {
        if (index == (int)nums.size()) {
            subsets.push_back(chosen);
            return;
        }

        backtrack(nums, index + 1, chosen, subsets);

        chosen.push_back(nums[index]);
        backtrack(nums, index + 1, chosen, subsets);
        chosen.pop_back();
    }

    vector<vector<int>> subsets(vector<int> &nums) {
        vector<vector<int>> result;
        vector<int> chosen;
        backtrack(nums, 0, chosen, result);
        return result;
    }
};

void test_solution() {
    Solution sol;
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> res = sol.subsets(nums);
    assert(res.size() == 8);
    vector<int> single = {0};
    assert(sol.subsets(single).size() == 2);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
