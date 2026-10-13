#include <algorithm>
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

int main() {
    Solution sol;
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> result = sol.groupAnagrams(strs);
    for (const auto &group : result) {
        cout << "[";
        for (size_t i = 0; i < group.size(); i++) {
            cout << group[i];
            if (i + 1 < group.size()) cout << ", ";
        }
        cout << "]\n";
    }
    return 0;
}
