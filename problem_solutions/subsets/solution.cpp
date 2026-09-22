#include <bits/stdc++.h>
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

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> result = sol.subsets(nums);

    for (auto &subset : result) {
        cout << "[";
        for (size_t i = 0; i < subset.size(); i++) {
            cout << subset[i];
            if (i + 1 < subset.size()) cout << ", ";
        }
        cout << "]" << endl;
    }

    return 0;
}
