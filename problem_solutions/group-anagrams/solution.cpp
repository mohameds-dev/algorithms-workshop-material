#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs) {
        unordered_map<string, vector<string>> groups;
        for (const string &s : strs) {
            string key = s;
            sort(key.begin(), key.end());
            groups[key].push_back(s);
        }

        vector<vector<string>> result;
        result.reserve(groups.size());
        for (auto &pair : groups) {
            result.push_back(move(pair.second));
        }
        return result;
    }
};

void test_solution() {
    Solution sol;
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> result = sol.groupAnagrams(strs);
    for (auto &group : result) {
        sort(group.begin(), group.end());
    }
    sort(result.begin(), result.end());

    vector<vector<string>> expected = {{"ate", "eat", "tea"}, {"bat"}, {"nat", "tan"}};
    sort(expected.begin(), expected.end());
    assert(result == expected);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
