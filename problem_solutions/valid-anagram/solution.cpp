#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) {
            return false;
        }

        vector<int> counts(26, 0);
        for (size_t i = 0; i < s.length(); i++) {
            counts[s[i] - 'a']++;
            counts[t[i] - 'a']--;
        }

        for (int count : counts) {
            if (count != 0) {
                return false;
            }
        }
        return true;
    }
};

void test_solution() {
    Solution sol;
    assert(sol.isAnagram("anagram", "nagaram") == true);
    assert(sol.isAnagram("rat", "car") == false);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
