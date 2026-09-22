#include <bits/stdc++.h>
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

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> result = sol.permute(nums);

    for (auto &permutation : result) {
        cout << "[";
        for (size_t i = 0; i < permutation.size(); i++) {
            cout << permutation[i];
            if (i + 1 < permutation.size()) cout << ", ";
        }
        cout << "]" << endl;
    }

    return 0;
}
